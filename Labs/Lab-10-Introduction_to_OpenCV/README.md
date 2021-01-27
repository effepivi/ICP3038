---
title: Lab 10 -- Introductin to OpenCV in C/C++
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 1 of Semester 2
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---


# Aim and objectives

The aim of today's lab is to become familiar with OpenCV and its usage in C/C++. To achieve this, we will fulfil the objectives as follows:

1.   Create an OpenCV project using CMake;
2.   Display an image using OpenCV;
3.   Convert from RGB to luminance;
4.   Convert from `unsigned char` to `float`;
5.   Save an image into a file;
6.   Apply some basic filtering techniques;
7.   Do some more fun on videos.

To achieve these goals, we will create several programs:

1.  `displayImage.cxx`: A simple program using OpenCV to open an image
    and display it in a window;
2.  `rgb2grey.cxx`: A program to convert a RGB image in a greyscale
    image using OpenCV;
3.  `logScale.cxx`: A program to display an image in the log scale;
4.  `meanFilter.cxx`: A program to perform the mean filter using OpenCV;
5.  `medianFilter.cxx`: A program to perform the median filter using
    OpenCV;
6.  `gaussianFilter.cxx`: A program to perform the Gaussian filter using
    OpenCV.
7.  `cartoonise.cxx`

Note that this semester I am not going to provide any test image. I expect that you test your code using your own data.


# Installing OpenCV

