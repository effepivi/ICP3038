#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <algorithm>


bool isEqual(float a, float b, float epsilon = 0.0001)
{
    // Handle infinities
    if (a == b) return true;
    //else return false;
        
    float abs_A    = abs(a);
    float abs_B    = abs(b);
    float abs_diff = abs(a - b);

    // if a or b is zero or both are extremely close to it
    // then relative error is less meaningful
    if (a == 0 || b == 0 || (abs_A + abs_B < std::numeric_limits<float>::min()))
        return abs_diff < std::numeric_limits<float>::min();
    // use relative error
    else
        return ((abs_diff / std::min(abs_A, abs_B)) < epsilon);
}



void compare(float a, float b)
{
    std::cout << a << " is " << (isEqual(a, b)?"the SAME as ":"DIFFERENT from ") << b << std::endl;
}


int main()
{
    float i = 11.1111;
    float j = 22.2222;
    float k = i + j;
    float l = j + i;
    float m = 33.3333;
    float o = i * 3.0;

    std::cout << "k=" << k << "\tl=" << l << "\tm=" << m << "\to=" << o << std::endl;
    
    std::cout << 
        std::setprecision(17) << "k=" << k << 
        "\tl=" << std::setprecision(17) << l << 
        "\tm=" << std::setprecision(17) << m << 
        "\to=" << std::setprecision(17) << 0 <<
        std::endl;

    compare(k, l);
    compare(k, m);
    compare(l, m);
    compare(o, m);

    return 0;
}
