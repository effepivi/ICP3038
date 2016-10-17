#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
int main() {
    std::vector<int> v0(5);                     // 5 copies of default value of int: 0
    std::vector<int> v1(5, 1);                  // 5 copies of the provided value 1
    std::fill(std::begin(v0), std::end(v0), 2); // fill the range with the provided value
    std::fill_n(std::back_inserter(v0), 5, 3);  // fill (push_back) 5 more provided values
    std::copy(std::begin(v0), std::end(v0), std::ostream_iterator<int>(std::cout, "\n"));
    return 0;
}
