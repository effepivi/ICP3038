#ifndef EXAMPLE1_H
#define EXAMPLE1_H

class Cube
{
public:
    Cube();
    Cube(float anEdgeSize);
    
    float getVolume() const;
    
    bool isBigger(const Cube& aCube) const;
    
private:
    float m_edge_size;
};

#endif
