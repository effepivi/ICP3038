#include <iostream>

#include "example8.h"


void sort(unsigned char& i, unsigned char& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


void sort(char& i, char& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


void sort(unsigned short& i, unsigned short& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


void sort(short& i, short& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}

void sort(unsigned int& i, unsigned int& j)
{
    std::cout << "IN: void sort(unsigned int& i, unsigned int& j)" << std::endl;

    if (i > j)
    {
        swap(i, j);
    }
}


void sort(int& i, int& j)
{
    std::cout << "IN: void sort(int& i, int& j)" << std::endl;

    if (i > j)
    {
        swap(i, j);
    }
}


void sort(float& i, float& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


void sort(double& i, double& j)
{
    if (i > j)
    {
        swap(i, j);
    }
}


void swap(unsigned char& i, unsigned char& j)
{
    unsigned char temp(i);
    i = j;
    j = temp;
}


void swap(char& i, char& j)
{
    char temp(i);
    i = j;
    j = temp;
}


void swap(unsigned short& i, unsigned short& j)
{
    unsigned short temp(i);
    i = j;
    j = temp;
}


void swap(short& i, short& j)
{
    short temp(i);
    i = j;
    j = temp;
}


void swap(unsigned int& i, unsigned int& j)
{
    unsigned int temp(i);
    i = j;
    j = temp;
}


void swap(int& i, int& j)
{
    int temp(i);
    i = j;
    j = temp;
}


void swap(float& i, float& j)
{
    float temp(i);
    i = j;
    j = temp;
}


void swap(double& i, double& j)
{
    double temp(i);
    i = j;
    j = temp;
}


int main()
{
    int a(-2), b(-1);
    unsigned int c(2), d(1);
    
    sort(a, b);
    sort(c, d);
    
    std::cout << a << " < " << b << std::endl;
    std::cout << c << " < " << d << std::endl;
    
    return (0);
}

