#include "Rectangle.h"


Rectangle::Rectangle():
        m_width(0.0),
        m_height(0.0)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


Rectangle::Rectangle(double aWidth, double aHeight):
        m_width(aWidth),
        m_height(aHeight)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


double Rectangle::getWidth() const
{
    return (m_width);
}


double Rectangle::getHeight() const
{
    return (m_height);
}


double Rectangle::GetArea() const
{
    return (m_width * m_height);
}


double Rectangle::GetPerimeter() const
{
    return (2.0 * m_width + 2.0 * m_height);
}
