#include "Rectangle.h"


Rectangle::Rectangle(double aWidth, double aHeight):
        Shape(),
        m_width(aWidth),
        m_height(aHeight)
{}


double Rectangle::getWidth() const
{
    return (m_width);
}


double Rectangle::getHeight() const
{
    return (m_height);
}


double Rectangle::getArea() const
{
    return (m_width * m_height);
}


double Rectangle::getPerimeter() const
{
    return (2.0 * m_width + 2.0 * m_height);
}
