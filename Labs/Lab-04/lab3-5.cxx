#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    cout << "The program is: " << argv[0] << endl;

    for (int i = 1; i < argc; ++i)
    {
        cout << "argument " << i << " is: " << argv[i] << endl;
    }
    return 0;
}
