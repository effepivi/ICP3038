#include <iostream>
#include <queue>
int main()
{
    std::queue<int> q;	// FIFO queue
                        // adaptor on some internal container
                        // doesn't allow iteration through elements
    q.push(1); q.push(2); q.push(3);

    while (!q.empty()) {
        std::cout << q.front() << std::endl;
        q.pop();
    }
	
    return 0;
}
