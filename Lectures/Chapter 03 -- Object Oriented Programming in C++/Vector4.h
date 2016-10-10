#ifndef __Vector4_h
#define __Vector4_h


#include <iostream>


class Vector4;

std::ostream& operator<<(std::ostream& anOutputStream,
                         const Vector4& aVector);

std::istream& operator>>(std::istream& anInputStream,
                         Vector4& aVector);

class Vector4
{
public:
    Vector4(int x = 0, int y = 0);

    ~Vector4();
    
    int dotProduct(const Vector4 aVector) const;

    Vector4 crossProduct(const Vector4 aVector) const;
    
    double distance(const Vector4 aVector) const;

    void setX(int x);
    
    void setY(int y);
    
    int getX() const;
    
    int getY() const;
    
    double getLength() const;
    
    const int& operator[](std::size_t anIndex) const;
    
    bool operator==(const Vector4 aVector) const;
    bool operator!=(const Vector4 aVector) const;
    
    Vector4& operator=(const Vector4 aVector);

private:
    // Only called when m_x or m_y are modified, e.g. in constructor and setters
    void updateLength();

    int m_x;
    int m_y;
    double m_length;
};

#endif
