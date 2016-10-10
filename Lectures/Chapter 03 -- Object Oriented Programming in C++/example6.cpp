/*
********************************************************************************
*
*	@file		value_vs_reference.cxx
*
*	@brief		Illustration of passing parameters by value and by reference.
*
*	@version	1.0
*
*	@date		08 Mar 2012
*
*	@author		Dr Franck P. Vidal (e-mail: f.vidal@bangor.ac.uk)
*
*	@section	Institution
*			
*	School of Computer Science
*	Bangor University
*	Dean Street
*	Bangor LL57 1UT
*	Gwynydd
*	United Kingdom
*
********************************************************************************
*/


#include <iostream>

// By value
float Test1(const float aValue)
{
	aValue = aValue * aValue;
	return aValue;
}

// By reference
float Test2(const float& aValue)
{
	aValue = aValue * aValue;
	return aValue;
}


// By pointer
float Test3(const float* aValue)
{
	*aValue = *aValue * *aValue;
	return *aValue;
}


int main()
{
	std::cout << "************************* passing parameters by value *************************" << std::endl;

	float a1 = 2;
	std::cout << "a1 = " << a1 << std::endl;

	float temp1 = Test1(a1);
	std::cout << "temp1 = " << temp1 << std::endl;

	std::cout << "a1 = " << a1 << std::endl << std::endl << std::endl;


	std::cout << "*********************** passing parameters by reference ***********************" << std::endl;

	float a2 = 2;
	std::cout << "a2 = " << a2 << std::endl;

	float temp2 = Test2(a2);
	std::cout << "temp2 = " << temp2 << std::endl;

	std::cout << "a2 = " << a2 << std::endl << std::endl;

	std::cout << "*********************** passing parameters by pointer ***********************" << std::endl;

	float a3 = 2;
	std::cout << "a3 = " << a3 << std::endl;

	float temp3 = Test3(&a3);
	std::cout << "temp3 = " << temp3 << std::endl;

	std::cout << "a3 = " << a3 << std::endl;

	return 0;
}