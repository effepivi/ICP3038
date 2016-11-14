/**
********************************************************************************
*
*	@file		MyVector.cpp
*
*	@brief		Class used to manage a 1D vector of single-precision 
*               floating point numbers. The class is used to illustrate 
*               how to compare two vectors with each other. Care is given 
*               to handle numerical inaccuracy.
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
#include <fstream>
#include <sstream>
#include <cmath>

#include "MyVector.h"


const float EPSILON = 1.0e-6;


//------------------
MyVector::MyVector()
//------------------
{}


//------------------------------------------
MyVector::MyVector(const MyVector& aVector):
//------------------------------------------
        m_data(aVector.m_data)
//------------------------------------------
{}


//----------------------------------------------------
MyVector::MyVector(const std::vector<float>& aVector):
//----------------------------------------------------
        m_data(aVector)
//----------------------------------------------------
{}


//---------------------------------------
MyVector::MyVector(const char* aFileName)
//---------------------------------------
{
    // Load the file
    loadASCII(aFileName);
}


//----------------------------------------------
MyVector::MyVector(const std::string& aFileName)
//----------------------------------------------
{
    // Load the file
    loadASCII(aFileName);
}


//---------------------------------------------
void MyVector::loadASCII(const char* aFileName)
//---------------------------------------------
{
    // Open the file
    std::ifstream file_data(aFileName);
    
    // The file is not open
    if (!file_data.is_open())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "Cannot open the file \"" << aFileName << "\". ";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;

        // Throw an error
        throw error_message.str();
    }
    
    // Empty the vector
    m_data.clear();
    
    // Load the file
    float temp;
    while (file_data >> temp)
    {
        m_data.push_back(temp);
    }
}


//----------------------------------------------------
void MyVector::loadASCII(const std::string& aFileName)
//----------------------------------------------------
{
    // Load the file
    loadASCII(aFileName.data());
}


//----------------------------------------------------------------
void MyVector::printStatistics(std::ostream& anOutputStream) const
//----------------------------------------------------------------
{
    anOutputStream << "size:\t" << getSize() << std::endl;
    anOutputStream << "min:\t" << getMinValue() << std::endl;
    anOutputStream << "max:\t" << getMaxValue() << std::endl;
    anOutputStream << "sum:\t" << getSum() << std::endl;
    anOutputStream << "average:\t" << getAverage() << std::endl;
    anOutputStream << "variance:\t" << getVariance() << std::endl;
    anOutputStream << "standard deviation:\t" << getStandardDeviation() << std::endl;
}


//------------------------------------
unsigned int MyVector::getSize() const
//------------------------------------
{
    return (m_data.size());
}


//----------------------------------------------------
MyVector& MyVector::operator=(const MyVector& aVector)
//----------------------------------------------------
{
    m_data = aVector.m_data;

    return (*this);
}


//----------------------------------------------
float MyVector::operator[](unsigned int i) const
//----------------------------------------------
{
    // Invalid index
    if (i >= getSize())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "Try to access Element " << i << " of an array with " << getSize() << " elements.";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;

        // Throw an error
        throw error_message.str();
    }
    
    return (m_data[i]);
}

  
//----------------------------------------------
float MyVector::operator()(unsigned int i) const
//----------------------------------------------
{
    // Invalid index
    if (i >= getSize())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "Try to access Element " << i << " of an array with " << getSize() << " elements.";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;

        // Throw an error
        throw error_message.str();
    }
    
    return (m_data[i]);
}

  
//----------------------------------------------
MyVector MyVector::operator+(float aValue) const
//----------------------------------------------
{
    // Create a new vector from the current vector
    std::vector<float> p_temp(m_data);
    
    // Add aValue to every element
    for (std::vector<float>::iterator ite(p_temp.begin());
            ite != p_temp.end();
            ++ite)
    {
        *ite += aValue;
    }
    
    // Return the new vector
    return (MyVector(p_temp));
}


//------------------------------------------
MyVector& MyVector::operator+=(float aValue)
//------------------------------------------
{
    // Add aValue to every element
    for (std::vector<float>::iterator ite(m_data.begin());
            ite != m_data.end();
            ++ite)
    {
        *ite += aValue;
    }
    
    // Return the updated vector
    return (*this);
}


//---------------------------------------------------------
MyVector MyVector::operator+(const MyVector& aVector) const
//---------------------------------------------------------
{
    // The two vectors have different sizes
    if (getSize() != aVector.getSize())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "The two vectors have different sizes (" << getSize() << " and " << aVector.getSize() << ").";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;

        // Throw an error
        throw error_message.str();
    }
    
    // Create a new vector from the current vector
    std::vector<float> p_temp(m_data);

    // Initialise iterators
    std::vector<float>::const_iterator ite_input(aVector.m_data.begin());
    std::vector<float>::iterator ite_output(p_temp.begin());
    
    // Element-wise sum
    while (ite_input != aVector.m_data.end() && ite_output != p_temp.end())
    {
        *ite_output++ += *ite_input++;
    }
    
    // Return the new vector
    return (MyVector(p_temp));
}


//-----------------------------------------------------
MyVector& MyVector::operator+=(const MyVector& aVector)
//-----------------------------------------------------
{
    // The two vectors have different sizes
    if (getSize() != aVector.getSize())
    {
        // Generate an error message
        std::stringstream error_message;
        error_message << "The two vectors have different sizes (" << getSize() << " and " << aVector.getSize() << ").";
        error_message << "See: " << std::endl;
        error_message << "\t" << __FILE__ << std::endl;
        error_message << "\t" << __FUNCTION__ << std::endl;
        error_message << "\t" << __LINE__ << std::endl;

        // Throw an error
        throw error_message.str();
    }
    
    // Initialise iterators
    std::vector<float>::const_iterator ite_input(aVector.m_data.begin());
    std::vector<float>::iterator ite_output(m_data.begin());
    
    // Element-wise sum
    while (ite_input != aVector.m_data.end() && ite_output != m_data.end())
    {
        *ite_output++ += *ite_input++;
    }
    
    // Return the updated vector
    return (*this);
}


//---------------------------------
float MyVector::getMinValue() const
//---------------------------------
{
    // Replace with your own code
    return (0);
}


//---------------------------------
float MyVector::getMaxValue() const
//---------------------------------
{
    // Replace with your own code
    return (0);
}


//----------------------------
float MyVector::getSum() const
//----------------------------
{
    // Replace with your own code
    return (0);
}


//--------------------------------
float MyVector::getAverage() const
//--------------------------------
{
    // Replace with your own code
    return (0);
}


//---------------------------------
float MyVector::getVariance() const
//---------------------------------
{
    // Replace with your own code
    return (0);
}


//------------------------------------------
float MyVector::getStandardDeviation() const
//------------------------------------------
{
    // Replace with your own code
    return (0);
}


//------------------------------------------------------
bool MyVector::operator==(const MyVector& aVector) const
//------------------------------------------------------
{
    // The two vectors have different sizes
    if (getSize() != aVector.getSize())
    {
        // They are different
        return (false);
    }

    // Initialise iterators
    std::vector<float>::const_iterator ite0(m_data.begin());
    std::vector<float>::const_iterator ite1(aVector.m_data.begin());
    
    // Check every corresponding pair of elements
    while (ite0 != aVector.m_data.end() && ite1 != aVector.m_data.end())
    {
        // Does not take into account numerical inacuracy
        if (*ite0++ != *ite1++) return (false);

        // Take into account numerical inacuracy
        //if (std::abs(*ite0++ - *ite1++) > EPSILON) return (false);
    }

    // No element is different. The two vectors are then identical
    return (true);
}


//------------------------------------------------------
bool MyVector::operator!=(const MyVector& aVector) const
//------------------------------------------------------
{
    return (!((*this) == aVector));
}


//------------------------------------------------
float MyVector::SAE(const MyVector& aVector) const
//------------------------------------------------
{
    // Replace with your own code
    return (true);
}


//------------------------------------------------
float MyVector::NCC(const MyVector& aVector) const
//------------------------------------------------
{
    // Replace with your own code
    return (true);
}
