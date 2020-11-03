# This week

- We'll also integrate a 3rd party library ([GTest](https://github.com/google/googletest)) for unit testing.
- we'll add a 3rd party library ([libjpeg-turbo](https://libjpeg-turbo.org/)) to load JPEG files and
- start implementing the statistics methods as well as the arithmetic operators.
- That means we'll be able to run some very basic image processing based on point operators.
- We'll generate the automatic documentation from the header file.

Don't worry if both the [libjpeg-turbo](https://libjpeg-turbo.org/) and [GTest](https://github.com/google/googletest) are not installed on your computer. CMake will take care of it.
But before we start, make sure to install [Doxygen](https://www.doxygen.org/) from [https://www.doxygen.org/](https://www.doxygen.org/).


# Integrating GoogleTest in CMake

We saw last week that testing our code with unit testing was limited with CMake's built-in functionalities. This week we address this deficiency using GoogleTest (GTest).

We first need to revise our CMake script to download and compile GTest.

1. Increment the project version number:

```cmake
PROJECT (ICP3038-img-class VERSION 0.2)
```

2. Enable C++ 11, just in case:

```cmake
# Use C++ 11
set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++11 is required (i.e. not optional)
set(CMAKE_CXX_EXTENSIONS OFF) # without compiler extensions like gnu++11
```

3. Build GTest:

```cmake
# Build GoogleTest
INCLUDE(cmake/External_GTest.cmake)
```

4. Enable unit testing

```cmake
enable_testing()
```

5. Compilation and linkage:

```cmake
# Compilation
ADD_EXECUTABLE(test-constructors
    include/Image.h
    src/Image.cxx
    src/test-constructors.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-constructors PUBLIC include)
target_include_directories(test-constructors PUBLIC ${GTEST_INCLUDE_DIRS})

# Add linkage
target_link_directories(test-constructors PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-constructors ${GTEST_LIBRARIES})

# Add dependency
ADD_DEPENDENCIES(test-constructors googletest)
```

6. Addingthe test to CTest

```cmake
# Add the unit test
add_test (test-constructors test-constructors)
```

[My final version of CMakeLists.txt can be find in this directory](./CMakeLists.txt)


# Converting our tests from `cout` to GTest

We are now editing `test-constructors.cxx`.

1. Add the header file:

```cpp
#include "gtest/gtest.h"
```

2. For now, just comment the main. Will cut/paste some code out of it.
3. Create a new test:

```cpp
TEST(TestContructors, DefaultConstructor)
{
    ...
}
```
we'll replace `...` with the corresponding code from the main (use cut/paste):
```cpp
// Test the default constructor
Image test_default_constructor;

cout << test_default_constructor.getWidth() << " " << test_default_constructor.getHeight() << " " << test_default_constructor.getPixelPointer() << endl << endl;
```
Well, we are getting rid of `cout`. We know that `test_default_constructor.getWidth()`, and `test_default_constructor.getHeight()` must return 0. `test_default_constructor.getPixelPointer()` must return the NULL pointer.
Replace `cout << test_default_constructor.getWidth() << " " << test_default_constructor.getHeight() << " " << test_default_constructor.getPixelPointer() << endl << endl;` with:
```cpp
ASSERT_EQ(test_default_constructor.getWidth(), 0);
ASSERT_EQ(test_default_constructor.getHeight(), 0);
EXPECT_TRUE(test_default_constructor.getPixelPointer() == NULL);
```

4. Compile and run your test. I see:

```bash
Running tests...
Test project /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-06-point-operators/bin
    Start 1: Constructors
1/1 Test #1: Constructors .....................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

5. Do the same for the constructor that makes use of a C array

Cut out

```cpp
// Test the constructor from a C array
float p_c_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
Image test_c_array_constructor(p_c_array, 4, 2);

cout << test_c_array_constructor << endl << endl;
```
and paste it in a new test:

```cpp
TEST(TestContructors, CArrayConstructor)
{
    float p_c_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Image test_c_array_constructor(p_c_array, 4, 2);

    cout << test_c_array_constructor << endl << endl;
}
```
Replace the `cout` with something more suitable for an actual unit test. We make sure the image size is correct with:
```cpp
ASSERT_EQ(test_c_array_constructor.getWidth(), 4);
ASSERT_EQ(test_c_array_constructor.getHeight(), 2);
```

We make sure the pixel data is correct with:
```cpp
size_t k = 0;
for (size_t j = 0; j < test_c_array_constructor.getHeight(); ++j)
{
    for (size_t i = 0; i < test_c_array_constructor.getWidth(); ++i, ++k)
    {
        ASSERT_EQ(test_c_array_constructor(i, j), p_c_array[k]);
    }
}
```
Compile and run your test.

6. Do the same for the constructor that makes use of a C++ vector:

```cpp
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
```

Compile and run your test.

7. Now, you may get the idea. Add the next unit test, for a constant image.
You must check the validity of the image size, then the pixel values.
Write the code, compile and run the unit tests.

8. Add the next unit test, for the copy constructor.
You must check the validity of the image size, then the pixel values.
Write the code, compile and run the unit tests.

# Generating the technical documentation.

1. Before you start this part, make sure to install [Doxygen](https://www.doxygen.org/) from [https://www.doxygen.org/](https://www.doxygen.org/).
2. Edit `CMakeLists.txt` again and add at the end of the file.

```cmake
# The documentation build is an option. Set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)

    # Set some variables
    SET (PROJECT_NAME ICP3038-img-class)
    SET (PROJECT_DESCRIPTION "An Image class used in ICP3038 at Bangor University")

    # Set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a custom target
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
```

In CMake, configure. If Doxygen is not installed, you see a warning message:

```
-- Could NOT find Doxygen (missing: DOXYGEN_EXECUTABLE)
CMake Warning at CMakeLists.txt:58 (message):
  Doxygen need to be installed to generate the doxygen documentation
```

If Doxygen is installed, a new target "doc_doxygen" will be created in your project.
When you run it, it will create a new directory "doc_doxygen" in your binary tree. You can find the doc in ["doc_doxygen/html/index.html"](doc_doxygen/html/index.html).
Have a look at your new doc. See why commenting the code (header file) is important?

# Loading JPEG files

1.  Edit `CMakeLists.txt` again and add at after enabling C++ 11:

```cmake
# Find the libJPEG
FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
    add_definitions(-DHAS_LIBJPEG)
ELSE(JPEG_FOUND)
    MESSAGE(WARNING "JPEG not found.")
ENDIF(JPEG_FOUND)
```

2. Install the LibJPEG.

You can find it at
[https://sourceforge.net/projects/libjpeg-turbo/files/2.0.5/libjpeg-turbo-2.0.5-vc64.exe/download](https://sourceforge.net/projects/libjpeg-turbo/files/2.0.5/libjpeg-turbo-2.0.5-vc64.exe/download).

3. Re-run cmake (using the GUI) and configure. Something new should appear.
Adjust the path of the directory where the header file is and the path of the library.

4. In `Image.cxx` add the code to load a JPEG file:

Add the header file if LibJPEG is found

```cpp
#ifdef HAS_LIBJPEG
#include <jerror.h>
#include <jpeglib.h>
#endif
```

5. Edit the corresponding methods:

```cpp
//-------------------------------------
void Image::load(const char* aFilename)
//-------------------------------------
{
#ifdef HAS_LIBJPEG
    // Allocate and initialize a JPEG decompression object
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Specify the source of the compressed data (eg, a file)
    FILE* p_input_file(fopen(aFilename, "rb"));
    if (!p_input_file)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Can't open " << aFilename << std::endl;
        throw std::runtime_error(error_message.str());
    }
    jpeg_stdio_src(&cinfo, p_input_file);

    // Call jpeg_read_header() to obtain image info
    jpeg_read_header(&cinfo, TRUE);

    // Set parameters for decompression
    // Nothing to be done if the defaults are appropriate

    // Start decompression
    jpeg_start_decompress(&cinfo);

    // Save the size of the image
    m_width = cinfo.output_width;
    m_height = cinfo.output_height;
    m_pixel_data.resize(m_width * m_height);

    // Decompress data
    JSAMPROW row_pointer[1];        // pointer to a single row
    int row_stride;                 // physical row width in buffer

    if (cinfo.out_color_space == JCS_RGB)
    {
        row_stride = m_width * 3;   // JSAMPLEs per row in image_buffer
    }
    else if (cinfo.out_color_space == JCS_GRAYSCALE)
    {
        row_stride = m_width;   // JSAMPLEs per row in image_buffer
    }
    // Unknown colour space
    else
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Unknown colour space" << std::endl;
        throw std::runtime_error(error_message.str());
    }

    // Create temporary buffer
    unsigned char* p_rgb_image(new unsigned char[m_width * m_height * 3]);

    // Decompress the data
    while (cinfo.output_scanline < cinfo.output_height)
    {
        row_pointer[0] = & p_rgb_image[cinfo.output_scanline * row_stride];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish decompression
    jpeg_finish_decompress(&cinfo);

    // Release the JPEG decompression object
    jpeg_destroy_decompress(&cinfo);

    // Convert the data
    if (cinfo.out_color_space == JCS_RGB)
    {
        double pixel_value;

        for (size_t i(0); i < m_width * m_height; ++i)
        {
            // Compute the relative luminance from RGB data
            // using Photometric/digital ITU-R
            pixel_value  = 0.2126 * p_rgb_image[i * 3    ];
            pixel_value += 0.7152 * p_rgb_image[i * 3 + 1];
            pixel_value += 0.0722 * p_rgb_image[i * 3 + 2];

            m_pixel_data[i] = pixel_value;
        }
    }
    // Copy the data
    else if (cinfo.out_color_space == JCS_GRAYSCALE)
    {
        for (unsigned int i(0); i < m_width * m_height; ++i)
        {
            m_pixel_data[i] = p_rgb_image[i];
        }
    }

    // Release memory
    delete [] p_rgb_image;

    // The statistics is not up-to-date
    m_stats_up_to_date = false;
#else
    // Format a nice error message
    std::stringstream error_message;
    error_message << "ERROR:" << std::endl;
    error_message << "\tin File:" << __FILE__ << std::endl;
    error_message << "\tin Function:" << __FUNCTION__ << std::endl;
    error_message << "\tat Line:" << __LINE__ << std::endl;
    error_message << "\tMESSAGE: LibJPEG not supported" << std::endl;
    throw std::runtime_error(error_message.str());
#endif
}


