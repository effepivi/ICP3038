/**
******************************************************************************
*
*	@file		readDataFromConsole.cpp
*
*	@brief		Test program to read some data from the console (terminal).
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
    int a;
    short b;
    char c;
    char d[1024];
    std::string e;
    int f[5];
    
    // Print a prompt message
    std::cout << "Type a signed int:" << std::endl;
    std::cin >> a;
    std::cout << "The int you typed was: " << a << std::endl << std::endl;
    
    // Print a prompt message
    std::cout << "Type a signed short:" << std::endl;
    std::cin >> b;
    std::cout << "The short you typed was: " << b << std::endl << std::endl;
    
    // Print a prompt message
    std::cout << "Type a signed char:" << std::endl;
    std::cin >> c;
    std::cout << "The char you typed was: " << c << std::endl << std::endl;
    
    // Print a prompt message
    std::cout << "Type a string:" << std::endl;
    std::cin >> d;
    std::cout << "The string you typed was: " << d << std::endl << std::endl;
    
    // Print a prompt message
    std::cout << "Type a string:" << std::endl;
    std::cin >> e;
    std::cout << "The string you typed was: " << e << std::endl << std::endl;
    
    // Print a prompt message
    std::cout << "Type five signed int separated by a ' ' character:" << std::endl;
    std::cin >> f[0] >> f[1] >> f[2] >> f[3] >> f[4];
    std::cout << "The ints you typed were: " << d << std::endl << std::endl;
    
    for (unsigned int i = 0; i < 5; i++)
    {
        std::cout << f[i] << " ";
    }
    std::cout << std::endl;
    
    // Each main function should return an error code
    // 0 means no error
    return (0);
}
