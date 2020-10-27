---
title: Lab 4 -- An image class
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 5
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---

# Introduction

Last week we start to write our own classes. This week, we'll write a class to hold image data, and that can perform some image processing.

Prepare `Image.h` with:

```cpp
#ifndef __Image_h
#define __Image_h

class Image
{
public:

private:

};

#endif // __Image_h
```

and `Image.cxx` with:
```cpp
#include "Image.h"
```


# Requirements

The class should hold some image data in greyscale using a 1D array of floating point numbers.
It should be able to perform some arithmetic operations as well as boolean operations.
It should hold some statistics data about the pixel values.

## List of attributes

By default attributes will be `private`. I always use `m_` as a prefix, meaning "member". For variables, I use small letters, with every words separated with an underscore. We need a robust "coding standard". Also have a look at the way I write my comments in the header files. We are going to generate some automatic docs from our code using [Doxygen](https://www.doxygen.org/). Install it if you don't have it yet.

```cpp
    std::vector<float> m_pixel_data; //< The pixel data in greyscale as a 1D array (here STL vector)
    size_t m_width; //< The number of columns
    size_t m_height; //< The number of rows
    float m_min_pixel_value; //< The smallest pixel value
    float m_max_pixel_value; //< The largest pixel value
    float m_average_pixel_value; //< The average pixel value
    float m_stddev_pixel_value; //< The standard deviation of the pixel values

    bool m_stats_up_to_date; //< True if m_min_pixel_value, m_max_pixel_value, m_average_pixel_value and m_stddev_pixel_value are up-to-date, false otherwise
```


In order to use `std::vector`, make sure to include the `<vector>` header file in `Image.h`.

## Constructors

Now we know all the data held by the class, we need to initialise it with constructors. There are 7 constructors that we discussed in the (virtual) classroom. Make sure to declare them as public members of the class:

1. Default constructor to create an empty  image;
2. Copy constructor to copy an existing image;
3. A constructor to load the data from a 1D C array currently stored in the RAM;
4. A constructor to load the data from a 1D C++ STL vector currently stored in the RAM;
5. A constructor to create a uniform image;
6. A constructor loading the data from a file (C string); and
7. A constructor loading the data from a file (C++ string)


```cpp
    //--------------------------------------------------------------------------
    /// Default constructor: Create an empty image
    //--------------------------------------------------------------------------
    Image();


    //--------------------------------------------------------------------------
    /// Copy constructor: Copy an existing image
    /**
    * @param anImage: The image to copy
    */
    //--------------------------------------------------------------------------
    Image(const Image& anImage);


    //--------------------------------------------------------------------------
    /// Constructor: Copy an 1D array
    /**
    * @param anImage: The pixel data
    * @param aWidth: The image width
    * @param aHeight: The image height
    */
    //--------------------------------------------------------------------------
    Image(const float* anImage, size_t aWidth, size_t aHeight);


    //--------------------------------------------------------------------------
    /// Constructor: Copy an 1D array
    /**
    * @param anImage: The pixel data
    * @param aWidth: The image width
    * @param aHeight: The image height
    */
    //--------------------------------------------------------------------------
    Image(const std::vector<float>& anImage, size_t aWidth, size_t aHeight);


    //--------------------------------------------------------------------------
    /// Constructor: Copy a uniform image from a constant value
    /**
    * @param aConstant: The default pixel value
    * @param aWidth: The image width
    * @param aHeight: The image height
    */
    //--------------------------------------------------------------------------
    Image(float aConstant, size_t aWidth, size_t aHeight);


    //--------------------------------------------------------------------------
    /// Constructor: Load a file from the disk
    /**
    * @param aFilename: The name of the file to load
    */
    //--------------------------------------------------------------------------
    Image(const char* aFilename);


    //--------------------------------------------------------------------------
    /// Constructor: Load a file from the disk
    /**
    * @param aFilename: The name of the file to load
    */
    //--------------------------------------------------------------------------
    Image(const std::string& aFilename);
```

In `Image.cxx`, we must initialise all the class attributes (if applicable) using initialisation lists.
I wrote "if applicable" as the STL vector class that we use to store pixel data also has a default constructor (we don't have to call it as it'll be done automatically: it's the point of a default constructor).
In the initialisation lists, follow the same order as the declarations in the class declaration (faster code). If you don't on a Mac, CLang will generate a warning. g++ and MSVC++ won't.

```cpp
//---------------------------
Image::Image():
//---------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//---------------------------
{}


//-------------------------------------------------------
Image::Image(const Image& anImage):
//-------------------------------------------------------
    m_pixel_data(anImage.m_pixel_data),
    m_width(anImage.m_width),
    m_height(anImage.m_height),
    m_min_pixel_value(anImage.m_min_pixel_value),
    m_max_pixel_value(anImage.m_max_pixel_value),
    m_average_pixel_value(anImage.m_average_pixel_value),
    m_stddev_pixel_value(anImage.m_stddev_pixel_value),
    m_stats_up_to_date(anImage.m_stats_up_to_date)
//-------------------------------------------------------
{}


//----------------------------------------------------------------
Image::Image(const float* anImage, size_t aWidth, size_t aHeight):
//----------------------------------------------------------------
    m_pixel_data(anImage, anImage + aWidth * aHeight),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(false)
//----------------------------------------------------------------
{}


//-----------------------------------------------------------------------------
Image::Image(const std::vector<float>& anImage, size_t aWidth, size_t aHeight):
//-----------------------------------------------------------------------------
    m_pixel_data(anImage),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(false)
//-----------------------------------------------------------------------------
{}


//-----------------------------------------------------------
Image::Image(float aConstant, size_t aWidth, size_t aHeight):
//-----------------------------------------------------------
    m_pixel_data(aConstant, aWidth * aHeight),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(aConstant),
    m_max_pixel_value(aConstant),
    m_average_pixel_value(aConstant),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//-----------------------------------------------------------
{}


//----------------------------------
Image::Image(const char* aFilename):
//----------------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//---------------------------
{
    load(aFilename);
}


//-----------------------------------------
Image::Image(const std::string& aFilename):
//-----------------------------------------
    m_width(0),
    m_height(0),
    m_min_pixel_value(0),
    m_max_pixel_value(0),
    m_average_pixel_value(0),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//-----------------------------------------
{
    load(aFilename);
}
```


## Load the data from files

It appears that we need to declare in `Image.h`:

```cpp
//--------------------------------------------------------------------------
/// Constructor: Load a file from the disk
/**
* @param aFilename: The name of the file to load
*/
//--------------------------------------------------------------------------
void load(const char* aFilename);


//--------------------------------------------------------------------------
/// Constructor: Load a file from the disk
/**
* @param aFilename: The name of the file to load
*/
//--------------------------------------------------------------------------
void load(const std::string& aFilename);
```

and add an empty definition for now in `Image.cxx`:

```cpp
//-------------------------------------
void Image::load(const char* aFilename)
//-------------------------------------
{

}


//--------------------------------------------
void Image::load(const std::string& aFilename)
//--------------------------------------------
{

}
```


## CMakeLists.txt

Maybe it's a good time to compile and see if we've made no mistake. I doubt it, there are always mistakes!

Create the `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 3.10)

PROJECT (ICP3038-img-class VERSION 0.1)

ADD_EXECUTABLE(test-constructors
    include/Image.h
    src/Image.cxx
    src/test-constructors.cxx)

TARGET_INCLUDE_DIRECTORIES(test-constructors PUBLIC include)
```

## Create a test file

In `test-constructors.cxx`, we are going to test what? The constructors!

- 1st, we need to include the header files (`<iostream>` and `"Image.h"`).
- 2nd, create an empty main.
- Then, call all the constructors in the main:

```cpp
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
```

## Compile

You can now compile, but...

```bash
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
In file included from /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-05-an_image_class/src/Image.cxx:1:0:
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-05-an_image_class/include/Image.h:61:22: error: ‘string’ in namespace ‘std’ does not name a type
     Image(const std::string& aFilename);
```

oops. I forgot to include `<string>` header file in `Image.h`. Well, add it to fix the error.

## Unit testing

Question: How are we going to test the code????
Answer: use `operator<<`, accessors (getters) on `m_width`, `m_height`, `m_pixel_data`.

In the `main` of `test-constructors.cxx`, add something like:

```cpp
cout << test_default_constructor.getWidth() << " " << test_default_constructor.getHeight() << " " << test_default_constructor.getPixelPointer() << endl << endl;
cout << test_fileName_C << endl << endl;
cout << test_fileName_C << endl << endl;
cout << test_c_array_constructor << endl << endl;
cout << test_cxx_array_constructor << endl << endl;
cout << test_constant_constructor << endl;
cout << test_copy_constructor << endl;
```

The output should be in the terminal should:

```bash
0 0 0





1 2 3 4
5 6 7 8

1 2
3 4
5 6
7 8

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

We could also write the unit test in `CMakeLists.txt`. But first, let's make it compile by adding the missing methods and operators.

## Adding the missing methods and operators

At the top of the header file, just after the header inclusions, add the following header inclusion, then these declarations:

```cpp
#include <iostream>

class Image;
std::ostream& operator<<(std::ostream& anOutputStrem, const Image& anImage);
```

In the class add the missing public methods and operators:

```cpp
//--------------------------------------------------------------------------
/// Accessor on a given pixel
/**
* @param col: coordinate of the pixel along the horizontal axis
* @param row: coordinate of the pixel along the vertical axis
* @return the corresponding pixel value
*/
//--------------------------------------------------------------------------
const float& operator()(size_t col, size_t row) const;


//--------------------------------------------------------------------------
/// Accessor on a given pixel
/**
* @param col: coordinate of the pixel along the horizontal axis
* @param row: coordinate of the pixel along the vertical axis
* @return the corresponding pixel value
*/
//--------------------------------------------------------------------------
float& operator()(size_t col, size_t row);


//--------------------------------------------------------------------------
/// Accessor on the image width in number of pixels
/**
* @return the width of the image in number of pixels
*/
//--------------------------------------------------------------------------
size_t getWidth() const;


//--------------------------------------------------------------------------
/// Accessor on the image height in number of pixels
/**
* @return the height of the image in number of pixels
*/
//--------------------------------------------------------------------------
size_t getHeight() const;


//--------------------------------------------------------------------------
/// Accessor on the raw pixel data
/**
* @return the pointer on the raw pixel data
*/
//--------------------------------------------------------------------------
const float* getPixelPointer() const;


//--------------------------------------------------------------------------
/// Accessor on the raw pixel data
/**
* @return the pointer on the raw pixel data
*/
//--------------------------------------------------------------------------
float* getPixelPointer();
```


Add this function in `Image.cxx`:

```cpp
//--------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& anOutputStream, const Image& anImage)
//--------------------------------------------------------------------------
{
    // Output all the rows
    for (unsigned row = 0; row < anImage.getHeight(); ++row)
    {
        // Output all the columns
        for (unsigned col = 0; col < anImage.getWidth(); ++col)
        {
            // Output the corresponding pixel
            anOutputStream << anImage(col, row);

            // Add a space charater if needed
            if (col < anImage.getWidth() - 1)
            {
                anOutputStream << " ";
            }
        }

        // Add a end of line if needed
        if (row < anImage.getHeight() - 1)
        {
            anOutputStream << std::endl;
        }
    }

    // Return the stream
    return anOutputStream;
}
```

Try to compile (to be on the safe side). The compilation should work. The linkage should not.
I get:

```bash
Scanning dependencies of target test-constructors
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
[ 66%] Building CXX object CMakeFiles/test-constructors.dir/src/test-constructors.cxx.o
[100%] Linking CXX executable test-constructors
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: CMakeFiles/test-constructors.dir/src/Image.cxx.o: in function `operator<<(std::ostream&, Image const&)':
Image.cxx:(.text+0x23): undefined reference to `Image::getHeight() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: Image.cxx:(.text+0x47): undefined reference to `Image::getWidth() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: Image.cxx:(.text+0x66): undefined reference to `Image::operator()(unsigned long, unsigned long) const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: Image.cxx:(.text+0x8b): undefined reference to `Image::getWidth() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: Image.cxx:(.text+0xbf): undefined reference to `Image::getHeight() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: CMakeFiles/test-constructors.dir/src/test-constructors.cxx.o: in function `main':
test-constructors.cxx:(.text+0x1cf): undefined reference to `Image::getWidth() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: test-constructors.cxx:(.text+0x1f8): undefined reference to `Image::getHeight() const'
/usr/lib64/gcc/x86_64-suse-linux/7/../../../../x86_64-suse-linux/bin/ld: test-constructors.cxx:(.text+0x212): undefined reference to `Image::getPixelPointer()'
collect2: error: ld returned 1 exit status
make[2]: *** [CMakeFiles/test-constructors.dir/build.make:99: test-constructors] Error 1
make[1]: *** [CMakeFiles/Makefile2:76: CMakeFiles/test-constructors.dir/all] Error 2
make: *** [Makefile:84: all] Error 2
```

All good, really. We just need to add the accessor definitions in `Image.cxx` now.
I'll do some error checks. Always do error checks. Assume the class user will make mistakes.
Add the following header inclusions:

```cpp
#include <sstream>        // Format nice error messages
#include <stdexcept>      // std::out_of_range exception
```

and add the methods:

```cpp
//----------------------------------------------------------
const float& Image::operator()(size_t col, size_t row) const
//----------------------------------------------------------
{
    // Check if the coordinates are valid, if not throw an error
    if (col < 0 || col >= m_width || row < 0 || row >= m_height)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Pixel(" << col << ", " << row << ") does not exist. The image size is: " << m_width << "x" << m_height << std::endl;

        // Throw an exception
        throw std::out_of_range(error_message.str());
    }

    return m_pixel_data[row * m_width + col];
}


//----------------------------------------------
float& Image::operator()(size_t col, size_t row)
//----------------------------------------------
{
    // Check if the coordinates are valid, if not throw an error
    if (col < 0 || col >= m_width || row < 0 || row >= m_height)
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Pixel(" << col << ", " << row << ") does not exist. The image size is: " << m_width << "x" << m_height << std::endl;

        // Throw an exception
        throw std::out_of_range(error_message.str());
    }

    // To be on the safe side, turn the flag off
    m_stats_up_to_date = false;

    return m_pixel_data[row * m_width + col];
}


