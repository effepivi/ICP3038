#include <iostream>

#include "Vector2.h"

using namespace std;


int main()
{
    Vector2 v1(3);

    cout << "v1 = (" << v1.getX() << ", " << v1.getY() << ")" << endl;
    cout << "v1.m_length = " << v1.getLength() << endl << endl;
    
    Vector2 v2(2, 4);

    cout << "v2 = (" << v2.getX() << ", " << v2.getY() << ")" << endl;
    cout << "v2.m_length = " << v2.getLength() << endl << endl;

    cout << "Distance between v1 and v2: " << v1.distance(v2) << endl << endl;
   
    v1.setY(5);
    cout << "v1 = (" << v1.getX() << ", " << v1.getY() << ")" << endl;
    cout << "v1.m_length = " << v1.getLength() << endl << endl;

    //v1.updateLength();
    //cout << "v1.m_length = " << v1.getLength() << endl;

    return 0;
}
