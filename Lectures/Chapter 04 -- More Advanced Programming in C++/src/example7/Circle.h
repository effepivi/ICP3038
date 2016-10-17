#ifndef CIRCLE_H
#define CIRCLE_H


#include "Shape.h"


class Circle: public Shape
{
public:
    Circle(double aWidth = 0);

    double getRadius() const;
    double getDiameter() const;

    virtual double getArea() const;
    virtual double getPerimeter() const;
    
private:
    unsigned int m_radius;
};

#endif