We installed OpenCV in Semester 1. See [Lab 7 on Blending and Segmentation(../Lab-07-Blending-segmentation). I recommend OpenCV 4.5.x.

<!-- Before using OpenCV, you have to make sure it is installed on the
machine you are using. **If it is a University's PC, we will consider
that it is installed (so skip this section).**

-   On Mac, OpenCV is available via Homebrew (`brew install opencv3`),
    Fink and Macports;

-   Most Linux distributions have packages for OpenCV. Make sure you
    install the `-devel` package;

-   There are pre-compiled versions on <http://www.opencv.org/> that can
    be used on Windows.

    1.  **Go to OpenCV's website** at <http://www.opencv.org/>.

    2.  **Download the latest version of OpenCV 3** (i.e. 3.4.5): On the
        top (see Figure [1](#fig:main_page){reference-type="ref"
        reference="fig:main_page"}), there is a link called 'RELEASES',
        or just click on
        <https://sourceforge.net/projects/opencvlibrary/files/3.4.5/opencv-3.4.5-vc14_vc15.exe/download>.

        ![[\[fig:main_page\]]{#fig:main_page
        label="fig:main_page"}OpenCV's
        website.](opencv_mainpage.png){#fig:main_page
        width="\\textwidth"}

    3.  **Run the file** and extract the library in `C:` drive.

    4.  **Job done:** There is a new directory called `opencv` in the
        `C:` drive. -->

# Task 1:

1. Create the following empty files in the root directory of your project:

- `displayImage.cxx`;
- `rgb2grey.cxx`;
- `logScale.cxx`;
- `meanFilter.cxx`;
- `medianFilter.cxx`;
- `gaussianFilter.cxx`; and
- `cartoonise.cxx`

2. If you are using MS Windows, double-check the file extension;

- Open the `File Explorer`; if you do not have an icon for this in the task bar; click `Start`, click `Windows System`, and then `File Explorer`.
- Click the `View` tab in `File Explorer`.
- Click the box next to `File name extensions` to see file extensions.

Last semester some people had problems as they did not see that the file extension was actually `.txt` rather than `.cxx`.

3. Make sure every file compilable. For example we could add:

```cpp
int main(int argc, char** argv)
{
    return 0;
}
```

# Tast 2: Prepare `CMakeLists.txt`

As some of you will use

-   MS Windows on the University's computers,
-   MS Windows on their own computer(s),
-   Mac OS, and
-   Linux

it is important to keep in mind portability and we saw that toolchains
can help us achieve it. [CMake](https://www.cmake.org/) is an example of toolchain that is user friendly. It is actually the industry standard. I assume it is still installed on your PC.

1. Create a new file in the same directory as your `.cxx` files. Name the file `CMakeLists.txt`.


2. Set the minimum CMake version to at least 3.1. It is needed to enable  the C++ 11 standard.
```cmake
CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(ICP3038--Lab10--Intro2OpenCV)
```

3. C++ 11 is a requirement for OpenCV 4, enable it with:

```cmake
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
```

4. For MS Windows users, add where OpenCV might be installed (look in D: first, then in C:). If you installed OpenCV somewhere else, adjust the path accordingly:

```cmake
IF (WIN32)
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:\\opencv\\build")
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\opencv\\build")
ENDIF (WIN32)
```

5. Find OpenCV
```cmake
FIND_PACKAGE(OpenCV REQUIRED)
```

6. The executable programs
```cmake
ADD_EXECUTABLE (displayImage   displayImage.cxx)
ADD_EXECUTABLE (rgb2grey       rgb2grey.cxx)
ADD_EXECUTABLE (logScale       logScale.cxx)
ADD_EXECUTABLE (meanFilter     meanFilter.cxx)
ADD_EXECUTABLE (medianFilter   medianFilter.cxx)
ADD_EXECUTABLE (gaussianFilter gaussianFilter.cxx)
ADD_EXECUTABLE (cartoonise     cartoonise.cxx)
```

7. Add OpenCV's header path for each program
```cmake
INCLUDE_DIRECTORIES (${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(displayImage PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(rgb2grey PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(logScale PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(meanFilter PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(medianFilter PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(gaussianFilter PUBLIC ${OpenCV_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(cartoonise PUBLIC ${OpenCV_INCLUDE_DIRS})
```

8. Add OpenCV libraries to each executable programs
```cmake
TARGET_LINK_LIBRARIES (displayImage   ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (rgb2grey       ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (logScale       ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (meanFilter     ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (medianFilter   ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (gaussianFilter ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES (cartoonise     ${OpenCV_LIBS})
```

9. If windows is used, copy the DLLs into the project directory
```cmake
SET (CV_VERSION_STRING ${OpenCV_VERSION_MAJOR}${OpenCV_VERSION_MINOR}${OpenCV_VERSION_PATCH})
IF (WIN32)
    IF ( ${OpenCV_VERSION_MAJOR} EQUAL 4)
        IF (EXISTS "${OpenCV_DIR}/x64/vc15/bin/opencv_videoio_ffmpeg${CV_VERSION_STRING}_64.dll")
            FILE (COPY        "${OpenCV_DIR}/x64/vc15/bin/opencv_videoio_ffmpeg${CV_VERSION_STRING}_64.dll"
                  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
        ELSE ()
      MESSAGE (WARNING "opencv_videoio_ffmpeg${CV_VERSION_STRING}_64.dll is not in ${OpenCV_DIR}/x64/vc15/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
        ENDIF ()
  ELSE ()
        IF (EXISTS "${OpenCV_DIR}/x64/vc15/bin/opencv_ffmpeg${CV_VERSION_STRING}_64.dll")
            FILE (COPY        "${OpenCV_DIR}/x64/vc15/bin/opencv_ffmpeg${CV_VERSION_STRING}_64.dll"
                  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
        ELSE ()
      MESSAGE (WARNING "opencv_ffmpeg${CV_VERSION_STRING}_64.dll is not in ${OpenCV_DIR}/x64/vc15/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
        ENDIF ()
  ENDIF ()

    IF (EXISTS "${OpenCV_DIR}/x64/vc15/bin/opencv_world${CV_VERSION_STRING}.dll")
        FILE (COPY        "${OpenCV_DIR}/x64/vc15/bin/opencv_world${CV_VERSION_STRING}.dll"
              DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ELSE ()
      MESSAGE (WARNING "opencv_world${CV_VERSION_STRING}.dll is not in ${OpenCV_DIR}/x64/vc15/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
    ENDIF ()

    IF (EXISTS "${OpenCV_DIR}/x64/vc15/bin/opencv_world${CV_VERSION_STRING}d.dll")
        FILE (COPY        "${OpenCV_DIR}/x64/vc15/bin/opencv_world${CV_VERSION_STRING}d.dll"
              DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ELSE ()
      MESSAGE (WARNING "opencv_world${CV_VERSION_STRING}d.dll is not in ${OpenCV_DIR}/x64/vc15/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
    ENDIF ()
ENDIF (WIN32)    
```

# Task 3: Configure and generate the project

Configuring the project using CMake is relatively straightforward. **MAKE SURE YOU USE A GENERATOR THAT SUPPORT 64 BITS.** Every year some people use Win32 instead of Win64. OpenCV is now shipped with the libs compiled in 64 bits only. Win32 won't work.

Do not compile (see "Where to build the binaries:") in the same directory a your source code.

![Project configuration using CMake.](doc/cmake.png)

# Task 4: Opening and Displaying an Image

We will write a program that opens and displays an image file.

- NAME
  - `displayImage` - open and display an image file
- SYNOPSIS
  - `displayImage infile`
- DESCRIPTION
  - `displayImage` is a program that loads an image file, opens a window, and display the image into that window. OpenCV is used for that purpose.
- OPTION(s)
  - `infile`: path to an image file.

## Add a preamble to `displayImage.cxx`

Using C++ comments, add a preamble at the top of your file.
It must describe the program:

1. the author of the program (you),
2. the date,
3. the purpose of the file (inc. the command line options),
4. the todo-list if anything is missing.


## Header inclusion

OpenCV uses exceptions. To catch them, we need `<exception>`. To display
text in the console `<iostream>` is required. The main OpenCV header is
`<opencv2/opencv.hpp>`.

```cpp
#include <exception> // Header for catching exceptions
#include <iostream>  // Header to display text in the console
#include <opencv2/opencv.hpp> // Main OpenCV header
```

## Main structure

As stated previously, OpenCV uses exceptions. We can (or should) catch
them to handle errors. The structure of the main is (almost always):

```cpp
//-----------------------------
int main(int argc, char** argv)
//-----------------------------
{
    try
    {
        // Check the command line
        if (argc != 2)
        {
            // Create an error message
            std::string error_message;
            error_message  = "usage: ";
            error_message += argv[0];
            error_message += " <input_image>";

            // Throw an error
            throw error_message;
        }

        // Write your own code here
        //....
        //....
        //....
    }
    // An error occured
    catch (const std::exception& error)
    {
        // Display an error message in the console
        cerr << error.what() << endl;
    }
    catch (const std::string& error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }
    catch (const char* error)
    {
        // Display an error message in the console
        cerr << error << endl;
    }
    catch (...)
    {
        // Display an error message in the console
        cerr << "Unnown error caught" << endl;
    }

#ifdef WIN32
#ifdef _DEBUG
    system("pause");
#endif
#endif

    return 0;
```

## Arguments of the Command Line

The first program only takes one parameter. It corresponds to the path
of an image file. To make sure the number of arguments is correct, you
can use:

```cpp
// Check the command line
if (argc != 2)
{
    // Create an error message
    std::string error_message;
    error_message  = "usage: ";
    error_message += argv[0];
    error_message += " <input_image>";

    // Throw an error
    throw error_message;
}
```

If there was no error, you can use to get the file name:

```cpp
std::string input_filename(argv[1]);
```

## Reading the File

An image is stored in an instance of the class `Mat`. Note that OpenCV's
namespace is `cv::`. To declare the variable that will hold our image,
type:

```cpp
// Create an image instance
cv::Mat image;
```

In OpenCV 4, the image is loaded using:

```cpp
// Open and read the image
image = cv::imread( input_filename, cv::IMREAD_COLOR );
```

It is a good practice to check if any error occurred, e.g. to avoid
unspecified behaviours and crashed. If the image is not loaded, its
`data` field is empty. If it is the case we can throw an error as
follows:

```cpp
// The image has not been loaded
if (!image.data)
{
    // Create an error message
    std::string error_message;
    error_message  = "Could not open or find the image \"";
    error_message += input_filename;
    error_message += "\".";

    // Throw an error
    throw error_message;
}
```

## Displaying the Image

There are four steps to create a window and display and image:

1.  Create a string to contain the window title (it is used to identify
    the window);
2.  Create the window;
3.  Show the image in the window;
4.  Wait for a user input to leave the window.

It can be done as follows:

```cpp
        // Create a string to contain the window title
        string window_title;
        window_title  = "Display \"";
        window_title += input_filename;
        window_title += "\"";

        // Create the window
        cv::namedWindow(window_title, cv::WINDOW_AUTOSIZE);

        // Show the image in the window
        cv::imshow(window_title, image);

        // Wait for a user input to leave the window
        cv::waitKey(0);
```

The program is now complete. You can compile it and run it with
different image files to test it.
Figure [3](#fig:displayImage){reference-type="ref"
reference="fig:displayImage"} shows a screenshot of the program.

![Screenshot of `displayImage`.](doc/displayImage.png)


# Converts a RGB Image in a Greyscale Image

A lot of algorithms work on greyscale images. We are going to write a program that does just that.
Copy the main function of `displayImage.cxx` into `rgb2grey.cxx`.

- NAME
  - `rgb2grey` - convert an RGB image file into a greyscale image
- SYNOPSIS
  - `rgb2grey [-display] infile outfile`
- DESCRIPTION
  - `rgb2grey` is a program that loads an image file, converts it into greyscale, and optionaly displays the results into a window. OpenCV is used for that purpose.
- OPTION(s)
  - `infile`: path to an input image file.
  - `outfile`: path to an output image file.
  - `-display`: display the greyscale image in a window. This argument is optional.

## Arguments of the Command Line

There are either 2 or 3 arguments. `infile` and `outfile` are required. `-display` is optional.
Modify the code accordingly. Examples of suitable usage:

```bash
$ rgb2grey input.png output.png
$ rgb2grey -display input.png output.png
$ rgb2grey input.png output.png -display
$ rgb2grey input.png -display output.png  
```

The following is not suitable:
```cpp
$ rgb2grey input.png -display
```
If it occurs, generate an exception with a meaningful error message.

**Hints:** You'll need an extra two local variables. For the output file:
```cpp
std::string output_filename;
```
For the display option:
```cpp
bool display_image = false;
```

## Converting from RGB to Greyscale

To convert the original image in greyscale,
simply type:

```cpp
cv::Mat grey_image;
cv::cvtColor(image, grey_image, cv::COLOR_RGB2GRAY);
```

In OpenCV in general, the first argument is the input image; the second
argument is the output image; other arguments are the parameters of the
function.

## Saving an Image into a File

The function to save an image is `cv::imwrite(file_name, image)`. It
returns true if the file has been successfully written; false otherwise.
We can use the return value to handle possible errors:

```cxx
// Write the image
if (!cv::imwrite(output_filename, grey_image))
{
    // The image has not been written

    // Create an error message
    std::string error_message;
    error_message  = "Could not write the image \"";
    error_message += output_filename;
    error_message += "\".";

    // Throw an error
    throw error_message;
}
```

## Display the image

If the option `-display` was used in the command line, display `grey_image`.

Calling `rgb2grey lena_color_512.tif lena_grey.png` should produce the output
presented below:

![Input `rgb2grey`.](lena_color_512.png)

<!--![Output `rgb2grey`.](lena_grey.png)

Mean Filter
===========

Let us consider the mean filter. Copy parts of the main function of
`rgb2grey.cxx` into `meanFilter.cxx`. The new program will take 3
inputs:

1.  The input image;

2.  The output image; and

3.  The convolution kernel radius.

To convert a C string into an integer, use the `atoi` function from the
`<cstdlib>` header. It will be needed to get the kernel radius from the
command line argument. To set the kernel size, you need to use an
instance of the `cv::Size` class. You also have to specify its size. You
can use:

``` {.c++ language="c++"}
// Filter size
cv::Size filter_size(kernel_width, kernel_height);
```

or

``` {.c++ language="c++"}
// Filter size
cv::Size filter_size;
filter_size.width = kernel_width;
filter_size.height = kernel_height;
```

Note that

-   If the radius is 0, then the kernel size is $1\times1$

-   If the radius is 1, then the kernel size is $3\times3$

-   If the radius is 2, then the kernel size is $5\times5$

-   \...

-   If the radius is 7, then the kernel size is $15\times15$

-   etc.

Now you are ready to filter the input image. Use either `cv::blur` or
`cv::boxFilter`. They are the same. The first argument is the input
image; the second is the output image; and the third one is the kernel
size. Display and save the output image. Try different kernel sizes to
see the differences (see Figure [9](#fig:boxFilter){reference-type="ref"
reference="fig:boxFilter"}).

  --------------------------------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------
   ![[\[fig:boxFilter\]]{#fig:boxFilter label="fig:boxFilter"}Outputs of **meanFilter**.](lena_R1.png){#fig:boxFilter width="35%"}   ![[\[fig:boxFilter\]]{#fig:boxFilter label="fig:boxFilter"}Outputs of **meanFilter**.](lena_R2.png){#fig:boxFilter width="35%"}
                                                          \(a\) Radius = 1.                                                                                                                 \(b\) Radius = 2.
   ![[\[fig:boxFilter\]]{#fig:boxFilter label="fig:boxFilter"}Outputs of **meanFilter**.](lena_R5.png){#fig:boxFilter width="35%"}   ![[\[fig:boxFilter\]]{#fig:boxFilter label="fig:boxFilter"}Outputs of **meanFilter**.](lena_R50.png){#fig:boxFilter width="35%"}
                                                          \(c\) Radius = 5.                                                                                                                 \(d\) Radius = 50.
  --------------------------------------------------------------------------------------------------------------------------------- ----------------------------------------------------------------------------------------------------------------------------------

Display an Image in the Log Scale
=================================

The main function of `rgb2grey.cxx` into `logScale.cxx` as it is
important to use a greyscale image in this new program.
Fig. [\[fig:log\]](#fig:log){reference-type="ref" reference="fig:log"}
shows the shape of the $\log$ function.

(1500,900)(0,0) (131.0,131.0)

------------------------------------------------------------------------

(111,131)(0,0)\[r\]-3 (1419.0,131.0)

------------------------------------------------------------------------

(131.0,235.0)

------------------------------------------------------------------------

(111,235)(0,0)\[r\]-2 (1419.0,235.0)

------------------------------------------------------------------------

(131.0,339.0)

------------------------------------------------------------------------

(111,339)(0,0)\[r\]-1 (1419.0,339.0)

------------------------------------------------------------------------

(131.0,443.0)

------------------------------------------------------------------------

(111,443)(0,0)\[r\] 0 (1419.0,443.0)

------------------------------------------------------------------------

(131.0,547.0)

------------------------------------------------------------------------

(111,547)(0,0)\[r\] 1 (1419.0,547.0)

------------------------------------------------------------------------

(131.0,651.0)

------------------------------------------------------------------------

(111,651)(0,0)\[r\] 2 (1419.0,651.0)

------------------------------------------------------------------------

(131.0,755.0)

------------------------------------------------------------------------

(111,755)(0,0)\[r\] 3 (1419.0,755.0)

------------------------------------------------------------------------

(131.0,859.0)

------------------------------------------------------------------------

(111,859)(0,0)\[r\] 4 (1419.0,859.0)

------------------------------------------------------------------------

(262.0,131.0)

------------------------------------------------------------------------

(262,90)(0,0)-40 (262.0,839.0)

------------------------------------------------------------------------

(523.0,131.0)

------------------------------------------------------------------------

(523,90)(0,0)-20 (523.0,839.0)

------------------------------------------------------------------------

(785.0,131.0)

------------------------------------------------------------------------

(785,90)(0,0) 0 (785.0,839.0)

------------------------------------------------------------------------

(1047.0,131.0)

------------------------------------------------------------------------

(1047,90)(0,0) 20 (1047.0,839.0)

------------------------------------------------------------------------

(1308.0,131.0)

------------------------------------------------------------------------

(1308,90)(0,0) 40 (1308.0,839.0)

------------------------------------------------------------------------

(131.0,131.0)

------------------------------------------------------------------------

(131.0,131.0)

------------------------------------------------------------------------

(1439.0,131.0)

------------------------------------------------------------------------

(131.0,859.0)

------------------------------------------------------------------------

(30,495)(0,0)$y = \log{x}$ (785,29)(0,0)$x$ axis (786,204)
(786.61,204.00)(0.447,25.244)3

------------------------------------------------------------------------

(785.17,204.00)(3.000,82.244)2

------------------------------------------------------------------------

(789.61,318.00)(0.447,11.625)3

------------------------------------------------------------------------

(788.17,318.00)(3.000,38.125)2

------------------------------------------------------------------------

(792.17,371)

------------------------------------------------------------------------

(791.17,371.00)(2.000,20.264)2

------------------------------------------------------------------------

(794.61,406.00)(0.447,5.597)3

------------------------------------------------------------------------

(793.17,406.00)(3.000,18.597)2

------------------------------------------------------------------------

(797.17,432)

------------------------------------------------------------------------

(796.17,432.00)(2.000,12.075)2

------------------------------------------------------------------------

(799.61,453.00)(0.447,3.588)3

------------------------------------------------------------------------

(798.17,453.00)(3.000,12.088)2

------------------------------------------------------------------------

(802.61,470.00)(0.447,3.141)3

------------------------------------------------------------------------

(801.17,470.00)(3.000,10.641)2

------------------------------------------------------------------------

(805.17,485)

------------------------------------------------------------------------

(804.17,485.00)(2.000,7.396)2

------------------------------------------------------------------------

(807.61,498.00)(0.447,2.472)3

------------------------------------------------------------------------

(806.17,498.00)(3.000,8.472)2

------------------------------------------------------------------------

(810.61,510.00)(0.447,2.025)3

------------------------------------------------------------------------

(809.17,510.00)(3.000,7.025)2

------------------------------------------------------------------------

(813.17,520)

------------------------------------------------------------------------

(812.17,520.00)(2.000,5.641)2

------------------------------------------------------------------------

(815.61,530.00)(0.447,1.802)3

------------------------------------------------------------------------

(814.17,530.00)(3.000,6.302)2

------------------------------------------------------------------------

(818.17,539)

------------------------------------------------------------------------

(817.17,539.00)(2.000,4.472)2

------------------------------------------------------------------------

(820.61,547.00)(0.447,1.355)3

------------------------------------------------------------------------

(819.17,547.00)(3.000,4.855)2

------------------------------------------------------------------------

(823.61,554.00)(0.447,1.355)3

------------------------------------------------------------------------

(822.17,554.00)(3.000,4.855)2

------------------------------------------------------------------------

(826.17,561)

------------------------------------------------------------------------

(825.17,561.00)(2.000,3.302)2

------------------------------------------------------------------------

(828.61,567.00)(0.447,1.132)3

------------------------------------------------------------------------

(827.17,567.00)(3.000,4.132)2

------------------------------------------------------------------------

(831.17,573)

------------------------------------------------------------------------

(830.17,573.00)(2.000,3.302)2

------------------------------------------------------------------------

(833.61,579.00)(0.447,1.132)3

------------------------------------------------------------------------

(832.17,579.00)(3.000,4.132)2

------------------------------------------------------------------------

(836.61,585.00)(0.447,0.909)3

------------------------------------------------------------------------

(835.17,585.00)(3.000,3.409)2

------------------------------------------------------------------------

(839.17,590)

------------------------------------------------------------------------

(838.17,590.00)(2.000,2.717)2

------------------------------------------------------------------------

(841.61,595.00)(0.447,0.909)3

------------------------------------------------------------------------

(840.17,595.00)(3.000,3.409)2

------------------------------------------------------------------------

(844.61,600.00)(0.447,0.685)3

------------------------------------------------------------------------

(843.17,600.00)(3.000,2.685)2

------------------------------------------------------------------------

(847.17,604)

------------------------------------------------------------------------

(846.17,604.00)(2.000,2.132)2

------------------------------------------------------------------------

(849.61,608.00)(0.447,0.909)3

------------------------------------------------------------------------

(848.17,608.00)(3.000,3.409)2

------------------------------------------------------------------------

(852.17,613)

------------------------------------------------------------------------

(851.17,613.00)(2.000,2.132)2

------------------------------------------------------------------------

(854.61,617.00)(0.447,0.685)3

------------------------------------------------------------------------

(853.17,617.00)(3.000,2.685)2

------------------------------------------------------------------------

(857.00,621.61)(0.462,0.447)3

------------------------------------------------------------------------

(857.00,620.17)(1.962,3.000)2

------------------------------------------------------------------------

(860.17,624)

------------------------------------------------------------------------

(859.17,624.00)(2.000,2.132)2

------------------------------------------------------------------------

(862.00,628.61)(0.462,0.447)3

------------------------------------------------------------------------

(862.00,627.17)(1.962,3.000)2

------------------------------------------------------------------------

(865.61,631.00)(0.447,0.685)3

------------------------------------------------------------------------

(864.17,631.00)(3.000,2.685)2

------------------------------------------------------------------------

(868.17,635)

------------------------------------------------------------------------

(867.17,635.00)(2.000,1.547)2

------------------------------------------------------------------------

(870.00,638.61)(0.462,0.447)3

------------------------------------------------------------------------

(870.00,637.17)(1.962,3.000)2

------------------------------------------------------------------------

(873.17,641)

------------------------------------------------------------------------

(872.17,641.00)(2.000,1.547)2

------------------------------------------------------------------------

(875.00,644.61)(0.462,0.447)3

------------------------------------------------------------------------

(875.00,643.17)(1.962,3.000)2

------------------------------------------------------------------------

(878.00,647.61)(0.462,0.447)3

------------------------------------------------------------------------

(878.00,646.17)(1.962,3.000)2

------------------------------------------------------------------------

(881.17,650)

------------------------------------------------------------------------

(880.17,650.00)(2.000,1.547)2

------------------------------------------------------------------------

(883,653.17)

------------------------------------------------------------------------

(883.00,652.17)(1.547,2.000)2

------------------------------------------------------------------------

(886.00,655.61)(0.462,0.447)3

------------------------------------------------------------------------

(886.00,654.17)(1.962,3.000)2

------------------------------------------------------------------------

(889.17,658)

------------------------------------------------------------------------

(888.17,658.00)(2.000,1.547)2

------------------------------------------------------------------------

(891,661.17)

------------------------------------------------------------------------

(891.00,660.17)(1.547,2.000)2

------------------------------------------------------------------------

(894.17,663)

------------------------------------------------------------------------

(893.17,663.00)(2.000,1.547)2

------------------------------------------------------------------------

(896,666.17)

------------------------------------------------------------------------

(896.00,665.17)(1.547,2.000)2

------------------------------------------------------------------------

(899.00,668.61)(0.462,0.447)3

------------------------------------------------------------------------

(899.00,667.17)(1.962,3.000)2

------------------------------------------------------------------------

(902,671.17)

------------------------------------------------------------------------

(902.00,670.17)(1.000,2.000)2

------------------------------------------------------------------------

(904,673.17)

------------------------------------------------------------------------

(904.00,672.17)(1.547,2.000)2

------------------------------------------------------------------------

(907,675.17)

------------------------------------------------------------------------

(907.00,674.17)(1.547,2.000)2

------------------------------------------------------------------------

(910.17,677)

------------------------------------------------------------------------

(909.17,677.00)(2.000,1.547)2

------------------------------------------------------------------------

(912,680.17)

------------------------------------------------------------------------

(912.00,679.17)(1.547,2.000)2

------------------------------------------------------------------------

(915,682.17)

------------------------------------------------------------------------

(915.00,681.17)(1.000,2.000)2

------------------------------------------------------------------------

(917,684.17)

------------------------------------------------------------------------

(917.00,683.17)(1.547,2.000)2

------------------------------------------------------------------------

(920,686.17)

------------------------------------------------------------------------

(920.00,685.17)(1.547,2.000)2

------------------------------------------------------------------------

(923,688.17)

------------------------------------------------------------------------

(923.00,687.17)(1.000,2.000)2

------------------------------------------------------------------------

(925,690.17)

------------------------------------------------------------------------

(925.00,689.17)(1.547,2.000)2

------------------------------------------------------------------------

(928,692.17)

------------------------------------------------------------------------

(928.00,691.17)(1.000,2.000)2

------------------------------------------------------------------------

(930,693.67)

------------------------------------------------------------------------

(930.00,693.17)(1.500,1.000)2

------------------------------------------------------------------------

(933,695.17)

------------------------------------------------------------------------

(933.00,694.17)(1.547,2.000)2

------------------------------------------------------------------------

(936,697.17)

------------------------------------------------------------------------

(936.00,696.17)(1.000,2.000)2

------------------------------------------------------------------------

(938,699.17)

------------------------------------------------------------------------

(938.00,698.17)(1.547,2.000)2

------------------------------------------------------------------------

(941,701.17)

------------------------------------------------------------------------

(941.00,700.17)(1.547,2.000)2

------------------------------------------------------------------------

(944,702.67)

------------------------------------------------------------------------

(944.00,702.17)(1.000,1.000)2

------------------------------------------------------------------------

(946,704.17)

------------------------------------------------------------------------

(946.00,703.17)(1.547,2.000)2

------------------------------------------------------------------------

(949,706.17)

------------------------------------------------------------------------

(949.00,705.17)(1.000,2.000)2

------------------------------------------------------------------------

(951,707.67)

------------------------------------------------------------------------

(951.00,707.17)(1.500,1.000)2

------------------------------------------------------------------------

(954,709.17)

------------------------------------------------------------------------

(954.00,708.17)(1.547,2.000)2

------------------------------------------------------------------------

(957,710.67)

------------------------------------------------------------------------

(957.00,710.17)(1.000,1.000)2

------------------------------------------------------------------------

(959,712.17)

------------------------------------------------------------------------

(959.00,711.17)(1.547,2.000)2

------------------------------------------------------------------------

(962,713.67)

------------------------------------------------------------------------

(962.00,713.17)(1.500,1.000)2

------------------------------------------------------------------------

(965,715.17)

------------------------------------------------------------------------

(965.00,714.17)(1.000,2.000)2

------------------------------------------------------------------------

(967,716.67)

------------------------------------------------------------------------

(967.00,716.17)(1.500,1.000)2

------------------------------------------------------------------------

(970,718.17)

------------------------------------------------------------------------

(970.00,717.17)(1.000,2.000)2

------------------------------------------------------------------------

(972,719.67)

------------------------------------------------------------------------

(972.00,719.17)(1.500,1.000)2

------------------------------------------------------------------------

(975,721.17)

------------------------------------------------------------------------

(975.00,720.17)(1.547,2.000)2

------------------------------------------------------------------------

(978,722.67)

------------------------------------------------------------------------

(978.00,722.17)(1.000,1.000)2

------------------------------------------------------------------------

(980,724.17)

------------------------------------------------------------------------

(980.00,723.17)(1.547,2.000)2

------------------------------------------------------------------------

(983,725.67)

------------------------------------------------------------------------

(983.00,725.17)(1.500,1.000)2

------------------------------------------------------------------------

(986,726.67)

------------------------------------------------------------------------

(986.00,726.17)(1.000,1.000)2

------------------------------------------------------------------------

(988,728.17)

------------------------------------------------------------------------

(988.00,727.17)(1.547,2.000)2

------------------------------------------------------------------------

(991,729.67)

------------------------------------------------------------------------

(991.00,729.17)(1.000,1.000)2

------------------------------------------------------------------------

(993,730.67)

------------------------------------------------------------------------

(993.00,730.17)(1.500,1.000)2

------------------------------------------------------------------------

(996,731.67)

------------------------------------------------------------------------

(996.00,731.17)(1.500,1.000)2

------------------------------------------------------------------------

(999,733.17)

------------------------------------------------------------------------

(999.00,732.17)(1.000,2.000)2

------------------------------------------------------------------------

(1001,734.67)

------------------------------------------------------------------------

(1001.00,734.17)(1.500,1.000)2

------------------------------------------------------------------------

(1004,735.67)

------------------------------------------------------------------------

(1004.00,735.17)(1.000,1.000)2

------------------------------------------------------------------------

(1006,736.67)

------------------------------------------------------------------------

(1006.00,736.17)(1.500,1.000)2

------------------------------------------------------------------------

(1009,738.17)

------------------------------------------------------------------------

(1009.00,737.17)(1.547,2.000)2

------------------------------------------------------------------------

(1012,739.67)

------------------------------------------------------------------------

(1012.00,739.17)(1.000,1.000)2

------------------------------------------------------------------------

(1014,740.67)

------------------------------------------------------------------------

(1014.00,740.17)(1.500,1.000)2

------------------------------------------------------------------------

(1017,741.67)

------------------------------------------------------------------------

(1017.00,741.17)(1.500,1.000)2

------------------------------------------------------------------------

(1020,742.67)

------------------------------------------------------------------------

(1020.00,742.17)(1.000,1.000)2

------------------------------------------------------------------------

(1022,744.17)

------------------------------------------------------------------------

(1022.00,743.17)(1.547,2.000)2

------------------------------------------------------------------------

(1025,745.67)

------------------------------------------------------------------------

(1025.00,745.17)(1.000,1.000)2

------------------------------------------------------------------------

(1027,746.67)

------------------------------------------------------------------------

(1027.00,746.17)(1.500,1.000)2

------------------------------------------------------------------------

(1030,747.67)

------------------------------------------------------------------------

(1030.00,747.17)(1.500,1.000)2

------------------------------------------------------------------------

(1033,748.67)

------------------------------------------------------------------------

(1033.00,748.17)(1.000,1.000)2

------------------------------------------------------------------------

(1035,749.67)

------------------------------------------------------------------------

(1035.00,749.17)(1.500,1.000)2

------------------------------------------------------------------------

(1038,750.67)

------------------------------------------------------------------------

(1038.00,750.17)(1.500,1.000)2

------------------------------------------------------------------------

(1041,751.67)

------------------------------------------------------------------------

(1041.00,751.17)(1.000,1.000)2

------------------------------------------------------------------------

(1043,752.67)

------------------------------------------------------------------------

(1043.00,752.17)(1.500,1.000)2

------------------------------------------------------------------------

(1046,753.67)

------------------------------------------------------------------------

(1046.00,753.17)(1.000,1.000)2

------------------------------------------------------------------------

(1048,754.67)

------------------------------------------------------------------------

(1048.00,754.17)(1.500,1.000)2

------------------------------------------------------------------------

(1051,755.67)

------------------------------------------------------------------------

(1051.00,755.17)(1.500,1.000)2

------------------------------------------------------------------------

(1054,756.67)

------------------------------------------------------------------------

(1054.00,756.17)(1.000,1.000)2

------------------------------------------------------------------------

(1056,757.67)

------------------------------------------------------------------------

(1056.00,757.17)(1.500,1.000)2

------------------------------------------------------------------------

(1059,758.67)

------------------------------------------------------------------------

(1059.00,758.17)(1.500,1.000)2

------------------------------------------------------------------------

(1062,759.67)

------------------------------------------------------------------------

(1062.00,759.17)(1.000,1.000)2

------------------------------------------------------------------------

(1064,760.67)

------------------------------------------------------------------------

(1064.00,760.17)(1.500,1.000)2

------------------------------------------------------------------------

(1067,761.67)

------------------------------------------------------------------------

(1067.00,761.17)(1.000,1.000)2

------------------------------------------------------------------------

(1069,762.67)

------------------------------------------------------------------------

(1069.00,762.17)(1.500,1.000)2

------------------------------------------------------------------------

(1072,763.67)

------------------------------------------------------------------------

(1072.00,763.17)(1.500,1.000)2

------------------------------------------------------------------------

(1075,764.67)

------------------------------------------------------------------------

(1075.00,764.17)(1.000,1.000)2

------------------------------------------------------------------------

(1077,765.67)

------------------------------------------------------------------------

(1077.00,765.17)(1.500,1.000)2

------------------------------------------------------------------------

(1080,766.67)

------------------------------------------------------------------------

(1080.00,766.17)(1.500,1.000)2

------------------------------------------------------------------------

(1083,767.67)

------------------------------------------------------------------------

(1083.00,767.17)(1.000,1.000)2

------------------------------------------------------------------------

(1085,768.67)

------------------------------------------------------------------------

(1085.00,768.17)(1.500,1.000)2

------------------------------------------------------------------------

(1088,769.67)

------------------------------------------------------------------------

(1088.00,769.17)(1.000,1.000)2

------------------------------------------------------------------------

(1090,770.67)

------------------------------------------------------------------------

(1090.00,770.17)(1.500,1.000)2

------------------------------------------------------------------------

(1096,771.67)

------------------------------------------------------------------------

(1096.00,771.17)(1.000,1.000)2

------------------------------------------------------------------------

(1098,772.67)

------------------------------------------------------------------------

(1098.00,772.17)(1.500,1.000)2

------------------------------------------------------------------------

(1101,773.67)

------------------------------------------------------------------------

(1101.00,773.17)(1.000,1.000)2

------------------------------------------------------------------------

(1103,774.67)

------------------------------------------------------------------------

(1103.00,774.17)(1.500,1.000)2

------------------------------------------------------------------------

(1106,775.67)

------------------------------------------------------------------------

(1106.00,775.17)(1.500,1.000)2

------------------------------------------------------------------------

(1109,776.67)

------------------------------------------------------------------------

(1109.00,776.17)(1.000,1.000)2

------------------------------------------------------------------------

(1093.0,772.0)

------------------------------------------------------------------------

(1114,777.67)

------------------------------------------------------------------------

(1114.00,777.17)(1.500,1.000)2

------------------------------------------------------------------------

(1117,778.67)

------------------------------------------------------------------------

(1117.00,778.17)(1.000,1.000)2

------------------------------------------------------------------------

(1119,779.67)

------------------------------------------------------------------------

(1119.00,779.17)(1.500,1.000)2

------------------------------------------------------------------------

(1122,780.67)

------------------------------------------------------------------------

(1122.00,780.17)(1.000,1.000)2

------------------------------------------------------------------------

(1111.0,778.0)

------------------------------------------------------------------------

(1127,781.67)

------------------------------------------------------------------------

(1127.00,781.17)(1.500,1.000)2

------------------------------------------------------------------------

(1130,782.67)

------------------------------------------------------------------------

(1130.00,782.17)(1.000,1.000)2

------------------------------------------------------------------------

(1132,783.67)

------------------------------------------------------------------------

(1132.00,783.17)(1.500,1.000)2

------------------------------------------------------------------------

(1135,784.67)

------------------------------------------------------------------------

(1135.00,784.17)(1.500,1.000)2

------------------------------------------------------------------------

(1124.0,782.0)

------------------------------------------------------------------------

(1140,785.67)

------------------------------------------------------------------------

(1140.00,785.17)(1.500,1.000)2

------------------------------------------------------------------------

(1143,786.67)

------------------------------------------------------------------------

(1143.00,786.17)(1.000,1.000)2

------------------------------------------------------------------------

(1145,787.67)

------------------------------------------------------------------------

(1145.00,787.17)(1.500,1.000)2

------------------------------------------------------------------------

(1138.0,786.0)

------------------------------------------------------------------------

(1151,788.67)

------------------------------------------------------------------------

(1151.00,788.17)(1.000,1.000)2

------------------------------------------------------------------------

(1153,789.67)

------------------------------------------------------------------------

(1153.00,789.17)(1.500,1.000)2

------------------------------------------------------------------------

(1156,790.67)

------------------------------------------------------------------------

(1156.00,790.17)(1.500,1.000)2

------------------------------------------------------------------------

(1148.0,789.0)

------------------------------------------------------------------------

(1161,791.67)

------------------------------------------------------------------------

(1161.00,791.17)(1.500,1.000)2

------------------------------------------------------------------------

(1164,792.67)

------------------------------------------------------------------------

(1164.00,792.17)(1.000,1.000)2

------------------------------------------------------------------------

(1159.0,792.0)

------------------------------------------------------------------------

(1169,793.67)

------------------------------------------------------------------------

(1169.00,793.17)(1.500,1.000)2

------------------------------------------------------------------------

(1172,794.67)

------------------------------------------------------------------------

(1172.00,794.17)(1.000,1.000)2

------------------------------------------------------------------------

(1174,795.67)

------------------------------------------------------------------------

(1174.00,795.17)(1.500,1.000)2

------------------------------------------------------------------------

(1166.0,794.0)

------------------------------------------------------------------------

(1179,796.67)

------------------------------------------------------------------------

(1179.00,796.17)(1.500,1.000)2

------------------------------------------------------------------------

(1182,797.67)

------------------------------------------------------------------------

(1182.00,797.17)(1.500,1.000)2

------------------------------------------------------------------------

(1177.0,797.0)

------------------------------------------------------------------------

(1187,798.67)

------------------------------------------------------------------------

(1187.00,798.17)(1.500,1.000)2

------------------------------------------------------------------------

(1190,799.67)

------------------------------------------------------------------------

(1190.00,799.17)(1.500,1.000)2

------------------------------------------------------------------------

(1185.0,799.0)

------------------------------------------------------------------------

(1195,800.67)

------------------------------------------------------------------------

(1195.00,800.17)(1.500,1.000)2

------------------------------------------------------------------------

(1198,801.67)

------------------------------------------------------------------------

(1198.00,801.17)(1.000,1.000)2

------------------------------------------------------------------------

(1193.0,801.0)

------------------------------------------------------------------------

(1203,802.67)

------------------------------------------------------------------------

(1203.00,802.17)(1.500,1.000)2

------------------------------------------------------------------------

(1206,803.67)

------------------------------------------------------------------------

(1206.00,803.17)(1.000,1.000)2

------------------------------------------------------------------------

(1200.0,803.0)

------------------------------------------------------------------------

(1211,804.67)

------------------------------------------------------------------------

(1211.00,804.17)(1.500,1.000)2

------------------------------------------------------------------------

(1214,805.67)

------------------------------------------------------------------------

(1214.00,805.17)(1.000,1.000)2

------------------------------------------------------------------------

(1208.0,805.0)

------------------------------------------------------------------------

(1219,806.67)

------------------------------------------------------------------------

(1219.00,806.17)(1.000,1.000)2

------------------------------------------------------------------------

(1216.0,807.0)

------------------------------------------------------------------------

(1224,807.67)

------------------------------------------------------------------------

(1224.00,807.17)(1.500,1.000)2

------------------------------------------------------------------------

(1227,808.67)

------------------------------------------------------------------------

(1227.00,808.17)(1.000,1.000)2

------------------------------------------------------------------------

(1221.0,808.0)

------------------------------------------------------------------------

(1232,809.67)

------------------------------------------------------------------------

(1232.00,809.17)(1.500,1.000)2

------------------------------------------------------------------------

(1229.0,810.0)

------------------------------------------------------------------------

(1237,810.67)

------------------------------------------------------------------------

(1237.00,810.17)(1.500,1.000)2

------------------------------------------------------------------------

(1240,811.67)

------------------------------------------------------------------------

(1240.00,811.17)(1.000,1.000)2

------------------------------------------------------------------------

(1235.0,811.0)

------------------------------------------------------------------------

(1245,812.67)

------------------------------------------------------------------------

(1245.00,812.17)(1.500,1.000)2

------------------------------------------------------------------------

(1242.0,813.0)

------------------------------------------------------------------------

(1250,813.67)

------------------------------------------------------------------------

(1250.00,813.17)(1.500,1.000)2

------------------------------------------------------------------------

(1253,814.67)

------------------------------------------------------------------------

(1253.00,814.17)(1.500,1.000)2

------------------------------------------------------------------------

(1248.0,814.0)

------------------------------------------------------------------------

(1258,815.67)

------------------------------------------------------------------------

(1258.00,815.17)(1.500,1.000)2

------------------------------------------------------------------------

(1256.0,816.0)

------------------------------------------------------------------------

(1263,816.67)

------------------------------------------------------------------------

(1263.00,816.17)(1.500,1.000)2

------------------------------------------------------------------------

(1261.0,817.0)

------------------------------------------------------------------------

(1269,817.67)

------------------------------------------------------------------------

(1269.00,817.17)(1.000,1.000)2

------------------------------------------------------------------------

(1271,818.67)

------------------------------------------------------------------------

(1271.00,818.17)(1.500,1.000)2

------------------------------------------------------------------------

(1266.0,818.0)

------------------------------------------------------------------------

(1276,819.67)

------------------------------------------------------------------------

(1276.00,819.17)(1.500,1.000)2

------------------------------------------------------------------------

(1274.0,820.0)

------------------------------------------------------------------------

(1282,820.67)

------------------------------------------------------------------------

(1282.00,820.17)(1.000,1.000)2

------------------------------------------------------------------------

(1279.0,821.0)

------------------------------------------------------------------------

(1287,821.67)

------------------------------------------------------------------------

(1287.00,821.17)(1.500,1.000)2

------------------------------------------------------------------------

(1284.0,822.0)

------------------------------------------------------------------------

(1292,822.67)

------------------------------------------------------------------------

(1292.00,822.17)(1.500,1.000)2

------------------------------------------------------------------------

(1290.0,823.0)

------------------------------------------------------------------------

(1297,823.67)

------------------------------------------------------------------------

(1297.00,823.17)(1.500,1.000)2

------------------------------------------------------------------------

(1300,824.67)

------------------------------------------------------------------------

(1300.00,824.17)(1.500,1.000)2

------------------------------------------------------------------------

(1295.0,824.0)

------------------------------------------------------------------------

(1305,825.67)

------------------------------------------------------------------------

(1305.00,825.17)(1.500,1.000)2

------------------------------------------------------------------------

(1303.0,826.0)

------------------------------------------------------------------------

(1311,826.67)

------------------------------------------------------------------------

(1311.00,826.17)(1.000,1.000)2

------------------------------------------------------------------------

(1308.0,827.0)

------------------------------------------------------------------------

(1316,827.67)

------------------------------------------------------------------------

(1316.00,827.17)(1.000,1.000)2

------------------------------------------------------------------------

(1313.0,828.0)

------------------------------------------------------------------------

(1321,828.67)

------------------------------------------------------------------------

(1321.00,828.17)(1.500,1.000)2

------------------------------------------------------------------------

(1318.0,829.0)

------------------------------------------------------------------------

(1326,829.67)

------------------------------------------------------------------------

(1326.00,829.17)(1.500,1.000)2

------------------------------------------------------------------------

(1324.0,830.0)

------------------------------------------------------------------------

(1332,830.67)

------------------------------------------------------------------------

(1332.00,830.17)(1.000,1.000)2

------------------------------------------------------------------------

(1329.0,831.0)

------------------------------------------------------------------------

(1337,831.67)

------------------------------------------------------------------------

(1337.00,831.17)(1.000,1.000)2

------------------------------------------------------------------------

(1334.0,832.0)

------------------------------------------------------------------------

(1342,832.67)

------------------------------------------------------------------------

(1342.00,832.17)(1.500,1.000)2

------------------------------------------------------------------------

(1339.0,833.0)

------------------------------------------------------------------------

(1347,833.67)

------------------------------------------------------------------------

(1347.00,833.17)(1.500,1.000)2

------------------------------------------------------------------------

(1345.0,834.0)

------------------------------------------------------------------------

(1352,834.67)

------------------------------------------------------------------------

(1352.00,834.17)(1.500,1.000)2

------------------------------------------------------------------------

(1350.0,835.0)

------------------------------------------------------------------------

(1358,835.67)

------------------------------------------------------------------------

(1358.00,835.17)(1.000,1.000)2

------------------------------------------------------------------------

(1355.0,836.0)

------------------------------------------------------------------------

(1366,836.67)

------------------------------------------------------------------------

(1366.00,836.17)(1.000,1.000)2

------------------------------------------------------------------------

(1360.0,837.0)

------------------------------------------------------------------------

(1371,837.67)

------------------------------------------------------------------------

(1371.00,837.17)(1.000,1.000)2

------------------------------------------------------------------------

(1368.0,838.0)

------------------------------------------------------------------------

(1376,838.67)

------------------------------------------------------------------------

(1376.00,838.17)(1.500,1.000)2

------------------------------------------------------------------------

(1373.0,839.0)

------------------------------------------------------------------------

(1381,839.67)

------------------------------------------------------------------------

(1381.00,839.17)(1.500,1.000)2

------------------------------------------------------------------------

(1379.0,840.0)

------------------------------------------------------------------------

(1387,840.67)

------------------------------------------------------------------------

(1387.00,840.17)(1.000,1.000)2

------------------------------------------------------------------------

(1384.0,841.0)

------------------------------------------------------------------------

(1392,841.67)

------------------------------------------------------------------------

(1392.00,841.17)(1.000,1.000)2

------------------------------------------------------------------------

(1389.0,842.0)

------------------------------------------------------------------------

(1400,842.67)

------------------------------------------------------------------------

(1400.00,842.17)(1.000,1.000)2

------------------------------------------------------------------------

(1394.0,843.0)

------------------------------------------------------------------------

(1405,843.67)

------------------------------------------------------------------------

(1405.00,843.17)(1.500,1.000)2

------------------------------------------------------------------------

(1402.0,844.0)

------------------------------------------------------------------------

(1410,844.67)

------------------------------------------------------------------------

(1410.00,844.17)(1.500,1.000)2

------------------------------------------------------------------------

(1408.0,845.0)

------------------------------------------------------------------------

(1418,845.67)

------------------------------------------------------------------------

(1418.00,845.17)(1.500,1.000)2

------------------------------------------------------------------------

(1413.0,846.0)

------------------------------------------------------------------------

(1423,846.67)

------------------------------------------------------------------------

(1423.00,846.17)(1.500,1.000)2

------------------------------------------------------------------------

(1421.0,847.0)

------------------------------------------------------------------------

(1429,847.67)

------------------------------------------------------------------------

(1429.00,847.17)(1.000,1.000)2

------------------------------------------------------------------------

(1426.0,848.0)

------------------------------------------------------------------------

(1436,848.67)

------------------------------------------------------------------------

(1436.00,848.17)(1.500,1.000)2

------------------------------------------------------------------------

(1431.0,849.0)

------------------------------------------------------------------------

(131.0,131.0)

------------------------------------------------------------------------

(131.0,131.0)

------------------------------------------------------------------------

(1439.0,131.0)

------------------------------------------------------------------------

(131.0,859.0)

------------------------------------------------------------------------

Looking at the $y$ axis, we note that it is important to store the image
using floating point numbers. If we don't, there will be enormous
quantisation problems.

To convert the greyscale image from `unsigned char` to `float`, we use:

``` {.c++ language="c++" caption="Convert an image into floating point numbers."}
// Convert to float
        cv::Mat float_image;
        grey_image.convertTo(float_image, CV_32FC1);
```

It can be seen on the figure that $\log(x) \forall x \in ]-\infty,  0]$
is undefined. In other word, if $x$ is equal to zero or $x$ is negative,
then there is no $y$ value. As the input image was using
`unsigned char`, we do not have to worry about negative values. However,
we have to make sure no $0$ value is present in the image. To do so, we
apply the following transformation: $$f'(x,y) = \log(f(x,y) + 1)$$ using

``` {.c++ language="c++"}
// Log transformation
        cv::Mat log_image;
        cv::log(float_image + 1.0, log_image);
```

Looking at the curve, we notice another problem. In some case, $\log(x)$
may be negative. In this case, it is common to normalise the image so
that its values lie in the range $[0, 1]$ using:
$$f''(x,y) = \frac{f'(x,y) - \min(f')}{\max(f') - \min(f')}\label{eq:normal}$$

There are two ways to achieve this in OpenCV. You can implement
Eq. [\[eq:normal\]](#eq:normal){reference-type="ref"
reference="eq:normal"} using:

``` {.c++ language="c++"}
double min, max;
        cv::minMaxLoc(log_image, &min, &max);
        cv::Mat normalised_image = 255.0 * (log_image - min) / (max - min);
        normalised_image.convertTo(normalised_image, CV_8UC1);
```

or you can use OpenCV's function:

``` {.c++ language="c++"}
// Normalisation
        cv::Mat normalised_image;
        cv::normalize(log_image, normalised_image, 0, 255, cv::NORM_MINMAX, CV_8UC1);
```

Now you can display and save the image (see
Figure [11](#fig:logFilter){reference-type="ref"
reference="fig:logFilter"}.

  ------------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------
   ![[\[fig:logFilter\]]{#fig:logFilter label="fig:logFilter"}Input and output of **logScale**.](lake.png){#fig:logFilter width="35%"}   ![[\[fig:logFilter\]]{#fig:logFilter label="fig:logFilter"}Input and output of **logScale**.](lake_log.png){#fig:logFilter width="35%"}
                                                           \(a\) Input image.                                                                                                                      \(b\) Output image.
  ------------------------------------------------------------------------------------------------------------------------------------- -----------------------------------------------------------------------------------------------------------------------------------------

Additional tasks
================

Investigate the use of the median and Gaussian filters. The help page
for image filtering is availalbe at
<https://docs.opencv.org/4.0.1/d4/d86/group__imgproc__filter.html>

-   For `cv::medianBlur`, look at\
    <https://docs.opencv.org/4.0.1/d4/d86/group__imgproc__filter.html#ga564869aa33e58769b4469101aac458f9>

-   For `cv::GaussianBlur`, look at
    <https://docs.opencv.org/4.0.1/d4/d86/group__imgproc__filter.html#gaabe8c836e97159a9193fb0b11ac52cf1> -->
