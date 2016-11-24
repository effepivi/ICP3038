/**
********************************************************************************
*
*	@file		test_my_vector.cpp
*
*	@brief		Test our class MyVector.
*
*	@version	1.0
*
*	@date		17/11/2015
*
*	@author		Your name
*
*
********************************************************************************
*/


//******************************************************************************
//	Include
//******************************************************************************
#include <iostream>
#include <exception>
#include <string>

#include "MyVector.h"


//--------
int main()
//--------
{
    try
    {
        // Create four vectors and load corresponding files
        // Note to students: YOU MAY HAVE TO UPDATE THE PATH
        MyVector y("../data/y.mat");
        MyVector y_quadriple("../data/y_quadriple.mat");
        MyVector y_noise("../data/y_noise.mat");
        MyVector y_negative("../data/y_negative.mat");
    
        // Print some statistics (to test your methods check the alues against the ones given in the lab script)
        std::cout << "Y" << std::endl;
        y.printStatistics(std::cout);
        std::cout << std::endl;
    
        std::cout << "Y_quadriple" << std::endl;
        y_quadriple.printStatistics(std::cout);
        std::cout << std::endl;
    
        std::cout << "Y_noise" << std::endl;
        y_noise.printStatistics(std::cout);
        std::cout << std::endl;
    
        std::cout << "Y_negative" << std::endl;
        y_negative.printStatistics(std::cout);
        std::cout << std::endl;
    
        // Create two similar vectors
        MyVector temp1(y + 1.22222);
        temp1 += 2.11111;
    
        MyVector temp2(y + 3.33333);
    
        // They are similar
        if (temp1 == temp2)
        {
            std::cout << "temp1 and temp2 are the same" << std::endl;
        }
        // They are different
        else
        {
            std::cout << "temp1 and temp2 are different" << std::endl;
        
            // Access every pair of corresponding elements
            for (unsigned int i(0); i < y.getSize(); ++i)
            {
                // We have overwritten operator() and operator[]
                // We can use them to access an element
                // The elements are different
                if (temp1(i) != temp2[i])
                {
                    // Print the index and the elements
                    std::cout << i << "\t" << temp1(i) << " != " << temp2[i] << std::endl;
                }
            }
        }
        std::cout << std::endl;
    
        // Create a new vector similar to y_quadriple
        MyVector temp3(y + y + y + y);
    
        // They are similar
        if (temp3 == y_quadriple)
        {
            std::cout << "temp3 and y_quadriple are the same" << std::endl;
        }
        // They are different
        else
        {
            std::cout << "temp3 and y_quadriple are different" << std::endl;
        
            // Access every pair of corresponding elements
            for (unsigned int i(0); i < y_quadriple.getSize(); ++i)
            {
                // We have overwritten operator() and operator[]
                // We can use them to access an element
                // The elements are different
                if (temp3(i) != y_quadriple[i])
                {
                    // Print the index and the elements
                    std::cout << i << "\t" << temp3(i) << " != " << y_quadriple[i] << std::endl;
                }
            }
        }
        std::cout << std::endl;
    
        // Compute the SAE between vectors
        // (to test your method check the alues against the ones given in the lab script)
        std::cout << "SAE(Y, Y)"           << y.SAE(y)           << std::endl;
        std::cout << "SAE(Y, Y_quadriple)" << y.SAE(y_quadriple) << std::endl;
        std::cout << "SAE(Y, Y_noise)"     << y.SAE(y_noise)     << std::endl;
        std::cout << "SAE(Y, Y_negative)"  << y.SAE(y_negative)  << std::endl;
        std::cout << std::endl;

        // Compute the NCC between vectors
        // (to test your method check the alues against the ones given in the lab script)
        std::cout << "NCC(Y, Y)"           << y.NCC(y)           << y.NCC(y)           * 100.0 << std::endl;
        std::cout << "NCC(Y, Y_quadriple)" << y.NCC(y_quadriple) << y.NCC(y_quadriple) * 100.0 << std::endl;
        std::cout << "NCC(Y, Y_noise)"     << y.NCC(y_noise)     << y.NCC(y_noise)     * 100.0 << std::endl;
        std::cout << "NCC(Y, Y_negative)"  << y.NCC(y_negative)  << y.NCC(y_negative)  * 100.0 << std::endl;
        std::cout << std::endl;
    }
    // There was an error
    catch (const std::exception& error)
    {
        std::cerr << "ERROR:\t" << error.what() << std::endl;
    }
    catch (const std::string& error)
    {
        std::cerr << "ERROR:\t" << error << std::endl;
    }
    catch (const char* error)
    {
        std::cerr << "ERROR:\t" << error << std::endl;
    }
    catch (...)
    {
        std::cerr << "ERROR:\tUnknown" << std::endl;
    }
    
    return 0;
}

