#include <string>
#include <iostream>

int main()
{
	std::string my_string = "Test";
	std::cout << "Size: " << my_string.size() << std::endl;
	my_string = my_string + " concatenate";
	std::cout << my_string << std::endl;
    
    return 0;
}
