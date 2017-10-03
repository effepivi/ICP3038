#include <iostream>
#include "GreyscaleImage.h"

using namespace std;

int main()
{
    GreyscaleImage temp;
    temp.create(1024, 768, 2);
    cout << temp.aspectRatio() << endl;
    
    return (0);
}
