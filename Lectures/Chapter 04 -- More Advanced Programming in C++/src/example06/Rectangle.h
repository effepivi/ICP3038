#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
    Rectangle();
    Rectangle(double aWidth, double aHeight);

    double getWidth() const;
    double getHeight() const;
    
    double GetArea() const;
    double GetPerimeter() const;
    
private:
    double m_p_position[2];
    unsigned int m_width;
    unsigned int m_height;
};

#endif
