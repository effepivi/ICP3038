/**
******************************************************************************
*
*	@file		writeDataToConsole.cpp
*
*	@brief		Test program to write some data into the console (terminal).
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


#include <string> // Class to store string (text)


int main()
{
    // Let's create some variables of various types
    int a = -10;
    short b =  10;
    char c = 110; // 110 is the ASCII code of 'n'
    
    char d[] = "Some text";
    std::string e("Some more text");
    
    int f[5] = {0, 1, 2, 3, 4};
    
    // Now let's print all of them
    std::cout << a << " " <<
                 b << " " <<
                 c << " " <<
                 d << " " <<
                 e << " " <<
                 f;
    
    std::cout << std::endl; // New line
    
    // You should have seen something like:
    // -10 10 n Some text Some more text 0x7fff5d1de2d0
    
    // To print the values stored in f rather than the address, we need a for loop
    for (unsigned i = 0; i < 5; i++)
    {
        std::cout << f[i] << " ";
    }
    std::cout << std::endl;

    // You should have seen something like:
    // 0 1 2 3 4



    // Each main function should return an error code
    // 0 means no error
    return (0);
}
