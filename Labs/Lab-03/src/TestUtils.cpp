/**
******************************************************************************
*
*	@file		TestUtils.cpp
*
*	@brief		Test program to check Utils.h.
*
*	@version	1.0
*
*	@date		14/10/2018
*
*	@author		Your name
*
*
******************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <iostream>

#include "utils.h"


int main()
{
    // Test each function with different data types
    std::cout << getMinValue(1, 2) << std::endl;
    std::cout << getMinValue<int>(1, 2) << std::endl;

    // std::cout << getMinValue(1, 2.0) << std::endl; <= int+double does not work

    std::cout << getMinValue(3.5, 2.5) << std::endl;
    std::cout << getMinValue<double>(3.5, 2.5) << std::endl;

    // Will show '2' if not template function (will use the 'int' implementation that is provided by default)
    // Will show '2.5' when the template function is implemented
    std::cout << getMaxValue(1.0, 2.5) << std::endl;


    // Test other functions here with different types

    return (0);
}
