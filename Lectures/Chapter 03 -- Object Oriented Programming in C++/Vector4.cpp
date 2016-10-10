#include <cmath>
#include <cassert>

#include "Vector4.h"


using namespace std;


Vector4::Vector4(int x, int y):
    m_x(x),
    m_y(y),
    m_length(0.0)
{
    updateLength();
}


Vector4::~Vector4()
{}


void Vector4::updateLength()
{
    m_length = sqrt(double(m_x * m_x + m_y * m_y));
}


int Vector4::dotProduct(const Vector4 aVector) const
{
    return (m_x * aVector.m_x + m_y * aVector.m_y);
}


Vector4 Vector4::crossProduct(const Vector4 aVector) const
{
    return (Vector4(m_x * aVector.m_y, -aVector.m_x * m_y));
}


double Vector4::distance(const Vector4 aVector) const
{
    return (sqrt(
        pow(double(m_x - aVector.m_x), 2) +
        pow(double(m_y - aVector.m_y), 2))
    );
}


void Vector4::setX(int x)
{
    m_x = x;
    updateLength();
}


void Vector4::setY(int y)
{
    m_y = y;
    updateLength();
}


int Vector4::getX() const
{
    return (m_x);
}


int Vector4::getY() const
{
    return (m_y);
}


double Vector4::getLength() const
{
    return (m_length);
}


const int& Vector4::operator[](std::size_t anIndex) const
{
    assert(anIndex < 2);
    
    if (anIndex == 0)
    {
        return (m_x);
    }
    else if (anIndex == 1)
    {
        return (m_y);
    }
}


bool Vector4::operator==(const Vector4 aVector) const
{
    return (m_x == aVector.m_x && m_y == aVector.m_y);
}


bool Vector4::operator!=(const Vector4 aVector) const
{
    return (!operator==(aVector));
}


Vector4& Vector4::operator=(const Vector4 aVector)
{
    m_x = aVector.m_x;
    m_y = aVector.m_y;
    m_length = aVector.m_length;
    
    return (*this);
}


std::ostream& operator<<(std::ostream& anOutputStream,
                         const Vector4& aVector)
{
    anOutputStream << aVector.getX() << " " << aVector.getY();
    return (anOutputStream);
}

std::istream& operator>>(std::istream& anInputStream,
                         Vector4& aVector)

{
    int x, y;
    anInputStream >> x >> y;
    aVector = Vector4(x, y);
    return (anInputStream);
}
