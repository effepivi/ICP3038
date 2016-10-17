#ifndef EXAMPLE7_H
#define EXAMPLE7_H

#include <iostream>

class DynamicArray
{
public:
    DynamicArray();
    DynamicArray(const DynamicArray& anArray);
    DynamicArray(const float* apArray, unsigned int aNumberOfElements);

    ~DynamicArray();

    DynamicArray& operator=(const DynamicArray& anArray);
    
    const float& operator[](int i) const;
    float& operator[](int i);
    
    void pushBack(float aValue);
    float popBack();

    unsigned int getSize() const;
    float getSum() const;
    float getAverage() const;
    
    friend std::ostream& operator<<(std::ostream& aStream, const DynamicArray& anArray);
    friend std::istream& operator>>(std::istream& aStream, DynamicArray& anArray);
    
private:
    unsigned int m_buffer_size;
    unsigned int m_number_of_elements;
    
    float* m_p_data;
};

#endif
