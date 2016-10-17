#ifndef EXAMPLE5_H
#define EXAMPLE5_H

#include <iostream>


class Integer
{
public:
    Integer();
    Integer(const Integer& anInteger);
    Integer(int anInteger);
        
    Integer& operator++();
    Integer& operator--();

    Integer operator++(int anInteger);
    Integer operator--(int anInteger);

    friend std::ostream& operator<<(std::ostream& aStream, const Integer& anInteger);
    friend std::istream& operator>>(std::istream& aStream, Integer& anInteger);
  
private:
    int m_value;
};

#endif
