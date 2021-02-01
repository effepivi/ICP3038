/**
********************************************************************************
*
*    @file      videoFromFile.cxx
*
*    @brief     A simple program using OpenCV to display a video and
*               perform some image processing tasks.
*
*    @version   1.0
*
*    @date      05/02/2020
*
*    @author    Franck Vidal
*
*
********************************************************************************
*/


//******************************************************************************
//    Includes
//******************************************************************************
#include <exception> // Header for catching exceptions
#include <iostream>  // Header to display text in the console
#include <string>    // Header to manipulate strings
#include <cmath>     // Header use round()

#include <opencv2/opencv.hpp> // Main OpenCV header


//******************************************************************************
//    Namespaces
//******************************************************************************
using namespace std;


//******************************************************************************
//    Global variables
//******************************************************************************
const double EPSILON(1.0e-5);

const int g_edge = 5; // Edge around the images in the window

cv::Mat g_current_frame; // Store the current frame
cv::Mat g_edge_frame;    // Store the edges detected in the current frame
cv::Mat g_displayed_image; // The image displayed in the window

// The title of every window
std::string g_window_title("Video");


//******************************************************************************
//    Function declaration
//******************************************************************************
void cartoonise(int, void*);


//******************************************************************************
//    Implementation
//******************************************************************************


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    try
    {
		/**********************************************************************/
		/* Declare some local variables                                       */
		/**********************************************************************/

		// File names
		std::string input_file_name;
		std::string output_file_name;


		/**********************************************************************/
		/* Process the command line arguments                                 */
		/**********************************************************************/

        // No file to display
        if (argc != 3 && argc != 4)
        {
            // Create an error message
            std::string error_message;
            error_message  = "Usage: ";
            error_message += argv[0];
            error_message += " <input_video>";
            error_message += " <scaling_factor>";
            error_message += " [output_video]";

            error_message += "\n\tExample: ";
            error_message += argv[0];
            error_message += " SAMPLING.AVI";
            error_message += " 0.25";
            error_message += " test.avi";

            // Throw an error
            throw error_message;
        }


		// Get the file names
		input_file_name  = argv[1];
        double scaling_factor = atof(argv[2]);

        // An output file name has been specified
        if (argc == 4)
        {
            output_file_name = argv[3];
        }



		/**********************************************************************/
		/* Open the video                                                     */
		/**********************************************************************/

        // Open the video file
        cv::VideoCapture video_capture; // !@£ YOUR CODE HERE £@!

        // The image has not been loaded
        if (!video_capture.isOpened())
        {
            // Create an error message
            // !@£ YOUR CODE HERE £@!

            // Throw an error
            // !@£ YOUR CODE HERE £@!
        }

        // Read the frame rate of the video (does not always work)
        double fps = 0.0; // !@£ YOUR CODE HERE £@!
        cout << "Frame per seconds : " << fps << endl;

		// Convert in seconds per frame (default 30 ms / frame)
		double seconds_per_frame(1.0 / fps);

		// Convert in milliseconds
		int milliseconds_per_frame(round(seconds_per_frame * 1000.0));

        // Get the video size
		cv::Size input_video_size; // !@£ YOUR CODE HERE £@!

        // Apply the scaling factor
		cv::Size scaled_video_size; // !@£ YOUR CODE HERE £@!

        // Set the size of the image displayed in the window
		cv::Size target_video_size; // !@£ YOUR CODE HERE £@!

        // Create the output image
        // !@£ YOUR CODE HERE £@!


		/**********************************************************************/
		/* File writer                                                        */
		/**********************************************************************/
		cv::VideoWriter video_writer;

        // Open the output
        if (output_file_name.size())
        {
            // !@£ YOUR CODE HERE £@!
        }



		/**********************************************************************/
		/* Create the window                                                 */
		/**********************************************************************/

        // Create the window
        cv::namedWindow(g_window_title, cv::WINDOW_AUTOSIZE);


		/**********************************************************************/
		/* Event loop                                                         */
		/**********************************************************************/

        // Last key pressed
        int key;

		// Event loop
        do
        {
            // Grab the next frame if possible
            // If an error occured, throw an error
            if (!video_capture.read(g_current_frame))
            {
                // Throw an error
                throw "Could not read frames from the video.";
            }

            // Resize the input if needed
            if (input_video_size != scaled_video_size)
            {
                cv::resize(g_current_frame, g_current_frame, scaled_video_size);
            }

            // Process the image
            cartoonise(0, 0);

            // The file writer is working
            if (video_writer.isOpened())
            {
                // Add the current frame
                // !@£ YOUR CODE HERE £@!
            }

            // Wait for the key press event for X ms
			// (with X equal to 'milliseconds_per_frame')
            key = cv::waitKey(milliseconds_per_frame);
        }
        // Stop the loop if 'q' or 'Escape' have been pressed
        while (key != 'q' && key != 27);
    }
    // An error occured
    catch (const std::exception& error)
    {
        // Display an error message in the console
        cerr << error.what() << endl;
    }
    catch (const std::string& error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }
    catch (const char* error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }

    // Exit the program
    return 0;
}


//-------------------------
void cartoonise(int, void*)
//-------------------------
{
    // Copy the current frame into the large image (g_displayed_image).
    // Add an edge of g_edge pixels around g_current_frame.
    // !@£ YOUR CODE HERE £@!

    
    // Convert the image (g_current_frame) to greyscale.
    // Save the resulting image in greyscale_frame.
    cv::Mat greyscale_frame;
    // !@£ YOUR CODE HERE £@!
    
    
    // Apply a median filter on greyscale_frame with a size of 7 pixels.
    // Save the resulting image in median_frame.
    cv::Mat median_frame;
    // !@£ YOUR CODE HERE £@!
    
    
    // Perform a Laplacian filter on median_frame
    // You must use unsigned char for the output, i.e. the depth is CV_8U
    // The kernel size is 5x5
    // Save the resulting image in edge_frame.
    cv::Mat edge_frame;
    // !@£ YOUR CODE HERE £@!
    
    
    // Perform an edge detection using edge_frame and the threshold function.
    // The threshold is 100, the maximum value is 255, and the thresholding type is THRES_BINARY_INV (or 1).
    // Save the resulting image in mask_frame.
    cv::Mat mask_frame;
    // !@£ YOUR CODE HERE £@!
    
    
    // Reduce the input image (g_current_frame) size by a factor 10 and resample using pixel area relation.
    // Save the resulting image in small_frame.
    float ds_factor = 4;
    cv::Mat small_frame;
    // !@£ YOUR CODE HERE £@!
    
    
    // Apply a bilateral filter 10 times. The kernel size is 5, sigma colour is 5, and sigma space is 7.
    // Save the resulting image in small_frame.
    // !@£ YOUR CODE HERE £@!

    
    // Restore the of the image (small_frame) so that it is the same as the input image (g_current_frame) and resample using bi-linear interpolation.
    // Save the resulting image in output_frame.
    cv::Mat output_frame;
    // !@£ YOUR CODE HERE £@!

    
    // Add a thick boundary using a boolean operator (AND).
    // Save the resulting image in cartoon_frame.
    cv::Mat cartoon_frame;
    // !@£ YOUR CODE HERE £@!

    
    // Copy the result
    // !@£ YOUR CODE HERE £@!

    
    // Display the images
    // !@£ YOUR CODE HERE £@!
}
