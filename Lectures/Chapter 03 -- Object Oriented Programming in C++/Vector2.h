#ifndef __Vector2_h
#define __Vector2_h

class Vector2
{
public:
    Vector2(int x = 0, int y = 0);

    ~Vector2();
    
    int dotProduct(Vector2 aVector);

    Vector2 crossProduct(Vector2 aVector);
    
    double distance(Vector2 aVector);

    void setX(int x);
    
    void setY(int y);
    
    int getX();
    
    int getY();
    
    double getLength();
    
private:
    // Only called when m_x or m_y are modified, e.g. in constructor and setters
    void updateLength();

    int m_x;
    int m_y;
    double m_length;
};

#endif
