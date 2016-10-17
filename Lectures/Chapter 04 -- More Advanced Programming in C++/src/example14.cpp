#include <iostream>
#include <vector>
int main()
{
    std::vector<int> v = { 7, 42, 1, 7, -13 };  // initializer list since C++11
    v.push_back(11);                            // add another element to the end
    std::cout << v[5] << std::endl << std::endl;// some containers behave like arrays
    for (std::vector<int>::iterator ite = v.begin(); ite != v.end(); ++ite)
    
        *ite = 5;
        std::cout << *ite << std::endl;         // iterators behave like pointers

    return 0;
}
