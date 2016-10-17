#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "Shape.h"


class Rectangle: public Shape
{
public:
    Rectangle(double aWidth = 0, double aHeight = 0);

    double getWidth() const;
    double getHeight() const;
    
    virtual double getArea() const;
    virtual double getPerimeter() const;
    
protected:
    unsigned int m_width;
    unsigned int m_height;
};

#endif
