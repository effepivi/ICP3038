#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Wrong number of command line arguments." << endl;
        cerr << "Usage:\t" << argv[0] << "  temp_in_celcius" << endl;
        return 1;
    }

    float celsius = stof(argv[1]);


    float fahrenheit = 9.0 / 5.0 * celsius + 32;

    cout << celsius << " degrees Celsius is the same as " << fahrenheit << " degrees Fahrenheit." << endl;

    return 0;
}
