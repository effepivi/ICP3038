#include <iostream>

class B
{
public:
    B():
        i(1)
    {}
    
    int foo()
    {
        int i(123);
        return this->i;
    }

protected:
    int i;
};

class C
{
public:
    C():
        i(2)
    {}
    
    int foo()
    {
        int i(123);
        return this->i;
    }

protected:
    int i;
};

int main()
{
    B b;
    C c;
    std::cout << b.foo() << std::endl;
    std::cout << c.foo() << std::endl;
}
