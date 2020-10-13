#include <iostream>

using namespace std;

int main()
{
    // Start the block with the declaration and initialisation of the local variables
    int i = -1;
    unsigned int ui = -1;

    short s = -2;
    unsigned short us = -2;

    char c = 255;
    unsigned char uc = 255;

    float f = -1.2;
    double d = -1.4;

    string my_string = "Hey you!";

    cout << "To print an int in C, I need: " << i << endl;
    cout << "To print an unsigned int in C, I need: " << ui << endl;

    cout << "To print a short in C, I need: " << s << endl;
    cout << "To print an unsigned short in C, I need: " << us << endl;

    cout << "To print a char in C, I need: " << c << endl;
    cout << "To print an unsigned char in C, I need: " << uc << endl;

    cout << "To print a float in C, I need: " << f << endl;
    cout << "To print a double in C, I need: " << d << endl;

    cout << "To print a string in C, I need: " << my_string << endl;

    return 0;
}