//--------------------------------------------
void Image::load(const std::string& aFilename)
//--------------------------------------------
{
    load(aFilename.c_str());
}
```

6. In `CMakeLists.txt` add the header file path:

```cmake
IF(JPEG_FOUND)
    target_include_directories(test-constructors PUBLIC ${JPEG_INCLUDE_DIR})
ENDIF(JPEG_FOUND)
```

7. and modify the linkage:

```cmake
target_link_libraries(test-constructors ${GTEST_LIBRARIES} ${JPEG_LIBRARY})
```

# Saving JPEG files

1. Add the method declarations in the header file:

```cpp
//--------------------------------------------------------------------------
/// Save a JPEG file on the disk
/**
* @param aFilename: The name of the file to save
*/
//--------------------------------------------------------------------------
void saveJPEG(const char* aFilename);


//--------------------------------------------------------------------------
/// Save a JPEG file on the disk
/**
* @param aFilename: The name of the file to save
*/
//--------------------------------------------------------------------------
void saveJPEG(const std::string& aFilename);
```

2. Add the method definitions in the .cxx file:

```cpp
//-----------------------------------------
void Image::saveJPEG(const char* aFilename)
//-----------------------------------------
{
#ifdef HAS_LIBJPEG
    // Allocate and initialize a JPEG compression object
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Specify the destination for the compressed data (eg, a file)
    FILE* p_output_file(fopen(aFilename, "wb"));
    if (!p_output_file)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Can't open " << aFilename << std::endl;
        throw std::runtime_error(error_message.str());
    }
    jpeg_stdio_dest(&cinfo, p_output_file);

    // Set parameters for compression, including image size & colorspace
    cinfo.image_width  = m_width;   // image width in pixels
    cinfo.image_height = m_height;  // image height in pixels
    cinfo.input_components = 3;     // number of color components per pixel
    cinfo.in_color_space = JCS_RGB; // colorspace of input image
    jpeg_set_defaults(&cinfo);

    // Create temporary buffer
    unsigned char* p_rgb_image(new unsigned char[m_width * m_height *3]);

    // Convert the data
    double input_pixel_value;
    unsigned char output_pixel_value;

    for (unsigned int i(0); i < m_width * m_height; ++i)
    {
        input_pixel_value = m_pixel_data[i];

        if (input_pixel_value <= 0.0f)
        {
            output_pixel_value = 0;
        }
        else if (input_pixel_value >= 255.0f)
        {
            output_pixel_value = 255;
        }
        else
        {
            output_pixel_value = input_pixel_value;
        }

        p_rgb_image[i * 3    ] = output_pixel_value;
        p_rgb_image[i * 3 + 1] = output_pixel_value;
        p_rgb_image[i * 3 + 2] = output_pixel_value;
    }


    // Start compression
    jpeg_start_compress(&cinfo, TRUE);

    // Compress data
    JSAMPROW row_pointer[1];        // pointer to a single row
    int row_stride;                 // physical row width in buffer

    row_stride = m_width * 3;   // JSAMPLEs per row in image_buffer

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & p_rgb_image[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish compression
    jpeg_finish_compress(&cinfo);

    // Release the JPEG compression object
    jpeg_destroy_compress(&cinfo);

    // Release memory
    delete [] p_rgb_image;
#else
    // Format a nice error message
    std::stringstream error_message;
    error_message << "ERROR:" << std::endl;
    error_message << "\tin File:" << __FILE__ << std::endl;
    error_message << "\tin Function:" << __FUNCTION__ << std::endl;
    error_message << "\tat Line:" << __LINE__ << std::endl;
    error_message << "\tMESSAGE: LibJPEG not supported" << std::endl;
    throw std::runtime_error(error_message.str());
#endif
}


