/**
********************************************************************************
*
*    @file       edgeDetection1.cxx
*
*    @brief      A simple program using OpenCV to detect edges.
*
*    @version    1.0
*
*    @date       08/02/2016
*
*    @author     Franck Vidal
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
#include <opencv2/opencv.hpp> // Main OpenCV header


//******************************************************************************
//    Namespaces
//******************************************************************************
using namespace std;


//******************************************************************************
//    Global variables
//******************************************************************************


//******************************************************************************
//    Function declaration
//******************************************************************************


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

        // Image structures
        cv::Mat rgb_image;        
        cv::Mat grey_image;
        cv::Mat gaussian_image;
        cv::Mat scharr_image;
        cv::Mat edge_image;
        
        // The title of every window
        std::string grey_image_window_title("Original data");
        std::string filtered_image_window_title("Filtered data");
        std::string edge_image_window_title("Edge data");
        

		/**********************************************************************/
		/* Process the command line arguments                                 */
		/**********************************************************************/

        // No file to display
        if (argc != 3)
        {
            // Create an error message
            std::string error_message;
            error_message  = "usage: ";
            error_message += argv[0];
            error_message += " <input_image>";
            error_message += " <output_image>";

            // Throw an error
            throw error_message;
        }

		// Get the file names
		input_file_name  = argv[1];
		output_file_name = argv[2];


		/**********************************************************************/
		/* Read the input                                                     */
		/**********************************************************************/
		
		
        // Open and read the image
        rgb_image = cv::imread(input_file_name, CV_LOAD_IMAGE_COLOR);

        // The image has not been loaded
        if (!rgb_image.data)
        {
            // Create an error message
            std::string error_message;
            error_message  = "Could not open or find the image \"";
            error_message += input_file_name;
            error_message += "\".";

            // Throw an error
            throw error_message;
        }

		/**********************************************************************/
		/* Convert the RGB data to greyscale                                  */
		/**********************************************************************/
				
		// Write your own code here to
        
        // 1) Convert the image from RGB to greyscale
        
        // 2) Convert the image from unsigned char to float
        
        // 3) Normalise the image

        // Create the first window
        cv::namedWindow(grey_image_window_title, cv::WINDOW_AUTOSIZE);
                
        // Display the first window
        // Replace rgb_image by grey_image
        cv::imshow(grey_image_window_title, rgb_image);
        
        
		/**********************************************************************/
		/* Apply a 3x3 Gaussian filter with sigma 0.5 to reduce noise         */
		/**********************************************************************/
		
		// Write your own code here
		
		
		/**********************************************************************/
		/* Gradient filter                                                    */
		/**********************************************************************/
		
		// Write your own code here to:
        
        // 1) Apply the Scharr filter on gaussain_image along the X-axis
        cv::Mat scharr_x;
        
        // 2) Compute the absolute value of the gradient along the X-axis
        
        // 3) Apply the Scharr filter on gaussain_image along the Y-axis
        cv::Mat scharr_y;
        
        // 4) Compute the absolute value of the gradient along the Y-axis

		// 5) Combined scharr_x and scharr_y together so that
		// scharr_image(x,y) = 0.5 * |scharr_x(x,y)| + 0.5 * |scharr_y(x,y)|



        // Create the second window
        cv::namedWindow(filtered_image_window_title, cv::WINDOW_AUTOSIZE);
                
        // Display the second window
        // Replace rgb_image by scharr_image
        cv::imshow(filtered_image_window_title, rgb_image);


		/**********************************************************************/
		/* Threshold filter                                                   */
		/**********************************************************************/
        
        // Write your own code here
        



        // Create the third window
        cv::namedWindow(edge_image_window_title, cv::WINDOW_AUTOSIZE);
                
        // Display the third window
        // Replace rgb_image by edge_image
        cv::imshow(edge_image_window_title, rgb_image);
        
        // Wait for the user to press 'q' or 'Escape' (27 in ASCII code
        int key;
        do
        {
            key = cv::waitKey(0);
        }
        while (key != 'q' && key != 27);

		/**********************************************************************/
		/* Write the output                                                   */
		/**********************************************************************/
		
		// Write your own code here
        



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

