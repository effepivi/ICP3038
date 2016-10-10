#include <iostream>

#include "Vector1.h"

using namespace std;


int main()
{
    Vector1 v1(3);

    cout << "v1 = (" << v1.m_x << ", " << v1.m_y << ")" << endl;
    cout << "v1.m_length = " << v1.m_length << endl << endl;
    
    Vector1 v2(2, 4);

    cout << "v2 = (" << v2.m_x << ", " << v2.m_y << ")" << endl;
    cout << "v2.m_length = " << v2.m_length << endl << endl;

    cout << "Distance between v1 and v2: " << v1.distance(v2) << endl << endl;
   
    return 0;
}