//------------------------------------------------
void Image::saveJPEG(const std::string& aFilename)
//------------------------------------------------
{
    saveJPEG(aFilename.c_str());
}
```

3. If the LibJPEG is installed properly, you can load a JPEG and save it. Just to see if it works.

# Point operators

**Make sure you compile often**

**Make sure you test often too**

1. Add the two following declarations at the top of the header file, e.g. just after `std::ostream& operator<<(std::ostream& anOutputStream, const Image& anImage);`.

```cpp
Image operator*(float aValue, const Image& anInputImage);
Image operator+(float aValue, const Image& anInputImage);
```

It will enable us to do things like `2 * Image`.

2. Add the definition in the cxx file:

```cpp
//------------------------------------------------------
Image operator*(float aValue, const Image& anInputImage)
//------------------------------------------------------
{
    Image temp = anInputImage;

    float* p_data = temp.getPixelPointer();
    size_t number_of_pixels = temp.getWidth() * temp.getHeight();

    for (size_t i = 0; i < number_of_pixels; ++i)
    {
        *p_data++ *= aValue;
    }

    return temp;
}
```

3. Do the same for `Image operator+(float aValue, const Image& anInputImage)` but make sure to change the sign `*` into `+` and `*=` into `+=`.

4. Test your new operators:

Edit the `CMakeLists.txt` file and add the new test file:

```cmake
# Compilation
ADD_EXECUTABLE(test-operators
    include/Image.h
    src/Image.cxx
    src/test-operators.cxx)

