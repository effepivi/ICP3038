/**
******************************************************************************
*
*	@file		TestVector.cpp
*
*	@brief		Test program to use the vector implementation of the STL.
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
#include <iostream> // To use cout
#include <cstdlib>  // To use rand(), etc.
#include <ctime>    // To use time()


//## 1  -- add header file  <vector> here to use the STL vector class
//## 5a -- add header file <algorithm> here to use std::copy
//## 5b -- add header file <iterator> here to use the ostream_iterator needed by std::copy
//## 7a -- add header <algorithm> file here to use std::min_element and std::max_element
//## 8a -- add header <numeric> file here to use std::accumulate


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
    //	Start of ineffective C++ code
    //**************************************************************************
    
    // Create an array of fifty elements
    double* p_random_number_set = new double[50];
    
    // Initialise them to 50 random numbers between 0 and 1
    for (unsigned int i(0); i < 50; ++i)
    {
        p_random_number_set[i] = randd();
    }

    // Display every element
    for (unsigned int i(0); i < 50; ++i)
    {
        cout << p_random_number_set[i] << "\t";
    }
    cout << endl << endl;
    
    // Display every element in reverse order
    for (unsigned int i(50); i > 0; --i)
    {
        cout << p_random_number_set[i - 1] << "\t";
    }
    cout << endl << endl;
    
    // Create a temporary array
    double* p_temp = new double[40];
    
    
    // Copy 50 - 10 elements in p_temp
    for (unsigned int i(0); i < 40; ++i)
    {
        p_temp[i] = p_random_number_set[i];
    }
    
    // Release old array
    delete [] p_random_number_set;
    
    // Copy pointers
    p_random_number_set = p_temp;

    // Release memory
    delete [] p_random_number_set;
    
    
    //**************************************************************************
    //	End of ineffective C++ code
    //**************************************************************************


    // Not easy to add new elements to the array
    // Not easy to remove exisiting elements from the array
    
    // Replace the code above by better C++ code using the `vector' class from STL
    
    //## 2a - Create an empty vector of double precision floating point numbers
    
    
    //## 2b -- Check the size of the vector (how many elements stored in the array)
    
    
    //## 2c -- Add 50 random numbers between 0 and 1
    // Hint, use the push_back method
    
    
    //## 2d -- Check the size of the vector. Yes, same as 2b, just to be sure it is 50.


    //## 3a -- Display every element of the vector using the same method as in C (and cout <<)
    
    
    
    //## 3b -- Display every element of the vector using a const_iterator, a for loop, and cout <<


    //## 4 -- In the previous for loop, replace .begin() by .rbegin(), and .end() by .rend()
    // Also replace const_iterator by const_reverse_iterator
    

    
    //## 5c -- Instead of the for loop, use std::copy to display every element of the vector
    
    
    //## 6 -- Remove the last N elements of the vector, with N a random number equal to 10*randd()
    
    
    //## 7a -- display the smallest contained in the vector using std::min_element
    
    
    //## 7b -- display the largest contained in the vector using std::max_element
    
    
    //## 8a -- get the sum of all the values in the vector using std::accumulate()


    //## 8b -- using the sum value you just computed, display the average value (you will need to use the method std::vector<T>::size())

    

    return (0);
}
