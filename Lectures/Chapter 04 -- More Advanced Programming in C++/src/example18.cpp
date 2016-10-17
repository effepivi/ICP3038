#include <iostream>
#include <string>
#include <utility>

int main() {
    std::pair<std::string, int> John("John", 19);	// 2-tuple of any two types of data
    std::pair<std::string, int> Paul;
    Paul = std::make_pair("Paul", 17);            // alternative construction
    Paul.second++;                                // accessing the elements
    Paul.first = "George";
    if (Paul.second >= 18)
        std::cout << Paul.first << " is an adult" << std::endl;
    return 0;
}
