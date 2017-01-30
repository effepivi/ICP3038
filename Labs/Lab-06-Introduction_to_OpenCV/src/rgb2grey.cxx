/**
********************************************************************************
*
*	@file		rgb2grey.cxx
*
*	@brief		A program to convert a RGB image in a greyscale image using OpenCV.
*
*	@version	1.0
*
*	@date		29/01/2016
*
*	@author		Franck Vidal
*
*
********************************************************************************
*/


//******************************************************************************
//	Includes
//******************************************************************************
#include <exception> // Header for catching exceptions
#include <iostream>  // Header to display text in the console
#include <opencv2/opencv.hpp> // Main OpenCV header


//******************************************************************************
//	Namespaces
//******************************************************************************
using namespace std;


//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    try
    {
        // No file to display
        // No file to save
        if (argc != 3)
        {
            // Create an error message
            std::string error_message;
            error_message  = "usage: ";
            error_message += argv[0];
            error_message += " <input_image> <output_image>";

            // Throw an error
            throw error_message;
        }

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

