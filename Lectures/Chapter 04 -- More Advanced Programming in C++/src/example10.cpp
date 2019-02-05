#include <string>
#include <cstring>
#include "example10.h"


//----------------------------------------
DynamicArray::DynamicArray():
//----------------------------------------
        m_buffer_size(5),
        m_number_of_elements(0),
        m_p_data(new float[m_buffer_size])
//----------------------------------------
{}


//---------------------------------------------------------
DynamicArray::DynamicArray(const DynamicArray& anArray):
//---------------------------------------------------------
        m_buffer_size(anArray.m_buffer_size),
        m_number_of_elements(anArray.m_number_of_elements),
        m_p_data(new float[m_buffer_size])
//---------------------------------------------------------
{
    // There are elements in the array
    if (m_number_of_elements)
    {
        // Copy the elements
        memcpy(m_p_data, anArray.m_p_data, sizeof(float) * m_number_of_elements);
    }
}


//-------------------------------------------------------------------------------
DynamicArray::DynamicArray(const float* apArray, unsigned int aNumberOfElements):
//-------------------------------------------------------------------------------
        m_buffer_size(aNumberOfElements),
        m_number_of_elements(aNumberOfElements),
        m_p_data(new float[m_buffer_size])
//-------------------------------------------------------------------------------
{
    // There are elements in the array
    if (m_number_of_elements)
    {
        // Copy the elements
        memcpy(m_p_data, apArray, sizeof(float) * m_number_of_elements);
    }
}


//---------------------------
DynamicArray::~DynamicArray()
//---------------------------
{
    // Dynamic memory allocated
    if (m_p_data)
    {
        // Release the memory
        delete [] m_p_data;
    }
}



//----------------------------------------------------------------
DynamicArray& DynamicArray::operator=(const DynamicArray& anArray)
//----------------------------------------------------------------
{
    // Avoid self-copy
    if (this != &anArray)
    {
        // The current array is too smal
        if (m_buffer_size < anArray.m_number_of_elements)
        {
            // Increase the size
            m_buffer_size = anArray.m_buffer_size;

            // Dynamic memory allocated
            if (m_p_data)
            {
                // Release the memory
                delete [] m_p_data;
            }

            // Allocate memory
            m_p_data = new float[m_buffer_size];
        }

        // Store the number of elements
        m_number_of_elements = anArray.m_number_of_elements;

        // There are elements in the array
        if (m_number_of_elements)
        {
            // Copy the elements
            memcpy(m_p_data, anArray.m_p_data, sizeof(float) * m_number_of_elements);
        }
    }

    // Return the instance
    return (*this);
}


//------------------------------------------------
const float& DynamicArray::operator[](int i) const
//------------------------------------------------
{
    // The index is invalid
    if (i < 0 || i >= m_number_of_elements)
    {
        // Throw an error
        throw (std::string("Invalid index"));
    }

    // Return the element
    return (m_p_data[i]);
}


//------------------------------------
float& DynamicArray::operator[](int i)
//------------------------------------
{
    // The index is invalid
    if (i < 0 || i >= m_number_of_elements)
    {
        // Throw an error
        throw (std::string("Invalid index"));
    }

    // Return the element
    return (m_p_data[i]);
}


//---------------------------------------
void DynamicArray::pushBack(float aValue)
//---------------------------------------
{
    // The array is too small
    if (m_number_of_elements + 1 > m_buffer_size)
    {
        // Create a new and bigger array
        float* p_temp(new float[m_buffer_size * 2]);

        // Copy the data
        memcpy(p_temp, m_p_data, sizeof(float) * m_number_of_elements);

        // Release the 'old' memory
        delete [] m_p_data;

        // Save the pointer
        m_p_data = p_temp;
    }

    // Add the new element
    m_p_data[m_number_of_elements] = aValue;

    // Increment the counter
    ++m_number_of_elements;
}


//---------------------------
float DynamicArray::popBack()
//---------------------------
{
    // There is no element
    if (!m_number_of_elements)
    {
        // Throw an error
        throw (std::string("Empty list"));
    }

    // Decrement the counter
    --m_number_of_elements;

    // Return the last element
    return (m_p_data[m_number_of_elements]);
}


//----------------------------------------
unsigned int DynamicArray::getSize() const
//----------------------------------------
{
    // Return the number of elements in the array
    return (m_number_of_elements);
}


//--------------------------------
float DynamicArray::getSum() const
//--------------------------------
{
    float temp(0.0);

    for (unsigned int i(0); i < m_number_of_elements; ++i)
    {
        temp += m_p_data[i];
    }

    return (temp);
}


//------------------------------------
float DynamicArray::getAverage() const
//------------------------------------
{
    // There is no element
    if (!getSize())
    {
        // Throw an error
        throw (std::string("Division by zero"));
    }

    // Return the average value
    return (getSum() / getSize());
}


//--------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& aStream, const DynamicArray& anArray)
//--------------------------------------------------------------------------
{
    // Display all the elements of the array
    for (unsigned int i(0); i < anArray.m_number_of_elements; ++i)
    {
        aStream << anArray.m_p_data[i];

        if (i < (anArray.m_number_of_elements - 1))
        {
            aStream << "\t";
        }
    }

    return (aStream);
}


//--------------------------------------------------------------------
std::istream& operator>>(std::istream& aStream, DynamicArray& anArray)
//--------------------------------------------------------------------
{
    // Add an element in the array
    float temp;
    aStream >> temp;
    anArray.pushBack(temp);

    return (aStream);
}


//--------
int main()
//--------
{
    // Look for exceptions
    try
    {
        DynamicArray a0;

        a0.pushBack(1);
        a0.pushBack(2);
        a0.pushBack(3);
        a0.pushBack(4);
        a0.pushBack(5);
        a0.pushBack(6);

        std::cout << a0 << std::endl;

        {
            DynamicArray a1;

            for (unsigned int i(0); i < 5; ++i)
            {
                std::cout << "Enter a number:" << std::endl;
                std::cin >> a1;
            }
            std::cout << std::endl;

            a0 = a1;

            std::cout << a0 << std::endl;
        }

        std::cout << a0.popBack() << std::endl;
        std::cout << a0.popBack() << std::endl;
        std::cout << a0.popBack() << std::endl;
        std::cout << a0.popBack() << std::endl;
        std::cout << a0.popBack() << std::endl;
        //std::cout << a0.popBack() << std::endl;

        std::cout << a0 << std::endl;

        a0.pushBack(1);
        a0.pushBack(2);
        a0.pushBack(3);
        a0.pushBack(4);
        a0.pushBack(5);
        a0.pushBack(6);

        //for (unsigned int i(0); i <= a0.getSize(); ++i)
        for (unsigned int i(0); i < a0.getSize(); ++i)
        {
            std::cout << i << "\t" << a0[i] << std::endl;
        }

        std::cout << "Sum:\t" << a0.getSum() << "\tAverage:\t" << a0.getAverage() << std::endl;

        return (0);
    }
    // There was an error
    catch (std::string& anErrorMessage)
    {
        std::cerr << "ERROR:\t" << anErrorMessage << std::endl;
        return (1);
    }
}
