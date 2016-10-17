#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
int main() {
    std::vector<int> v = { 7, 42, 1, 7, -13 };
    std::sort(std::begin(v), std::end(v));
    std::swap(v.front(), v.back()); // swap any 2 references, doesn't require container
    std::copy(std::begin(v), std::end(v), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl << std::accumulate(std::begin(v), std::end(v), 0) << std::endl;
    std::cout << *std::max_element(std::begin(v), std::end(v)) << std::endl;
    return 0;
}
