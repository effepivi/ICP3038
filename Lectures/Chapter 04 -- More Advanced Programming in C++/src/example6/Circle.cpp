#include <cmath> // Needed for pi
#include "Circle.h"


Circle::Circle():
        m_radius(0)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


Circle::Circle(double aRadius):
        m_radius(aRadius)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


double Circle::getRadius() const
{
    return (m_radius);
}


double Circle::getDiameter() const
{
    return (2.0 * m_radius);
}


double Circle::getArea() const
{
    return (M_PI * m_radius * m_radius);
}


double Circle::getPerimeter() const
{
    return (2.0 * M_PI * m_radius);
}

