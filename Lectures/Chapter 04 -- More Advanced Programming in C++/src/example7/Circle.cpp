#include <cmath> // Needed for pi
#include "Circle.h"


Circle::Circle(double aRadius):
        Shape(),
        m_radius(aRadius)
{}


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

