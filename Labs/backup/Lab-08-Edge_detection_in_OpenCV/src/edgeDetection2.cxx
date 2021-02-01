/**
********************************************************************************
*
*   @file       edgeDetection2.cxx
*
*   @brief      A more user friendly program using OpenCV to detect edges.
*
*   @version    1.0
*
*   @date       08/02/2016
*
*   @author     Franck Vidal
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
cv::Mat g_display_image;        
cv::Mat g_scharr_image;
cv::Mat g_edge_image;

std::string g_image_window_title("Edge detection");
        
int g_slider_count(256);
int g_slider_position(g_slider_count / 2);
int N = 3;
int k = 10;


//******************************************************************************
//    Function declaration
//******************************************************************************
void callback(int, void*);


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

		// Write your own code here to
		// Create the displayed image

		// Write your own code here to
        // Create the displayed image

	    // Create the window
		cv::namedWindow(g_image_window_title, cv::WINDOW_AUTOSIZE);

       
		/**********************************************************************/
		/* Convert the RGB data to greyscale                                  */
		/**********************************************************************/
		


     
		// Create the ROI in the target image
        cv::Mat targetROI = g_display_image(cv::Rect(0, 0, grey_image.cols, grey_image.rows));

		// Copy the source in the target
        grey_image.copyTo(targetROI);

        
		/**********************************************************************/
		/* Apply a 3x3 Gaussian filter with sigma 0.5 to reduce noise         */
		/**********************************************************************/
        
        
        
        
        
        /**********************************************************************/
		/* Gradient filter                                                    */
		/**********************************************************************/
        


		// Copy the result
        targetROI = g_display_image(cv::Rect(g_scharr_image.cols * 1 + 1 * k, 0, g_scharr_image.cols, g_scharr_image.rows));
        g_scharr_image.copyTo(targetROI);
        
      
		/**********************************************************************/
		/* Create the slider                                                  */
		/**********************************************************************/
		
		// Write your own code here to
      	// Create the slider
 
          

		/**********************************************************************/
		/* Threshold filter                                                   */
		/**********************************************************************/
		callback(0, 0);
		

		/**********************************************************************/
		/* Event loop                                                         */
		/**********************************************************************/
       
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

		// Write your own code here to
		// Write the image



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


//-----------------------
void callback(int, void*)
//-----------------------
{
	/**********************************************************************/
	/* Threshold                                                          */
	/**********************************************************************/
    double min, max;
    cv::minMaxLoc(g_scharr_image, &min, &max);
    
	// Linear interpolation    
	double threshold(min + (max - min) * (double(g_slider_position) / double(g_slider_count)));
	
			
	// Write your own code here to
	// Find edges using a threshold filter


	// Write your own code here to
	// Copy the result
        
	// Write your own code here to
    // Display the window
}

