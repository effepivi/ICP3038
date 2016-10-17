#include <iostream>
#include <vector>
#include <iterator>
int main()
{
    std::vector<int> v = { 7, 42, 1, 7, -13 };
    typedef std::vector<int>::iterator foo;		// define a shorter name to save typing
    for (foo ite = v.begin(); ite != v.end(); ++ite)
        std::cout << *ite << std::endl;
    
    for (auto ite = std::begin(v); ite != std::end(v); ++ite) // type inference and universal begin and end
                                                              // iterators since C++11
        std::cout << *ite << std::endl;
    return 0;
}
