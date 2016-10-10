#include "Vector3.h"

using namespace std;


int main()
{
    Vector3 v1(3);

    cout << "v1 = (" << v1 << ")" << endl;
    cout << "v1.m_length = " << v1.getLength() << endl << endl;
    
    cout << "Type a 2D vector:" << endl;
    Vector3 v2;
    cin >> v2;

    cout << "v2 = (" << v2 << ")" << endl;
    cout << "v2.m_length = " << v2.getLength() << endl << endl;

    cout << "v1 same as v2? " << (v1==v2?"YES" : "NO") << endl << endl;
   
    cout << "v1 = (" << v1[0] << " " << v1[1] << ")" << endl;

    return 0;
}