//----------------------------
size_t Image::getWidth() const
//----------------------------
{
    return m_width;
}


//-----------------------------
size_t Image::getHeight() const
//-----------------------------
{
    return m_height;
}


//-----------------------------------------
const float* Image::getPixelPointer() const
//-----------------------------------------
{
    return &m_pixel_data[0];
}

//-----------------------------
float* Image::getPixelPointer()
//-----------------------------
{
    // To be on the safe side, turn the flag off
    m_stats_up_to_date = false;

    return &m_pixel_data[0];
}
```

See that whenever a method can allow a modification of the pixel data, I turn off the     `m_stats_up_to_date` flag. It's the methods that do not end with the `const` keyword.

Compile and run your code. The output I get is:

```bash
Scanning dependencies of target test-constructors
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
[ 66%] Building CXX object CMakeFiles/test-constructors.dir/src/test-constructors.cxx.o
[100%] Linking CXX executable test-constructors
[100%] Built target test-constructors
0 0 0





1 2 3 4
5 6 7 8

1 2
3 4
5 6
7 8

Segmentation fault (core dumped)
```

My program has crashed :-( What could possibly be wrong? The default constructor has worked. The ones with the C array or the STL vector have worked. It must be the one with the constant value. Let's have a look at it:

```cpp
//-----------------------------------------------------------
Image::Image(float aConstant, size_t aWidth, size_t aHeight):
//-----------------------------------------------------------
    m_pixel_data(aConstant, aWidth * aHeight),
    m_width(aWidth),
    m_height(aHeight),
    m_min_pixel_value(aConstant),
    m_max_pixel_value(aConstant),
    m_average_pixel_value(aConstant),
    m_stddev_pixel_value(0),
    m_stats_up_to_date(true)