# Add dependency
ADD_DEPENDENCIES(test-operators googletest)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-operators PUBLIC include)
target_include_directories(test-operators PUBLIC ${GTEST_INCLUDE_DIRS})

IF(JPEG_FOUND)
    target_include_directories(test-operators PUBLIC ${JPEG_INCLUDE_DIR})
ENDIF(JPEG_FOUND)

# Add linkage
target_link_directories(test-operators PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-operators ${GTEST_LIBRARIES} ${JPEG_LIBRARY})

# Add the unit test
add_test (Operators test-operators)
```

In `test-operators.cxx`, I used something like:

```cpp
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
```

I created a simple image and manually the product and sum.

Compile, and run the new unit tests. Fix the code if needed.

5. Add the other point operators in the header file:

```cpp
//--------------------------------------------------------------------------
/// Add a constant value to all the pixels of an image
/**
* @param aValue: the value to add
* @return the new image
*/
//--------------------------------------------------------------------------
Image operator+(float aValue) const;


//--------------------------------------------------------------------------
/// Subtract a constant value to all the pixels of an image
/**
* @param aValue: the value to subtract
* @return the new image
*/
//--------------------------------------------------------------------------
Image operator-(float aValue) const;


//--------------------------------------------------------------------------
/// Multiply all the pixels of an image with a constant value
/**
* @param aValue: the value to multiply
* @return the new image
*/
//--------------------------------------------------------------------------
Image operator*(float aValue) const;


