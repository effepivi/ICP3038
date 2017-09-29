#include<iostream>
using namespace std;

int main()
{
	int a[5] = { 5, 4, 3, 2, 1 };
	int b[10] = { 2, 1 }; // elements b[2] to b[9] will be set to 0
	int c[10] = {}; // all elements will be set to 0
	int d[10];  // The elements in d will be uninitialized

	for (unsigned int i(0); i < 5; ++i)
	{
		cout << "a[" << i << "] = " << a[i] << endl;
	}
	cout << endl;

	for (unsigned int i(0); i < 10; ++i)
	{
		cout << "b[" << i << "] = " << b[i] << endl;
	}
	cout << endl;

	for (unsigned int i(0); i < 10; ++i)
	{
		cout << "c[" << i << "] = " << c[i] << endl;
	}
	cout << endl;

	for (unsigned int i(0); i < 10; ++i)
	{
		cout << "d[" << i << "] = " << d[i] << endl;
	}

	return 0;
}
