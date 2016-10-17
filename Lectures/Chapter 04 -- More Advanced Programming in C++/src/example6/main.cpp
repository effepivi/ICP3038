#include <iostream>

#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

int main()
{
    Circle    c(2);
    Rectangle r(3, 4);
    Square    s(5);
    
    std::cout << c.getArea() << std::endl;
    std::cout << r.GetArea() << std::endl;
    std::cout << s.GetArea() << std::endl;
    
    std::cout << c.getPerimeter() << std::endl;
    std::cout << r.GetPerimeter() << std::endl;
    std::cout << s.getPerimeter() << std::endl;
    
    return (0);
}
