/**
********************************************************************************
*
*	@file		task4.cpp
*
*	@brief		Sort an array of floating point numbers using the Bubble sort.
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
//	Global variables
//******************************************************************************


//******************************************************************************
//	Function declaration
//******************************************************************************
void swap(int& i, int& j);
void swap(int* i, int* j);
string suffix(int i);
void bubbleSort(float* apArray, int anArraySize);


//******************************************************************************
//	Implementation
//******************************************************************************
int main()
{
    // Number of floating point numbers
    int N(0);
    
    cout << "How many number do you want to sort?\t" << endl;
    cin >> N;
    if (N < 0)
    {
        cerr << "No integer to read" << endl;
        return 1;
    }
    
    // Allocate the memory
    float* p_array(new float[N]);
    if (!p_array)
    {
        cerr << "Out of memory" << endl;
        return 1;
    }
    
    // Read N floating point numbers from the standard input (e.g. command line)
    for (int i(0); i < N; ++i)
    {
        cout << "Type the " << i + 1 << suffix(i + 1) << " real number" << endl;
        cin >> p_array[i];
    }
    cout << endl;
    
    // Sort the array
    bubbleSort(p_array, N);
    
    // Display the array sorted using the bubble sort
    for (int i(0); i < N; ++i)
    {
        cout << p_array[i] << endl;
    }
    
    // Release the memory
    delete [] p_array;
    
    // Exit code
    return (0);
}


//-----------------------
void swap(int& i, int& j)
//-----------------------
{
    int temp(i);
    i = j;
    j = temp;
}


//-----------------------
void swap(int* i, int* j)
//-----------------------
{
    int temp(*i);
    *i = *j;
    *j = temp;
}


//------------------
string suffix(int i)
//------------------
{
    string value;
    
    switch (i)
    {
    case 1:
        value = "st";
        break;

    case 2:
        value = "nd";
        break;

    case 3:
        value = "rd";
        break;

    default:
        value = "th";
        break;
    }
    
    return (value);
}


//------------------------------
void bubbleSort(float* apArray,
                int anArraySize)
//------------------------------
{
    // Flag used to keep track of changes in the last iteration
    // It is initialsed to true to enter the while loop
    bool has_changed(true);
    
    // The array is not sorted
    while (has_changed)
    {
        // No change so far
        has_changed = false;
    
        // Process each pair
        for (int i(0); i < (anArraySize - 1); ++i)
        {
            // The two successive elements are not sorted
            if (apArray[i] > apArray[i + 1])
            {
                // Swap the two elements
                swap(apArray[i], apArray[i + 1]);
            
                // There has been a change
                has_changed = true;
            }
        }
    }
}
