#include <iostream>

#include "Image.h"
#include "gtest/gtest.h"


using namespace std;

// Test the default constructor
TEST(TestContructors, DefaultConstructor)
{
    Image test_default_constructor;
    
    ASSERT_EQ(test_default_constructor.getWidth(), 0);
    ASSERT_EQ(test_default_constructor.getHeight(), 0);
    EXPECT_TRUE(test_default_constructor.getPixelPointer() == NULL);
}

// Test the constructor from a C array
TEST(TestContructors, CArrayConstructor)
{
    float p_c_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Image test_c_array_constructor(p_c_array, 4, 2);

    ASSERT_EQ(test_c_array_constructor.getWidth(), 4);
    ASSERT_EQ(test_c_array_constructor.getHeight(), 2);
    
    size_t k = 0;
    for (size_t j = 0; j < test_c_array_constructor.getHeight(); ++j)
    {
        for (size_t i = 0; i < test_c_array_constructor.getWidth(); ++i, ++k)
        {
            ASSERT_EQ(test_c_array_constructor(i, j), p_c_array[k]);
        }
    }
}

// Test the constructor from a C++ STL vector
TEST(TestContructors, CXXArrayConstructor)
{
    vector<float> p_cxx_array = {1, 2, 3, 4, 5, 6, 7, 8};
    Image test_cxx_array_constructor(p_cxx_array, 2, 4);

    ASSERT_EQ(test_cxx_array_constructor.getWidth(), 2);
    ASSERT_EQ(test_cxx_array_constructor.getHeight(), 4);
    
    size_t k = 0;
    for (size_t j = 0; j < test_cxx_array_constructor.getHeight(); ++j)
    {
        for (size_t i = 0; i < test_cxx_array_constructor.getWidth(); ++i, ++k)
        {
            ASSERT_EQ(test_cxx_array_constructor(i, j), p_cxx_array[k]);
        }
    }
}

// Test the constructor from a constant
TEST(TestContructors, ConstantConstructor)
{
    Image test_constant_constructor(0.0, 6, 3);
    
    ASSERT_EQ(test_constant_constructor.getWidth(), 6);
    ASSERT_EQ(test_constant_constructor.getHeight(), 3);
    
    for (size_t j = 0; j < test_constant_constructor.getHeight(); ++j)
    {
        for (size_t i = 0; i < test_constant_constructor.getWidth(); ++i)
        {
            ASSERT_EQ(test_constant_constructor(i, j), 0.0);
        }
    }
}

// Test the copy constructor
TEST(TestContructors, CopyConstructor)
{
    Image test_constant_constructor(0.0, 6, 3);
    Image test_copy_constructor = test_constant_constructor;
    
    ASSERT_EQ(test_constant_constructor.getWidth(), test_copy_constructor.getWidth());
    ASSERT_EQ(test_constant_constructor.getHeight(), test_copy_constructor.getHeight());
    
    for (size_t j = 0; j < test_constant_constructor.getHeight(); ++j)
    {
        for (size_t i = 0; i < test_constant_constructor.getWidth(); ++i)
        {
            ASSERT_EQ(test_constant_constructor(i, j), test_copy_constructor(i, j));
        }
    }
}

