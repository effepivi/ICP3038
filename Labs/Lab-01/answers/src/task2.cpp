/**
********************************************************************************
*
*	@file		task2.cpp
*
*	@brief		Add floating point numbers passed as arguments.
*
*	@version	1.0
*
*	@date		06/10/2015
*
*	@author		Franck P. Vidal (f.vidal@bangor.ac.uk)
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include<iostream>
#include <cstdlib>


//******************************************************************************
//	namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//	Implementation
//******************************************************************************
int main(int argc, char** argv)
{
    int return_code(0);
    
    // Number of floats
    unsigned int number_of_floats(argc - 1);
    
    // Even number of arguments
    bool even_number_of_floats((number_of_floats % 2) == 0);
    
    // At least a float has been passed to the program
    if (number_of_floats > 0)
    {
        // An even number of floats has been passed to the program
        if (even_number_of_floats)
        {
            char* p_end;
            for (unsigned int i(0); i < number_of_floats; i += 2)
            {
                float a(strtod(argv[i + 1], &p_end));
                float b(strtod(argv[i + 2], &p_end));
            
                std::cout << a << " + " << b << " = " << a + b << std::endl;
            }
        }
        // An odd number of floats has been passed to the program
        else
        {
            // There is an error, set the error code
            return_code = 2;
        
            // Print an error message
            std::cerr << "Did not pass an even number of floats to the program!" << std::endl;
        }
    }
    // No float has been passed to the program
    else
    {
        // There is an error, set the error code
        return_code = 1;
    
        // Print an error message
        std::cerr << "Did not pass any float to the program!" << std::endl;
    }
    
    // Exit code
    return (return_code);
}
