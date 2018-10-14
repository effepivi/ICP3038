#ifndef UTILS_H
#define UTILS_H


/**
******************************************************************************
*
*	@file		utils.h
*
*	@brief		Used to get familiar with template functions.
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


// Modify the code below to use template functions
// for example "int getMinValue(int i, int j);"
// becomes

//int getMinValue(int i, int j);
template <typename T> T getMinValue(T i, T j);


int getMaxValue(int i, int j);
void swap(int& i, int& j);
void sort(int& i, int& j);
int power(int i, unsigned int j); // Return i^j   (j is always an unsigned int)
double getAverage(int i, int j); // Always returns a double




#include "utils.inl"

#endif
