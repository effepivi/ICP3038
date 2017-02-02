/*
 
 Copyright (c) 2017, Dr Franck P. Vidal (f.vidal@bangor.ac.uk),
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
 *   @file       sobel_image.cxx
 *
 *   @brief      Demo program to show how to implement the Sobel edge detector
 *               using OpenCV.
 *
 *   @version    1.0
 *
 *   @date       02/02/2017
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
 *               http://www.fpvidal.net/, Feb 2017, 2017, version 1.0,
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

// Callback function for the threshold trackbar
void Threshold_Demo( int aThreshold, void* apImage);


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
        Mat input_image = imread(argv[1]);
        
        // Check for invalid input
        if (!input_image.data)
        {
            throw "Could not open or find the image";
        }
        
        // Create a window called "input"
        namedWindow("input", CV_WINDOW_AUTOSIZE);
        
        // The image is not a greyscale image
        cv::cvtColor(input_image, input_image, CV_RGB2GRAY);
        
        // Show our image
        imshow ("input", input_image);
        
        /// Sobel detector
        cv::Mat sobel_x;
        cv::Sobel(input_image , sobel_x, CV_32F, 1, 0);
        imshow ("sobel_x", sobel_x);
        
        
        
        
        
        
        /*
       
        cv::Mat sobel_y;
        cv::Sobel(input_image , sobel_y, CV_32F, 0, 1);
        imshow ("sobel_y", sobel_y);
        
        */
        
        
        
        
        
        /*
        cv::Mat abs_sobel_x;
        abs_sobel_x = cv::abs(sobel_x);
        imshow ("abs_sobel_x", abs_sobel_x);
        */
        
        
        
        
        
        /*
        
        cv::Mat abs_sobel_y;
        abs_sobel_y = cv::abs(sobel_y);
        imshow ("abs_sobel_y", abs_sobel_y);
        */
        
        
        
        
        
        
        /*
        cv::Mat sobel;
        sobel = abs_sobel_x + abs_sobel_y;
        imshow ("sobel", sobel);

        */
        
        
        
        
        
        /*
        cv::normalize(sobel, sobel, 0.0, 255, cv::NORM_MINMAX, CV_8UC1);
        imshow ("normalize", sobel);
        */
        
        
        
        
        
        
        
        /*
        Mat threshold;
        cv::threshold(sobel, threshold, 128, 255, THRESH_BINARY );
        imshow( "Thresohld", threshold );
*/
        
        
        
        

        
        
        
        
        
        
        /*
        int threshold_value(128);
        createTrackbar( "Thresohld: " ,
                "Thresohld",
                &threshold_value,
                255,
                Threshold_Demo,
                &sobel );
        */

        
        
        
        

        
        
        
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


void Threshold_Demo( int aThreshold, void* apImage)
{
    Mat* p_image(reinterpret_cast<Mat*>(apImage));
    Mat dst;
    threshold(*p_image, dst, aThreshold, 255, THRESH_BINARY );
    
    imshow( "Thresohld", dst );
}
