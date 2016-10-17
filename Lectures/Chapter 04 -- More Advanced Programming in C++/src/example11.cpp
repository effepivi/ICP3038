#include <string>
#include <cstring>
#include "example11.h"



//--------
int main()
//--------
{
    // Look for exceptions
    try
    {
        DynamicArray<int> a0;
        DynamicArray<double> a1;
    
        a0.pushBack(1);
        a0.pushBack(2);
        a0.pushBack(3);
        a0.pushBack(4);
        a0.pushBack(5);
        a0.pushBack(6);
        
        a1.pushBack(1.5);
        a1.pushBack(2.5);
        a1.pushBack(3.5);
        a1.pushBack(4.5);
        a1.pushBack(5.5);
        a1.pushBack(6.5);
        
        std::cout << a0 << std::endl << std::endl;
        std::cout << a1 << std::endl;

        std::cout << "Sum:\t" << a0.getSum() << "\tAverage:\t" << a0.getAverage() << std::endl;

        std::cout << "Sum:\t" << a1.getSum() << "\tAverage:\t" << a1.getAverage() << std::endl;
    
        return (0);
    }
    // There was an error
    catch (std::string& anErrorMessage)
    {
        std::cerr << "ERROR:\t" << anErrorMessage << std::endl;
        return (1);
    }
}

