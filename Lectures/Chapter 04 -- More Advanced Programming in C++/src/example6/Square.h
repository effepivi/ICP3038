#ifndef SQUARE_H
#define SQUARE_H

class Square
{
public:
    Square();

    Square(double aWidth);

    double getEdge() const;

    double GetArea() const;
    double getPerimeter() const;
    
private:
    double m_p_position[2];
    unsigned int m_edge_length;
};

#endif
