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

By default attributes will be private. I use `m_` as a prefix, meaning "member". For variables, I use small letters, with every words separated with an underscore.

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

Now we know all the data held by the class, we need to initialise it with constructors. There are 6 constructors that we discussed in the (virtual) classroom. Make sure to declare them as public members of the class:

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

In `Image.cxx`, make sure to initialise all the class attributes (if applicable) using initialisation lists. In the initialisation lists, follow the same order as the declarations in the class (faster code). If you don't CLang on Mac will generate a warning, g++ and MSVC++ won't.

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

It appears we need to declare in `Image.h`:

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

1st, we need to include the header files (`<iostream>` and `"Image.h"`)

## Compile

```bash
[ 33%] Building CXX object CMakeFiles/test-constructors.dir/src/Image.cxx.o
In file included from /home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-05-an_image_class/src/Image.cxx:1:0:
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-05-an_image_class/include/Image.h:61:22: error: ‘string’ in namespace ‘std’ does not name a type
     Image(const std::string& aFilename);
```

oops. I forgot to include `<string>` header file in `Image.h`. Well, add it to fix the error.
