#include <iostream>
#include <iterator>
#include <set>
int main() {
    std::set<int> s = { 7, 42, 1, 7, -13 };	// set in maths sense; internally sorted
    std::cout << s.size() << std::endl;		// no duplicate elements
    for (auto it = std::begin(s); it != std::end(s); ++it)	// allows iteration
        std::cout << *it << std::endl;
    s.insert(12); s.insert(7);			// insert, returns pair<iterator, bool>
    s.erase(-13); s.erase(5);			// remove, returns number erased
    if (s.find(42) != s.end())			// returns iterator if found or else end()
        std::cout << "s contains 42" << std::endl;
    return 0;
}
