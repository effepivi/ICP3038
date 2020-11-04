#include <iostream>

#include "Image.h"
#include "gtest/gtest.h"


using namespace std;

// Test the default constructor
TEST(Operators, FloatImageOperators)
{
    Image input_image({0, 1, 2, 3, 4, 5, 6 , 7}, 4, 2);

    Image image_product = 2 * input_image;
    ASSERT_EQ(image_product.getWidth(), input_image.getWidth());
    ASSERT_EQ(image_product.getHeight(), input_image.getHeight());
    
    Image image_sum = 2 + input_image;
    ASSERT_EQ(image_sum.getWidth(), input_image.getWidth());
    ASSERT_EQ(image_sum.getHeight(), input_image.getHeight());
    
    cout << image_sum << endl;
    size_t k = 0;
    for (size_t j = 0; j < image_product.getHeight(); ++j)
    {
        for (size_t i = 0; i < image_product.getWidth(); ++i, ++k)
        {
            ASSERT_NEAR(image_product(i, j), k * 2, 1e-6);
            ASSERT_NEAR(image_sum(i, j), k + 2, 1e-6);
        }
    }
}

