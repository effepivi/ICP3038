#include <iostream>

template<class T>
class A
{
protected:
    int i;
};

template<class T>
class B: A<T>
{
public:
    int foo()
    {
        //return i; // Compilation error: use of undeclared identifier 'i'
        return this->i;
    }

};

int main()
{
    B<int> b;
    std::cout << b.foo() << std::endl;
}
