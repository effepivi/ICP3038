#include <iostream>

#include "example1.h"

using namespace std;


int my_global = 1;


class MyClass
{
public:
    void myMethod( int a )
    {
        cout << a << endl;
    }
};


int main()
{
    int* p_global(0);
    p_global = &my_global;

    MyClass* p_class(0);
    
    p_class = new MyClass;
    p_class->myMethod(*p_global++);
    delete p_class;
    
    MyClass* p_class_set(0);
    p_class_set = new MyClass[10];
    for (unsigned int i = 0; i < 10; ++i)
    {
        p_class_set[i].myMethod(*p_global++);
    }
    delete [] p_class_set;
    
    return 0;
}
