#include <iostream>

using namespace std;

int main()
{
    cout << "Please enter a temperature in Celsius: ";
    float celsius = 0.0;
    cin >> celsius;

    float fahrenheit = 9.0/5.0 * celsius + 32;

    cout << celsius << " degrees Celsius is the same as " << fahrenheit << " degrees Fahrenheit." << endl;

    return 0;
}