//-----------------------------------------------------------
{}
```


How did I create the image:
```cpp
// Test the constructor from a constant
Image test_constant_constructor(0.0, 6, 3);
```

Anything too obvious. I am going to replace

```cpp
cout << test_constant_constructor << endl;
```

with

```cpp
cout << test_constant_constructor.getWidth() << " " << test_constant_constructor.getHeight() << " " << test_constant_constructor.getPixelPointer() << endl << endl;
```

Compile and run your code. The output I get is:

```bash
Scanning dependencies of target test-constructors
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/test-constructors.cxx.o
[ 66%] Linking CXX executable test-constructors
[100%] Built target test-constructors
0 0 0





1 2 3 4
5 6 7 8

1 2
3 4
5 6
7 8

6 3 0

Segmentation fault (core dumped)
```

Ah. The pointer is NULL. Meaning `m_pixel_data(aConstant, aWidth * aHeight),` is wrong. oops. Look at [https://en.cppreference.com/w/cpp/container/vector/vector](https://en.cppreference.com/w/cpp/container/vector/vector). I see:

```cpp
explicit vector( size_type count,

                 const T& value = T(),
                 const Allocator& alloc = Allocator());
```

The first parameter of the vector constructor is the number of elements, the second one the default value. My mistake. Let's swap the two values:

```cpp
m_pixel_data(aWidth * aHeight, aConstant),
```

Compile and run your code. The output I get is:

```bash
Scanning dependencies of target test-constructors
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
[ 66%] Linking CXX executable test-constructors
[100%] Built target test-constructors
0 0 0





