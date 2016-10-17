#include <cmath>
#include <iostream>

#include "example1.h"


//--------------------
Cube::Cube():
//--------------------
        m_edge_size(1)
//--------------------
{}


//-----------------------------
Cube::Cube(float anEdgeSize):
//-----------------------------
        m_edge_size(anEdgeSize)
//-----------------------------
{}


//---------------------------
float Cube::getVolume() const
//---------------------------
{
    return (pow(m_edge_size, 3));
}


//------------------------------------------
bool Cube::isBigger(const Cube& aCube) const
//------------------------------------------
{
    return (this->getVolume() > aCube.getVolume());
    
    // Same as below:
    /*
    if (this->getVolume() > aCube.isBigger())
    {
        return (true);
    }
    else
    {
        return (false);
    }
    */
}


//--------
int main()
//--------
{
    Cube a(1);
    Cube b(2);
    Cube c(2);
    
    if (a.isBigger(b))
    {
        std::cout << "a is bigger than b" << std::endl;
    }
    else if (b.isBigger(a))
    {
        std::cout << "b is bigger than a" << std::endl;
    }
    else
    {
        std::cout << "a and b have the same volume" << std::endl;
    }
    
    if (b.isBigger(c))
    {
        std::cout << "b is bigger than c" << std::endl;
    }
    else if (c.isBigger(b))
    {
        std::cout << "c is bigger than b" << std::endl;
    }
    else
    {
        std::cout << "b and c have the same volume" << std::endl;
    }
    
    return (0);
}
