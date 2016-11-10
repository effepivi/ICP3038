/**
******************************************************************************
*
*	@file		writeDataToASCIIFile.cpp
*
*	@brief		Test program to write some data into an ASCII file.
*
*	@version	1.0
*
*	@date		10/11/2016
*
*	@author		Franck Vidal (f.vidal@bangor.ac.uk)
*
*
******************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <iostream> // We need this header to use "cout/cerr"
                    // "cout" is the command used to write into the console

#include <fstream> // We need this header to save the data in files

#include <string> // Class to store string (text)


int main(int argc, char** argv)
{
    // No file name as parameter
    if (argc != 2)
    {
        // Print an error message
        std::cerr << "Usage: " << argv[0] << " output_file.txt" << std::endl;
    
        // Return an error code
        return 1;
    }
    
    // Get the file name
    std::string file_name(argv[1]);
    
    // Declare the output file stream and open it as an ASCII file
    std::ofstream output_file(file_name.data());
    
    // The file is not open
    if (!output_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << file_name << " in writing mode" << std::endl;
    
        // Return an error code
        return 1;
    }
    
    // Let's create some variables of various types
    int a = -10;
    short b =  10;
    char c = 110; // 110 is the ASCII code of 'n'
    
    char d[] = "Some text";
    std::string e("Some more text");
    
    int f[5] = {0, 1, 2, 3, 4};
    
    // Now let's print all of them on the same line
    output_file << a << " " <<
                 b << " " <<
                 c << " " <<
                 d << " " <<
                 e << " " <<
                 f;
    
    output_file << std::endl; // New line
    output_file << std::endl; // New line
    
    // Now let's print all of them on different lines
    output_file << a << std::endl <<
                 b << std::endl <<
                 c << std::endl <<
                 d << std::endl <<
                 e << std::endl <<
                 f << std::endl;
    
    // To print the values stored in f rather than the address, we need a for loop
    for (unsigned i = 0; i < 5; i++)
    {
        output_file << f[i] << " ";
    }
    output_file << std::endl;

    // Close the file (optional as it is done in the destructor if needed)
    output_file.close();

    // Each main function should return an error code
    // 0 means no error
    return (0);
}
