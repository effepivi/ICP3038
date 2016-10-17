#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
public:
    Shape();

    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    
protected:
    double m_p_position[2];
};

#endif
