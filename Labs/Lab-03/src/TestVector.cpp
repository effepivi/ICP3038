/**
******************************************************************************
*
*	@file		TestVector.cpp
*
*	@brief		Test program to use the vector implementation of the STL.
*
*	@version	1.0
*
*	@date		17/10/2016
*
*	@author		Your name
*
*
******************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <iostream> // To use cout
#include <cstdlib>  // To use rand(), etc.

//## 1 -- add header file here to use the STL vector class
//## 5a -- add header file here to use std::copy
//## 5b -- add header file here to use the ostream_iterator needed by std::copy
//## 7a -- add header file here to use std::min_element and std::max_element
//## 8a -- add header file here to use std::accumulate


//******************************************************************************
//	Name space
//******************************************************************************
using namespace std;


//-------------------
inline double randd()
//-------------------
{
    return (double(rand()) / (double(RAND_MAX) + 1));
}


int main()
{
    // Initialise the random number generator
    srand(time(0));
    
    
    //**************************************************************************
    //	Start of C code
    //**************************************************************************
    
    // Create an array of fifty random numbers between 0 and 1
    double p_random_number_set[50];
    for (unsigned int i(0); i < 50; ++i)
    {
        p_random_number_set[i] = randd();
    }

    for (unsigned int i(0); i < 50; ++i)
    {
        cout << p_random_number_set[i] << "\t";
    }
    cout << endl << endl;

    //**************************************************************************
    //	End of C code
    //**************************************************************************


    // Not easy to add new elements to the array
    // Not easy to remove exisiting elements from the array
    
    // Replace the C code above by C++ code using the `vector' class from STL
    
    //## 2a -- Create a vector of fifty double precision floating point numbers
    
    //## 2b -- Replace each element of the vector by random numbers between 0 and 1
    // Hint, use a for loop with an iterator
    
    //## 3 -- Display every element of the vector using a const_iterator, a for loop, and std::cout <<


    //## 4 -- In the for loop you just wrote, replace .begin() by .rbegin(), and .end() by .rend()

    
    //## 5c -- Instead of the for loop, use std::copy to display every element of the vector
    
    //## 6 -- Remove the last N elements of the vector, with N a random number equal to 10*randd()
    
    //## 7b -- display the smallest contained in the vector using std::min_element
    //## 7b -- display the largest contained in the vector using std::max_element
    
    //## 8b -- get the sum of all the values in the vector using std::accumulate()

    //## 8c -- using the sum value you just computed, display the average value (you will need to use the method std::vector<T>::size())
    
    return (0);
}
