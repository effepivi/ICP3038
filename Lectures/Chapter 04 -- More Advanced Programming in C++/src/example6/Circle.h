#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
public:
    Circle();
    Circle(double aWidth);

    double getRadius() const;
    double getDiameter() const;

    double getArea() const;
    double getPerimeter() const;
    
private:
    double m_p_position[2];
    unsigned int m_radius;
};

#endif
