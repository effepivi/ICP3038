/*

 Copyright (c) 2020, Dr Franck P. Vidal (f.vidal@bangor.ac.uk),
 http://www.fpvidal.net/
 All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation and/or
 other materials provided with the distribution.

 3. Neither the name of the Bangor University nor the names of its contributors
 may be used to endorse or promote products derived from this software without
 specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/


/**
 ********************************************************************************
 *
 *   @file       hoguh_transform.cxx
 *
 *   @brief      Demo program to show how to implement the Hough transform.
 *
 *   @version    1.0
 *
 *   @date       06/02/2020
 *
 *   @author     Dr Franck P. Vidal
 *
 *   @section    License
 *               BSD 3-Clause License.
 *
 *               For details on use and redistribution please refer
 *               to http://opensource.org/licenses/BSD-3-Clause
 *
 *   @section    Copyright
 *               (c) by Dr Franck P. Vidal (f.vidal@bangor.ac.uk),
 *               http://www.fpvidal.net/, Feb 2020 2020, version 1.0,
 *               BSD 3-Clause License
 *
 ********************************************************************************
 */


//******************************************************************************
//  Include
//******************************************************************************

// Header for cout and cerr (display some text in the console)
#include <iostream>

// C++ strings
#include <string>

// C++ exceptions
#include <exception>

// Headers for OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"


//******************************************************************************
//  Name spaces
//******************************************************************************

using namespace cv;
using namespace std;


//******************************************************************************
//  Function declarations
//******************************************************************************

double deg2rad(double anAngleInDegrees);

// Callback function for the threshold trackbar
void thresholdCallback(int, void*);

Mat houghTransform(const Mat& anInputImage,
                   int aCannyThreshold);

Mat drawLines(const Mat& anImage,
              const Mat& anAccumulator,
              int aHoughThreshold,
              int aLineWidth = 1,
              const Scalar& aLineColour = Scalar(0, 0, 255));


//******************************************************************************
//  Global variables
//******************************************************************************

int g_canny_low_threshold = 0;
int g_hough_low_threshold = 100;
const int g_max_low_threshold = 100;
const int g_ratio = 3;
const int g_kernel_size = 3;

Mat g_input_RGB_image;
Mat g_input_luminance_image;
Mat g_accumulator_image;


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    try
    {
        // Check the number of command line arguments
        if (argc != 2)
        {
            throw "Invalid number of command line arguments";
        }

        // Read the image
        g_input_RGB_image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

        // Check for invalid input
        if (!g_input_RGB_image.data)
        {
            throw "Could not open or find the image";
        }

        // Create a window called "input RGB image"
        namedWindow("input RGB image", CV_WINDOW_AUTOSIZE);

        // Show our image
        imshow ("input RGB image", g_input_RGB_image);

        // The image is not a greyscale image, convert it
        cvtColor(g_input_RGB_image, g_input_luminance_image, CV_RGB2GRAY);

        // Create a window called "input luminance image"
        namedWindow("input luminance image", CV_WINDOW_AUTOSIZE);

        // Show our image
        imshow ("input luminance image", g_input_luminance_image);


        /// Canny operator

        // Create a window called "edge image"
        namedWindow("edge image", CV_WINDOW_AUTOSIZE);

        // Create a slider in this window
        createTrackbar("Min Canny Threshold:",
                       "edge image",
                       &g_canny_low_threshold,
                       g_max_low_threshold,
                       thresholdCallback);

        // Run the Hough transform at least once
        thresholdCallback(0, 0);

        // Event loop
        char key = 0;
        while(key != 'q' && key != 27)
        {
            key = cv::waitKey(0);
        }
    }
    // There was an error
    catch (const std::exception& error)
    {
        std::cerr << "ERROR:\t" << error.what() << std::endl;
        return 1;
    }
    catch (const std::string& error)
    {
        std::cerr << "ERROR:\t" << error << std::endl;
        return 1;
    }
    catch (const char* error)
    {
        std::cerr << "ERROR:\t" << error << std::endl;
        return 1;
    }

    return 0;
}


