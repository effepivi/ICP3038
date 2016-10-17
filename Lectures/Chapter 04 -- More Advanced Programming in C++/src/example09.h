#ifndef EXAMPLE6_H
#define EXAMPLE6_H

#include <iostream>

// Declarations
template<typename T> void swap(T& i, T&j);
template<typename T> void sort(T& i, T&j);

// Definitions
template<typename T> void swap(T& i, T&j)
{
    T temp(i);
    i = j;
    j = temp;
}

template<typename T> void sort(T& i, T&j)
{
    std::cout << "IN: void sort(T& i, T& j)" << std::endl;

    if (i > j)
    {
        swap<T>(i, j);
    }
}


#endif
