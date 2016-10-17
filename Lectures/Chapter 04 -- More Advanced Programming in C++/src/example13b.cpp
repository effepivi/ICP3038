#include <iostream>
#include <string>
int main()
{
    std::string hi("Hi");
    hi += "ya";
    const std::string name = "John";
    if (name == "John")
        std::cout << hi << " " << name <<
            '!' << std::endl;
    return 0;
}