1 2 3 4
5 6 7 8

1 2
3 4
5 6
7 8

6 3 0x1538f00

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

Let's reverse our change in `test-constructors.cxx`.

Compile and run your code. The output I get is:

```bash
Scanning dependencies of target test-constructors
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
[ 66%] Linking CXX executable test-constructors
[100%] Built target test-constructors
0 0 0





1 2 3 4
5 6 7 8

1 2
3 4
5 6
7 8

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
```

which is EXACTLY the same as what I expected.
We are not going to write proper unit tests yet as CMake is too basic for that. We'll try something else next week. [GTest](https://github.com/google/googletest), which is very popular.

## Assignment operators

Add the declaration of the assignment operators (just after the constructors):

```cpp
//--------------------------------------------------------------------------
/// Assignment operator
/**
* @param anInputImage: The image to copy
* @return the new image
*/
//--------------------------------------------------------------------------
Image& operator=(const Image& anInputImage);


//--------------------------------------------------------------------------
/// Assignment operator
/**
* @param aFilename: The name of the file to load
* @return the new image
*/
//--------------------------------------------------------------------------
Image& operator=(const char* aFileName);


//--------------------------------------------------------------------------
/// Assignment operator
/**
* @param aFilename: The name of the file to load
* @return the new image
*/
//--------------------------------------------------------------------------
Image& operator=(const std::string& aFileName);
```

