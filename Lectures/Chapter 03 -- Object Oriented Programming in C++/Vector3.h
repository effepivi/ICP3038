#ifndef __Vector3_h
#define __Vector3_h


#include <iostream>


class Vector3;

std::ostream& operator<<(std::ostream& anOutputStream,
                         const Vector3& aVector);

std::istream& operator>>(std::istream& anInputStream,
                         Vector3& aVector);

class Vector3
{
public:
    Vector3(int x = 0, int y = 0);

    ~Vector3();
    
    int dotProduct(const Vector3 aVector) const;

    Vector3 crossProduct(const Vector3 aVector) const;
    
    double distance(const Vector3 aVector) const;

    void setX(int x);
    
    void setY(int y);
    
    int getX() const;
    
    int getY() const;
    
    double getLength() const;
    
    const int& operator[](std::size_t anIndex) const;
    
    bool operator==(const Vector3 aVector) const;
    bool operator!=(const Vector3 aVector) const;
    
    Vector3& operator=(const Vector3 aVector);

private:
    // Only called when m_x or m_y are modified, e.g. in constructor and setters
    void updateLength();

    int m_x;
    int m_y;
    double m_length;
};

#endif
