/**
******************************************************************************
*
*	@file		TestUtils.cpp
*
*	@brief		Test program to check Utils.h.
*
*	@version	1.0
*
*	@date		20/10/2015
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

    
    return (0);
}
