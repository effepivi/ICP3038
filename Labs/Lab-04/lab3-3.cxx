#include <iostream>
#include <string>

using namespace std;

void printArray(const string& aName, float* anArray, unsigned int aNumberOfElements);


int main()
{
    // write your own code here
    float a[5] = {1.0, 2.0, 4.4, 8.0, 16.0};
    // float b[5] = {1.0, 2.0, 4.4, 8.0, 16.0, 32.0}; // Compilation error, declared an array of 5 floating point numbers, but tried to initialise as an array of 6 numbers
    float c[] = {1.0, 2.0, 4.4, 8.0, 16.00};
    float d[5]; // The array is not initialise, CAREFUL
    float e[5] = {};

    printArray("a", a, 5);
    //printArray("b", b, 6);
    printArray("c", c, 5);
    printArray("d", d, 5);
    printArray("e", e, 5);

    return 0;
}


void printArray(const string& aName, float* anArray, unsigned int aNumberOfElements)
{
    // write your own code here
    for (size_t i = 0; i < aNumberOfElements; ++i)
    {
        cout << aName << "[" << i << "]: " << anArray[i] << endl;
    }
}
