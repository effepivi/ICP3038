#include <iostream>
#include <string>
#include <iterator>
#include <map>
int main() {
    std::map<std::string, int> m;  // map in maths sense; internally sorted by key
    m["Paul"] = 17;                // inserting key-value pairs
    m["John"] = 19;
    if (m.find("Paul") != m.end()) m.find("Paul")->second++;  // accessing value from key
    if (m.find("John") != m.end()) m["John"]++;               // much simpler
    for (auto it = std::begin(m); it != std::end(m); ++it)    // iterator to pair<key,value>
        std::cout << it->first << '\t' << it->second << std::endl;
    return 0;
}
