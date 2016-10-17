#include <cmath>
#include <iostream>

#include "example4.h"


Integer::Integer():
        m_value(0)
{}


Integer::Integer(const Integer& anInteger):
    m_value(anInteger.m_value)
{}


Integer::Integer(int anInteger):
    m_value(anInteger)
{}


Integer& Integer::operator=(const Integer& anInteger)
{
    m_value = anInteger.m_value;
    return (*this);
}


Integer& Integer::operator=(int anInteger)
{
    m_value = anInteger;
    return (*this);
}


Integer Integer::operator*(const Integer& anInteger) const
{
    return (Integer(m_value * anInteger.m_value));
}


Integer Integer::operator*(int anInteger) const
{
    return (Integer(m_value * anInteger));
}


Integer& Integer::operator*=(const Integer& anInteger)
{
    m_value *= anInteger.m_value;
    return (*this);
}


Integer& Integer::operator*=(int anInteger)
{
    m_value *= anInteger;
    return (*this);
}

/*
Integer& Integer::operator++()
{
    m_value++;
    return (*this);
}*/

/*
Integer& Integer::operator--()
{
    m_value--;
    return (*this);
}*/


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
    int i = 4;
    int k;
    k = i *= 3;
    std::cout << i << "\t" << k   << std::endl;

    int i0(1);
    Integer i1(1);

    i1 = i0;
    
    std::cout << i0 * 2 << std::endl;
    std::cout << i1 * 2 << std::endl;
    std::cout << std::endl;
    
    int j0(i0);
    Integer j1(j0);

    int k0;
    Integer k1;
    
    k0 = i0 *= 3;
    k1 = i1 *= 3;
    
    std::cout << k0 << "\t" << i0 << std::endl;
    std::cout << k1 << "\t" << i1 << std::endl;
    std::cout << std::endl;
    
    std::cout << ++i0 << std::endl;
    std::cout << ++i1 << std::endl;
    std::cout << std::endl;

    std::cout << k0 << "\t" << i0 << std::endl;
    std::cout << k1 << "\t" << i1 << std::endl;
    std::cout << std::endl;

    return (0);
}
