#include <cmath>

#include "Vector1.h"

using namespace std;

Vector1::Vector1(int x, int y):
    m_x(x),
    m_y(y),
    m_length(0.0)
{
    updateLength();
}


Vector1::~Vector1()
{}

void Vector1::updateLength()
{
    m_length = sqrt(double(m_x * m_x + m_y * m_y));
}

int Vector1::dotProduct(Vector1 aVector)
{
    return (m_x * aVector.m_x + m_y * aVector.m_y);
}

Vector1 Vector1::crossProduct(Vector1 aVector)
{
    return (Vector1(m_x * aVector.m_y, -aVector.m_x * m_y));
}

double Vector1::distance(Vector1 aVector)
{
    return (sqrt(
        pow(double(m_x - aVector.m_x), 2) +
        pow(double(m_y - aVector.m_y), 2))
    );
}
