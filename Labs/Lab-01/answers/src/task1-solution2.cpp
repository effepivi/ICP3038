/**
********************************************************************************
*
*	@file		task1-solution2.cpp
*
*	@brief		Add two integer numbers read from the standard input. 
*               Stops reading after encountering the end of file (or Ctrl-D)
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


//******************************************************************************
//	namespace
//******************************************************************************
using namespace std;


//******************************************************************************
//	Implementation
//******************************************************************************
int main()
{
    // Stop when Ctrl-D is reach (end of file)
    while (!std::cin.eof())
    {
        int a, b;
        std::cout << "Enter two integer numbers:" << std::endl;
        std::cin >> a >> b;
        std::cout << a << " + " << b << " = " << a + b << std::endl;
    }
    
    // Exit code
    return (0);
}
