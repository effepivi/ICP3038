#ifndef __Vector1_h
#define __Vector1_h

class Vector1
{
public:
    Vector1(int x = 0, int y = 0);

    ~Vector1();

    void updateLength();
    
    int dotProduct(Vector1 aVector);

    Vector1 crossProduct(Vector1 aVector);
    
    double distance(Vector1 aVector);

    int m_x;
    int m_y;
    double m_length;
};

#endif