and the definitions:

```cpp
//------------------------------------------------
Image& Image::operator=(const Image& anInputImage)
//------------------------------------------------
{
    return *this;
}


//--------------------------------------------
Image& Image::operator=(const char* aFileName)
//--------------------------------------------
{
    return *this;
}


//---------------------------------------------------
Image& Image::operator=(const std::string& aFileName)
//---------------------------------------------------
{
    return *this;
}
```

**The assignment operators ALWAYS return a reference of the instance (`*this`).** In both the operators loading the data from files, just call `load(aFileName);`.
For the assignment operator that copies an existing image, copy all the attributes:

```cpp
m_pixel_data = anInputImage.m_pixel_data;
m_width = anInputImage.m_width;
m_height = anInputImage.m_height;
m_min_pixel_value = anInputImage.m_min_pixel_value;
m_max_pixel_value = anInputImage.m_max_pixel_value;
m_average_pixel_value = anInputImage.m_average_pixel_value;
m_stddev_pixel_value = anInputImage.m_stddev_pixel_value;
m_stats_up_to_date = anInputImage.m_stats_up_to_date;
```

## Next Week

If all went well, you now have a functional class to create images. Next week
- we'll add a 3rd party library ([libjpeg-turbo](https://libjpeg-turbo.org/)) to load JPEG files and
- start implementing the statistics methods as well as the arithmetic operators.
- That means we'll be able to run some very basic image processing based on point operators.
- We'll also integrate a 3rd party library ([GTest](https://github.com/google/googletest)) for unit testing.
- We'll generate the automatic documentation from the header file.

Don't worry if both the [libjpeg-turbo](https://libjpeg-turbo.org/) and [GTest](https://github.com/google/googletest) are not installed on your computer. CMake will take care of it.
