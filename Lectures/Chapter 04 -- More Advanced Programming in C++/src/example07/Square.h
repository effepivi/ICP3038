#ifndef SQUARE_H
#define SQUARE_H


#include "Rectangle.h"


class Square: public Rectangle
{
public:
    Square(double aWidth = 0);

    double getEdge() const;
};

#endif
