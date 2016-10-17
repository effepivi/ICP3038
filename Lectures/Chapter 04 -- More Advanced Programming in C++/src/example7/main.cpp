#include <iostream>

#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

int main()
{
    Circle    c(2);
    Rectangle r(3, 4);
    Square    s(5);
    
    // Shape shape; // Error: Shape is an abstract class
    Shape* p_shape(0);

    p_shape = &c;
    std::cout << p_shape->getArea() << std::endl;
    std::cout << p_shape->getPerimeter() << std::endl;

    p_shape = &r;
    std::cout << p_shape->getArea() << std::endl;
    std::cout << p_shape->getPerimeter() << std::endl;

    p_shape = &s;
    std::cout << p_shape->getArea() << std::endl;
    std::cout << p_shape->getPerimeter() << std::endl;

    return (0);
}
