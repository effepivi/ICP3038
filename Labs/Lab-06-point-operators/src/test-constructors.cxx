#include <iostream>

#include "Image.h"


using namespace std;

int main()
{
    // Test the default constructor
    Image test_default_constructor;

    // Test the constructors from C and C++ strings
    const char* file_name_C = "sky.jpg";
    string file_name_CXX = file_name_C;

    Image test_fileName_C(file_name_C);
    Image test_fileName_CXX(file_name_CXX);

    // Test the constructor from a C array
    float p_c_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Image test_c_array_constructor(p_c_array, 4, 2);

    // Test the constructor from a C++ STL vector
    vector<float> p_cxx_array = {1, 2, 3, 4, 5, 6, 7, 8};
    Image test_cxx_array_constructor(p_cxx_array, 2, 4);

    // Test the constructor from a constant
    Image test_constant_constructor(0.0, 6, 3);

    // Test the copy constructor
    Image test_copy_constructor = test_constant_constructor;

    cout << test_default_constructor.getWidth() << " " << test_default_constructor.getHeight() << " " << test_default_constructor.getPixelPointer() << endl << endl;
    cout << test_fileName_C << endl << endl;
    cout << test_fileName_C << endl << endl;
    cout << test_c_array_constructor << endl << endl;
    cout << test_cxx_array_constructor << endl << endl;
    cout << test_constant_constructor << endl << endl;
    cout << test_copy_constructor << endl;

    return 0;
}
