/**
******************************************************************************
*
*	@file		readDataFromASCIIFileConsole.cpp
*
*	@brief		Test program to read some data from an ASCII file.
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
#include <iostream> // We need this header to use "cout"
                    // "cout" is the command used to write into the console

#include <fstream> // We need this header to read/save the data from/to files

#include <string> // Class to store string (text)

#include <cstdlib> // For random numbers, and exit()

#include <algorithm> // For min/max

#include <vector> // To store the data from the file in an array

#include <sstream> // To parse a string and extract the doubles from it


// Returns a random value between aMinValue and aMaxValue
double random(double aMinValue, double aMaxValue);

// Create a temporary file
void createTempFile(const char* aFileName);

// Read the file
void readTempFileMethod1(const char* aFileName);
void readTempFileMethod2(const char* aFileName);
void readTempFileMethod2_improved(const char* aFileName);
void readTempFileMethod3(const char* aFileName);
void readTempFileMethod3_improved(const char* aFileName);
std::vector<double> readTempFileMethod4(const char* aFileName); // Store the data in a vector


int main()
{
    //============================================================
    // Create a temporary file
    //============================================================
    std::cout << "Create a temporary file" << std::endl;
    createTempFile("temp.txt");
    std::cout << std::endl;
    
    
    //============================================================
    // Read the new file
    //============================================================
    std::cout << "Read the file using Method 1" << std::endl;
    readTempFileMethod1("temp.txt");
    std::cout << std::endl;

    std::cout << "Read the file using Method 2" << std::endl;
    readTempFileMethod2("temp.txt");
    std::cout << "The last element has been printed twice." << std::endl << std::endl;

    std::cout << "Read the file using Method 2 - improved" << std::endl;
    readTempFileMethod2_improved("temp.txt");
    std::cout << "With an extra test, the last element has been printed only once." << std::endl << std::endl;

    std::cout << "Read the file using Method 3" << std::endl;
    readTempFileMethod3("temp.txt");
    std::cout << "The last element has been printed twice." << std::endl << std::endl;


    std::cout << "Read the file using Method 3 - improved" << std::endl;
    readTempFileMethod3_improved("temp.txt");
    std::cout << "With an extra test, the last element has been printed only once." << std::endl << std::endl;
    
    std::cout << "Read the file using Method 4" << std::endl;
    std::vector<double> result = readTempFileMethod4("temp.txt");
    
    for (std::vector<double>::const_iterator ite(result.begin());
            ite != result.end();
            ++ite)
    {
        std::cout << *ite << " ";
    }
    std::cout << "       // From the vector[i]" << std::endl;




    return (0);
}


//-----------------------------------------------
double random(double aMinValue, double aMaxValue)
//-----------------------------------------------
{
    // Make sure the values are ordered
    double min_value = std::min(aMinValue, aMaxValue);
    double max_value = std::max(aMinValue, aMaxValue);
    
    return (min_value + (max_value - min_value) * double(rand()) / RAND_MAX);
}


//----------------------------------------
void createTempFile(const char* aFileName)
//----------------------------------------
{
    // Open a temporary file to store the data
    std::ofstream output_file("temp.txt");
    
    // The file is not open
    if (!output_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    // Create an array of 10 double precision floating point numbers
    double p_array[10];
    
    // Initialise it with random numbers
    for (unsigned int i = 0; i < 10; ++i)
    {
        p_array[i] = random(-5, 5);

        // Show the number in the console
        std::cout << p_array[i] << " ";
    
        // Store the number in the output file
        output_file << p_array[i] << " ";
    }
    std::cout << std::endl;
    
    // Close the file
    output_file.close();
}


//---------------------------------------------
void readTempFileMethod1(const char* aFileName)
//---------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    double temp_value = 0.0;
    while (input_file >> temp_value)
    {
        std::cout << temp_value << " ";
    }
    
    // Go to the new line
    std::cout << std::endl;
}


//---------------------------------------------
void readTempFileMethod2(const char* aFileName)
//---------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    double temp_value = 0.0;
    while (input_file.good())
    {
        input_file >> temp_value;
        std::cout << temp_value << " ";
    }
    
    // Go to the new line
    std::cout << std::endl;
}


//------------------------------------------------------
void readTempFileMethod2_improved(const char* aFileName)
//------------------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    double temp_value = 0.0;

    while (input_file.good())
    {
        input_file >> temp_value;
    
        if (input_file.good())
        {
            std::cout << temp_value << " ";
        }
    }
    
    // Go to the new line
    std::cout << std::endl;
}


//---------------------------------------------
void readTempFileMethod3(const char* aFileName)
//---------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    double temp_value = 0.0;
    while (!input_file.eof())
    {
        input_file >> temp_value;
        std::cout << temp_value << " ";
    }
    
    // Go to the new line
    std::cout << std::endl;
}


//------------------------------------------------------
void readTempFileMethod3_improved(const char* aFileName)
//------------------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    double temp_value = 0.0;
    while (!input_file.eof())
    {
        input_file >> temp_value;
    
        if (!input_file.eof())
        {
            std::cout << temp_value << " ";
        }
    }
    
    // Go to the new line
    std::cout << std::endl;
}


//------------------------------------------------------------
std::vector<double> readTempFileMethod4(const char* aFileName)
//------------------------------------------------------------
{
 // Open the file to read the data
    std::ifstream input_file("temp.txt");
    
    // The file is not open
    if (!input_file.is_open())
    {
        // Print an error message
        std::cerr << "Cannot open " << "temp.txt" << " in writing mode" << std::endl;
    
        // Return an error code
        exit(EXIT_FAILURE);
    }

    // Create the string that can contain many many characters
    char p_line[1000000];

    // Read the first line
    input_file.getline (p_line,1000000);

    // Display the string
    std::cout << p_line << "       // From the char*" << std::endl;

    // Convert the string into a stream
    std::stringstream line_as_stream;
    line_as_stream << p_line;
    
    std::vector<double> p_array;
    double temp_value = 0.0;
    while (line_as_stream >> temp_value)
    {
        input_file >> temp_value;
        p_array.push_back(temp_value);
    }

    return (p_array);
}


