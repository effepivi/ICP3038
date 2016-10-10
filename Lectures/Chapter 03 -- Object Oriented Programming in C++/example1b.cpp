#include "example1.h"

int main()
{
    int* p_global(0);
    MyClass* p_class(0);

    //p_global = &my_global; // Linkage error: Undefined symbols "_my_global", referenced from: _main
    //p_class = new MyClass; // Compilation error: incomplete type 'MyClass'
    
    return 0;
}
