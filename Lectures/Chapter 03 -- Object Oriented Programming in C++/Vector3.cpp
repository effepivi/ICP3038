#include <cmath>
#include <cassert>

#include "Vector3.h"


using namespace std;


Vector3::Vector3(int x, int y):
    m_x(x),
    m_y(y),
    m_length(0.0)
{
    updateLength();
}


Vector3::~Vector3()
{}


void Vector3::updateLength()
{
    m_length = sqrt(double(m_x * m_x + m_y * m_y));
}


int Vector3::dotProduct(const Vector3 aVector) const
{
    return (m_x * aVector.m_x + m_y * aVector.m_y);
}


Vector3 Vector3::crossProduct(const Vector3 aVector) const
{
    return (Vector3(m_x * aVector.m_y, -aVector.m_x * m_y));
}


double Vector3::distance(const Vector3 aVector) const
{
    return (sqrt(
        pow(double(m_x - aVector.m_x), 2) +
        pow(double(m_y - aVector.m_y), 2))
    );
}


void Vector3::setX(int x)
{
    m_x = x;
    updateLength();
}


void Vector3::setY(int y)
{
    m_y = y;
    updateLength();
}


int Vector3::getX() const
{
    return (m_x);
}


int Vector3::getY() const
{
    return (m_y);
}


double Vector3::getLength() const
{
    return (m_length);
}


const int& Vector3::operator[](std::size_t anIndex) const
{
    if (anIndex == 0)
    {
        return (m_x);
    }
    else if (anIndex == 1)
    {
        return (m_y);
    }
}


bool Vector3::operator==(const Vector3 aVector) const
{
    return (m_x == aVector.m_x && m_y == aVector.m_y);
}


bool Vector3::operator!=(const Vector3 aVector) const
{
    return (!operator==(aVector));
}


Vector3& Vector3::operator=(const Vector3 aVector)
{
    m_x = aVector.m_x;
    m_y = aVector.m_y;
    m_length = aVector.m_length;
    
    return (*this);
}


std::ostream& operator<<(std::ostream& anOutputStream,
                         const Vector3& aVector)
{
    anOutputStream << aVector.getX() << " " << aVector.getY();
    return (anOutputStream);
}

std::istream& operator>>(std::istream& anInputStream,
                         Vector3& aVector)

{
    int x, y;
    anInputStream >> x >> y;
    aVector = Vector3(x, y);
    return (anInputStream);
}
