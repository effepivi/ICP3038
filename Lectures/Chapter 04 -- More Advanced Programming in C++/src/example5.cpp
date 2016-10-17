#include <cmath>
#include <iostream>

#include "example5.h"


Integer::Integer():
        m_value(0)
{}


Integer::Integer(const Integer& anInteger):
    m_value(anInteger.m_value)
{}


Integer::Integer(int anInteger):
    m_value(anInteger)
{}


Integer& Integer::operator++()
{
    m_value++;
    return (*this);
}


Integer& Integer::operator--()
{
    m_value--;
    return (*this);
}


Integer Integer::operator++(int anInteger)
{
    Integer temp(*this);
    m_value++;
    return (temp);
}


Integer Integer::operator--(int anInteger)
{
    Integer temp(*this);
    m_value--;
    return (temp);
}


std::ostream& operator<<(std::ostream& aStream, const Integer& anInteger)
{
    aStream << anInteger.m_value;
    return (aStream);
}


std::istream& operator>>(std::istream& aStream, Integer& anInteger)
{
    aStream >> anInteger.m_value;
    return (aStream);
}


//--------
int main()
//--------
{
    int i(4);

    std::cout <<   i   << std::endl;
    std::cout <<   i++ << std::endl;
    std::cout << ++i   << std::endl;
/*
    int i0(4);
    Integer i1(4);
    
    std::cout <<   i0   << "\t" <<   i1   << std::endl;
    std::cout <<   i0++ << "\t" <<   i1++ << std::endl;
    std::cout << ++i0   << "\t" << ++i1   << std::endl;
  */  
    return (0);
}
