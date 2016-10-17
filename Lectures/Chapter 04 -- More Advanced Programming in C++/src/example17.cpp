#include <iostream>
#include <iterator>
#include <deque>

int main()
{
    std::deque<int> d(1, 2);	// Double-Ended QUEue, pronounced "deck"
        // initialized with 1 copy of the element 2
        // like a vector, O(1) insert/remove from end, O(n) insert/remove in middle
        // unlike a vector, also O(1) insert/remove from front
    d.push_front(1); d.push_front(0); d.push_back(3); d.push_back(4);
    d.pop_front(); d.pop_back();
    for (auto it = std::begin(d); it != std::end(d); ++it)
        std::cout << *it << std::endl;

    return 0;
}