//--------------------------------------------
inline double deg2rad(double anAngleInDegrees)
//--------------------------------------------
{
    return anAngleInDegrees * M_PI / 180.0;
}


//--------------------------------
void thresholdCallback(int, void*)
//--------------------------------
{
    g_accumulator_image = houghTransform(g_input_luminance_image, g_canny_low_threshold);

    Mat normalised_accumulator;
    normalize(g_accumulator_image, normalised_accumulator, 0, 255, NORM_MINMAX);
    imshow("accumulator image", normalised_accumulator);

    Mat image_with_lines = drawLines(g_input_RGB_image, g_accumulator_image, g_hough_low_threshold, 4);
    imshow("image with lines", image_with_lines);
}


//-----------------------------------------
Mat houghTransform(const Mat& anInputImage,
                   int aCannyThreshold)
//-----------------------------------------
{
    Mat blurred_image;
    blur( g_input_luminance_image, blurred_image, Size(3,3) );

    Mat edge_image;
    Canny(blurred_image,
          edge_image,
          aCannyThreshold,
          aCannyThreshold * g_ratio,
          g_kernel_size);

    imshow("edge image", edge_image);

    int width  = 180;
    double diagonal = sqrt(edge_image.cols * edge_image.cols + edge_image.rows * edge_image.rows);
    int height = floor(2.0 * diagonal);
    double half_height = height / 2.0;
    Mat accumulator(height, width, CV_8U, Scalar(0));

    // Process all the pixels of the edge image
    for (int j = 0; j < edge_image.rows; ++j)
    {
        for (int i = 0; i < edge_image.cols; ++i)
        {
            // The pixel is on an edge
            if (edge_image.at<unsigned char>(i, j) > 0)
            {
                // Process all the angles
                for (int theta = 0; theta <= 180; ++theta)
                {
                    double angle = deg2rad(theta);
                    double r = i * cos(angle) + j * sin(angle);

                    int v = floor(r + half_height);
                    //cout << theta << " " << v << " " << accumulator.cols << "x" << accumulator.rows << endl;
                    accumulator.at<unsigned char>(v, theta) += 1;
                }
            }
        }
    }

    return accumulator;
}


//--------------------------------------
Mat drawLines(const Mat& anImage,
              const Mat& anAccumulator,
              int aHoughThreshold,
              int aLineWidth,
              const Scalar& aLineColour)
//--------------------------------------
{
    // Copy the input image into the output image
    Mat output = anImage;

    // Process all the pixels of the accumulator image
    for (int j = 0; j < anAccumulator.rows; ++j)
    {
        for (int i = 0; i < anAccumulator.cols; ++i)
        {
            if (anAccumulator.at<unsigned char>(j, i) > aHoughThreshold)
            {
                // Find global maxima
                Point location(i, j);

                Point pt1(               0, 0);
                Point pt2(anImage.cols - 1, anImage.rows - 1);

                double theta = deg2rad(location.x);

                double r = location.y;
                r -= anAccumulator.rows / 2.0;

                cout << location << "  " << int(anAccumulator.at<unsigned char>(j, i)) << "   " << aHoughThreshold << "  " << theta << "  " << r << endl;

                // How to retrieve the line from theta and r:
                //      x = (r - y * sin(theta)) / cos(theta);
                //      y = (r - x * cos(theta)) / sin(theta);

                // sin(theta) != 0
                if (location.x != 0 && location.x != 180)
                {
                    pt1.x = (r - pt1.y * cos(theta)) / sin(theta);
                    pt2.x = (r - pt2.y * cos(theta)) / sin(theta);
                }
                // sin(theta) == 0 && cos(theta) != 0
                else
                {
                    pt1.y = (r - pt1.x * sin(theta)) / cos(theta);
                    pt2.y = (r - pt2.x * sin(theta)) / cos(theta);
                }

                // Draw the line
                line(output, pt1, pt2, aLineColour, aLineWidth);
            }
        }
    }

    return output;
}
