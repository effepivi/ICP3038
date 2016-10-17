#ifndef EXAMPLE4_H
#define EXAMPLE4_H

#include <iostream>


class Integer
{
public:
    Integer();
    Integer(const Integer& anInteger);
    Integer(int anInteger);
    
    Integer& operator=(const Integer& anInteger);
    Integer& operator=(int anInteger);
    
    Integer operator*(const Integer& anInteger) const;
    Integer operator*(int anInteger) const;
    
    Integer& operator*=(const Integer& anInteger);
    Integer& operator*=(int anInteger);
    
   /* Integer& operator++();
    Integer& operator--();
*/
    friend std::ostream& operator<<(std::ostream& aStream, const Integer& anInteger);
    friend std::istream& operator>>(std::istream& aStream, Integer& anInteger);
  
private:
    int m_value;
};

#endif
