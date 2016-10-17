#ifndef EXAMPLE8_H
#define EXAMPLE8_H

#include <iostream>

template <typename T>
class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(const DynamicArray& anArray);
    DynamicArray(const T* apArray, unsigned int aNumberOfElements);

    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& anArray);
    
    const T& operator[](int i) const;
    T& operator[](int i);
    
    void pushBack(T aValue);
    T popBack();

    unsigned int getSize() const;
    T getSum() const;
    float getAverage() const;
    
    template <typename U>
    friend std::ostream& operator<<(std::ostream& aStream, const DynamicArray<U>& anArray);
    
    template <typename U>
    friend std::istream& operator>>(std::istream& aStream, DynamicArray<U>& anArray);
    
private:
    unsigned int m_buffer_size;
    unsigned int m_number_of_elements;
    
    T* m_p_data;
};


//----------------------------------------
template <typename T>
DynamicArray<T>::DynamicArray():
//----------------------------------------
        m_buffer_size(5),
        m_number_of_elements(0),
        m_p_data(new T[m_buffer_size])
//----------------------------------------
{}


//---------------------------------------------------------
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& anArray):
//---------------------------------------------------------
        m_buffer_size(anArray.m_buffer_size),
        m_number_of_elements(anArray.m_number_of_elements),
        m_p_data(new T[m_buffer_size])
//---------------------------------------------------------
{
    // There are elements in the array
    if (m_number_of_elements)
    {
        // Copy the elements
        memcpy(m_p_data, anArray.m_p_data, sizeof(T) * m_number_of_elements);
    }
}


//-------------------------------------------------------------------------------
template <typename T>
DynamicArray<T>::DynamicArray(const T* apArray, unsigned int aNumberOfElements):
//-------------------------------------------------------------------------------
        m_buffer_size(aNumberOfElements),
        m_number_of_elements(aNumberOfElements),
        m_p_data(new T[m_buffer_size])
//-------------------------------------------------------------------------------
{
    // There are elements in the array
    if (m_number_of_elements)
    {
        // Copy the elements
        memcpy(m_p_data, apArray, sizeof(T) * m_number_of_elements);
    }
}


//---------------------------
template <typename T>
DynamicArray<T>::~DynamicArray()
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
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& anArray)
//----------------------------------------------------------------
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
        m_p_data = new T[m_buffer_size];
    }
    
    // Store the number of elements
    m_number_of_elements = anArray.m_number_of_elements;
    
    // There are elements in the array
    if (m_number_of_elements)
    {
        // Copy the elements
        memcpy(m_p_data, anArray.m_p_data, sizeof(T) * m_number_of_elements);
    }

    // Return the instance
    return (*this);
}


//------------------------------------------------
template <typename T>
const T& DynamicArray<T>::operator[](int i) const
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
template <typename T>
T& DynamicArray<T>::operator[](int i)
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
template <typename T>
void DynamicArray<T>::pushBack(T aValue)
//---------------------------------------
{
    // The array is too small
    if (m_number_of_elements + 1 > m_buffer_size)
    {
        // Create a new and bigger array
        T* p_temp(new T[m_buffer_size * 2]);
    
        // Copy the data
        memcpy(p_temp, m_p_data, sizeof(T) * m_number_of_elements);
    
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
template <typename T>
T DynamicArray<T>::popBack()
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
template <typename T>
unsigned int DynamicArray<T>::getSize() const
//----------------------------------------
{
    // Return the number of elements in the array
    return (m_number_of_elements);
}


//--------------------------------
template <typename T>
T DynamicArray<T>::getSum() const
//--------------------------------
{
    T temp(0.0);
    
    for (unsigned int i(0); i < m_number_of_elements; ++i)
    {
        temp += m_p_data[i];
    }
    
    return (temp);
}


//------------------------------------
template <typename T>
float DynamicArray<T>::getAverage() const
//------------------------------------
{
    // There is no element
    if (!getSize())
    {
        // Throw an error
        throw (std::string("Division by zero"));
    }

    // Return the average value
    return (float(getSum()) / getSize());
}


//--------------------------------------------------------------------------
template <typename T>
std::ostream& operator<<(std::ostream& aStream, const DynamicArray<T>& anArray)
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
template <typename T>
std::istream& operator>>(std::istream& aStream, DynamicArray<T>& anArray)
//--------------------------------------------------------------------
{
    // Add an element in the array
    T temp;
    aStream >> temp;
    anArray.pushBack(temp);
    
    return (aStream);
}


#endif
