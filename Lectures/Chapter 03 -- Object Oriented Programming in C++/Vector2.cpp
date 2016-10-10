#include <cmath>

#include "Vector2.h"


using namespace std;


Vector2::Vector2(int x, int y):
    m_x(x),
    m_y(y),
    m_length(0.0)
{
    updateLength();
}


Vector2::~Vector2()
{}


void Vector2::updateLength()
{
    m_length = sqrt(double(m_x * m_x + m_y * m_y));
}


int Vector2::dotProduct(Vector2 aVector)
{
    return (m_x * aVector.m_x + m_y * aVector.m_y);
}


Vector2 Vector2::crossProduct(Vector2 aVector)
{
    return (Vector2(m_x * aVector.m_y, -aVector.m_x * m_y));
}


double Vector2::distance(Vector2 aVector)
{
    return (sqrt(
        pow(double(m_x - aVector.m_x), 2) +
        pow(double(m_y - aVector.m_y), 2))
    );
}


void Vector2::setX(int x)
{
    m_x = x;
    updateLength();
}


void Vector2::setY(int y)
{
    m_y = y;
    updateLength();
}


int Vector2::getX()
{
    return (m_x);
}


int Vector2::getY()
{
    return (m_y);
}


double Vector2::getLength()
{
    return (m_length);
}
