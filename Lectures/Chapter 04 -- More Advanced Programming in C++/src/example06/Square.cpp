#include "Square.h"


Square::Square():
        m_edge_length(0)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


Square::Square(double aWidth):
        m_edge_length(aWidth)
{
    m_p_position[0] = 0;
    m_p_position[1] = 0;
}


double Square::getEdge() const
{
    return (m_edge_length);
}


double Square::GetArea() const
{
    return (m_edge_length * m_edge_length);
}


double Square::getPerimeter() const
{
    return (4.0 * m_edge_length);
}

