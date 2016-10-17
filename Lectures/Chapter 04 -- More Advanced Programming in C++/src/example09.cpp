#include "example9.h"

int main()
{
    int a(-2), b(-1);
    unsigned int c(2), d(1);
    
    sort<int>(a, b);
    sort<unsigned int>(c, d);
    
    sort(a, b);
    sort(c, d);

    std::cout << a << " < " << b << std::endl;
    std::cout << c << " < " << d << std::endl;
    
    return (0);
}