//--------------------------------------------------------------------------
/// Divide all the pixels of an image by a constant value
/**
* @param aValue: the divisor
* @return the new image
*/
//--------------------------------------------------------------------------
Image operator/(float aValue) const;
```

6. Add the definitions in the cxx file.


```cpp
//----------------------------------------
Image Image::operator+(float aValue) const
//----------------------------------------
{
    Image temp = *this;

    for (size_t i = 0; i < m_width * m_height; ++i)
    {
        temp.m_pixel_data[i] += aValue;
    }

    return temp;
}
```

Do the remaining 3 operators and add some unit tests.

7. Do the assignment arithmetic operators (`+=`, `-=`, `*=` and `/=`) too.
Add the declarations in the header file and reuse what we've just done in the definitions in the cxx file:

```cpp
//------------------------------------
Image& Image::operator+=(float aValue)
//------------------------------------
{
    *this = *this + aValue;
    return *this;
}


//------------------------------------
Image& Image::operator-=(float aValue)
//------------------------------------
{
    *this = *this - aValue;
    return *this;
}


//------------------------------------
Image& Image::operator*=(float aValue)
//------------------------------------
{
    *this = *this * aValue;
    return *this;
}


//------------------------------------
Image& Image::operator/=(float aValue)
//------------------------------------
{
    *this = *this / aValue;
    return *this;
}
```

8. Contrast enhancement

Now we can do some image processing, as we've seen yesterday:
The following method reuse the point operators we've just done to normalise the image between 0 and 1.

```cpp
//----------------------
Image Image::normalise()
//----------------------
{
    return (*this - getMinValue()) / (getMaxValue() - getMinValue());
}
```

We can use this code as follows in a program to improve the contrast of an input image:

```cpp
Image input(argv[1]);
Image output = 255 * input.normalise();
output.saveJPEG(argv[2]);
```

However, before it works, we need to implement `getMinValue`, `getMaxValue` and `updateStats`. Try to idetify the lazy evaluation that I mentioned in the class.

```cpp
//------------------------
float Image::getMinValue();
//------------------------
{
    if (!m_stats_up_to_date) updateStats();

    return m_min_pixel_value;
}


//------------------------
float Image::getMaxValue()
//------------------------
{
    if (!m_stats_up_to_date) updateStats();

    return m_max_pixel_value;
}


//-----------------------
void Image::updateStats()
//-----------------------
{
    // Need to udate the stats
    if (!m_stats_up_to_date && m_width * m_height)
    {
        m_min_pixel_value = m_pixel_data[0];
        m_max_pixel_value = m_pixel_data[0];
        m_average_pixel_value = m_pixel_data[0];

        for (size_t i = 1; i < m_width * m_height; ++i)
        {
            if (m_min_pixel_value > m_pixel_data[i]) m_min_pixel_value = m_pixel_data[i];
            if (m_max_pixel_value < m_pixel_data[i]) m_max_pixel_value = m_pixel_data[i];

            m_average_pixel_value += m_pixel_data[i];
        }
        m_average_pixel_value /= m_width * m_height;

        m_stddev_pixel_value = 0;
        for (size_t i = 0; i < m_width * m_height; ++i)
        {
            m_stddev_pixel_value += (m_pixel_data[i] - m_average_pixel_value) * (m_pixel_data[i] - m_average_pixel_value);
        }
        m_stddev_pixel_value /= m_width * m_height;
        m_stddev_pixel_value = sqrt(m_stddev_pixel_value);

        m_stats_up_to_date = true;
    }
}
```

# Next  week

We will add another 9 operators and we will perform some image processing tasks on actual images. Why not even create an animation!
