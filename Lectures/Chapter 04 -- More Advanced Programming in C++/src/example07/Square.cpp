#include "Square.h"


Square::Square(double aWidth):
        Rectangle(aWidth, aWidth)
{}


double Square::getEdge() const
{
    return (getWidth());
}
