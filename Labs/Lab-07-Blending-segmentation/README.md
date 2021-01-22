# This week

- We'll replace [libjpeg-turbo](https://libjpeg-turbo.org/) with [OpenCV 4.5.0](https://sourceforge.net/projects/opencvlibrary/files/4.5.0/opencv-4.5.0-vc14_vc15.exe/download) to load image files. Somehow the binaries for Windows don't work :-(
- Load/Save ASCII files.
- Unit test the load and save methods with JPEG, PNG and ASCII files.
- Write a command line tool to improve the brightness and contrast of an image using point operators.
- Write a command line tool to compute the negative of an image using point operators.
- Write a command line tool to generate an animation using image blending.

# Install OpenCV

## MacOS X

See Homebrew at: [https://formulae.brew.sh/formula/opencv](https://formulae.brew.sh/formula/opencv)

## MS Windows

1. Download [OpenCV 4.5.0](https://sourceforge.net/projects/opencvlibrary/files/4.5.0/opencv-4.5.0-vc14_vc15.exe/download) at [https://sourceforge.net/projects/opencvlibrary/files/4.5.0/opencv-4.5.0-vc14_vc15.exe/download](https://sourceforge.net/projects/opencvlibrary/files/4.5.0/opencv-4.5.0-vc14_vc15.exe/download).
2. Run `opencv-4.5.0-vc14_vc15.exe` once it is downloaded.
3. **Extract to `C:\`** It is important to use this path as it is where CMake will look for OpenCV. If you installed it somewhere else, you'll have to edit the line below accordingly (`LIST(APPEND CMAKE_PREFIX_PATH  "C:/opencv/build")`).

# Replace LibJPEG-turbo with OpenCV

1. In the `CMakeLists.txt` file, replace the code related to the LibJPEG library with OpenCV's:

```cmake
# Find the libJPEG
FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
    add_definitions(-DHAS_LIBJPEG)
ELSE(JPEG_FOUND)
    MESSAGE(WARNING "JPEG not found.")
ENDIF(JPEG_FOUND)
```

becomes:

```cmake
# Find OpenCV

# Add where OpenCV might be installed (look in D: first, then in C:)
IF (WIN32)
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/opencv/build")
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/opencv/build")
ENDIF (WIN32)

FIND_PACKAGE(OpenCV REQUIRED)
IF(OpenCV_FOUND)
    add_definitions(-DHAS_OPENCV)

    # If windows is used, copy the dlls into the project directory
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
ELSE(OpenCV_FOUND)
    MESSAGE(WARNING "OpenCV not found.")
ENDIF(OpenCV_FOUND)
```

To make your life easier, I make sure DLLs are copied from OpenCV's directory into your project directory.

`${JPEG_INCLUDE_DIR}` becomes `${OpenCV_INCLUDE_DIRS}`

`${JPEG_LIBRARY}` becomes `${OpenCV_LIBS}` and

`${JPEG_FOUND}` becomes `${OpenCV_FOUND}`


2. In `Image.cxx`, change the header file inclusion:

```cxx
#ifdef HAS_LIBJPEG
#include <jerror.h>
#include <jpeglib.h>
#endif
```

becomes

```cxx
#include <algorithm> // For std::min
#include <cstring> // For toupper
#include <fstream> // For ofstream and ifstream

#ifdef HAS_OPENCV
#include <opencv2/opencv.hpp>
#endif
```

3. Remove the content of `void Image::load(const char* aFilename)` and replace it with:

```cpp
    std::string temp_filename = aFilename;
    std::string capital_filename;

    // Capitalise
    for (int i = 0; i < temp_filename.size(); ++i)
        capital_filename += std::toupper(temp_filename[i]);

    if (std::string(aFilename).size() > 4)
    {
        // Load a text file
        if(capital_filename.substr( capital_filename.length() - 4 ) == ".TXT")
        {
            // Open the file
            std::ifstream input_file (aFilename);

            // The file is not open
            if (!input_file.is_open())
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

            // Empty the image
            m_pixel_data.clear();
            m_width = 0;
            m_height = 0;

            // Load the data into a vector
            std::string line;
            int number_of_rows(0);
            int number_of_columns(0);

            // Read evely line
            while (std::getline(input_file, line))
            {
                number_of_columns = 0;
                float intensity;
                std::stringstream line_parser;
                line_parser << line;
                while (line_parser >> intensity)
                {
                	m_pixel_data.push_back(intensity);
                    ++number_of_columns;
                }
                ++number_of_rows;
            }

            // Wrong number of pixels
            if (number_of_rows * number_of_columns != m_pixel_data.size())
            {
                // Format a nice error message
                std::stringstream error_message;
                error_message << "ERROR:" << std::endl;
                error_message << "\tin File:" << __FILE__ << std::endl;
                error_message << "\tin Function:" << __FUNCTION__ << std::endl;
                error_message << "\tat Line:" << __LINE__ << std::endl;
                error_message << "\tMESSAGE: The file " << aFilename << " is invalid" << std::endl;
                throw std::runtime_error(error_message.str());
            }

            // Allocate memory for file content
            m_width = number_of_columns;
            m_height = number_of_rows;
            m_stats_up_to_date = false;
        }
        // Use OpenCV
        else
        {
#ifdef HAS_OPENCV
            // Open the image in greyscale
            cv::Mat temp_image = cv::imread( aFilename, cv::IMREAD_GRAYSCALE);

            // The image did not load
            if ( !temp_image.data )
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

            // Save the size of the image
            m_width = temp_image.cols;
            m_height = temp_image.rows;
            m_pixel_data.resize(m_width * m_height);

            // Copy the pixel data
            cv::Mat img_float;
            temp_image.convertTo(img_float, CV_32F);
            for (int i = 0; i < m_width * m_height; ++i)
            {
                int x = i / m_width;
                int y = i % m_width;

                m_pixel_data[i] = img_float.at<float>(x, y);
            }


            // The statistics is not up-to-date
            m_stats_up_to_date = false;
#else
            // Format a nice error message
            std::stringstream error_message;
            error_message << "ERROR:" << std::endl;
            error_message << "\tin File:" << __FILE__ << std::endl;
            error_message << "\tin Function:" << __FUNCTION__ << std::endl;
            error_message << "\tat Line:" << __LINE__ << std::endl;
            error_message << "\tMESSAGE: OpenCV not supported" << std::endl;
            throw std::runtime_error(error_message.str());
#endif
        }
    }
    // Don't know the file type
    else
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Can't open " << aFilename << ", I don't understand the file type." << std::endl;
        throw std::runtime_error(error_message.str());
    }
```

You can now load ASCII files using our own code, or image files using OpenCV.

4. Rename the `saveJPEG` methods from both `Image.h` and `Image.cxx` into `save`.

5. Remove the content of `void Image::save(const char* aFilename)` and replace it with:

```cpp
    std::string temp_filename = aFilename;
    std::string capital_filename;

    // Capitalise
    for (int i = 0; i < temp_filename.size(); ++i)
        capital_filename += std::toupper(temp_filename[i]);

    if (std::string(aFilename).size() > 4)
    {
        // Load a text file
        if(capital_filename.substr( capital_filename.length() - 4 ) == ".TXT")
        {
            // Open the file
            std::ofstream output_file (aFilename);

            // The file is not open
            if (!output_file.is_open())
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

            // Write content to file
            float* p_data(getPixelPointer());
            for (unsigned int j(0); j < m_height; ++j)
            {
                for (unsigned int i(0); i < m_width; ++i)
                {
                    output_file << *p_data++;

                    // This is not the last pixel of the line
                    if (i < m_width - 1)
                    {
                        output_file << " ";
                    }
                }

                // This is not the last line
                if (j < m_height - 1)
                {
                    output_file << std::endl;
                }
            }
        }
        // Use OpenCV
        else
        {
#ifdef HAS_OPENCV
            // Convert the data into an OpenCV Mat instance.
            cv::Mat temp_image(m_height, m_width, CV_32FC1, (float*)getPixelPointer());

            // Write the data
            cv::imwrite(aFilename, temp_image);

#else
            // Format a nice error message
            std::stringstream error_message;
            error_message << "ERROR:" << std::endl;
            error_message << "\tin File:" << __FILE__ << std::endl;
            error_message << "\tin Function:" << __FUNCTION__ << std::endl;
            error_message << "\tat Line:" << __LINE__ << std::endl;
            error_message << "\tMESSAGE: OpenCV not supported" << std::endl;
            throw std::runtime_error(error_message.str());
#endif
        }
    }
    // Don't know the file type
    else
    {
        // Format a nice error message
        std::stringstream error_message;
        error_message << "ERROR:" << std::endl;
        error_message << "\tin File:" << __FILE__ << std::endl;
        error_message << "\tin Function:" << __FUNCTION__ << std::endl;
        error_message << "\tat Line:" << __LINE__ << std::endl;
        error_message << "\tMESSAGE: Can't save " << aFilename << ", I don't understand the file type." << std::endl;
        throw std::runtime_error(error_message.str());
    }
```

You can now save ASCII files using our own code, or image files using OpenCV.

# Testing load/save?

If we load an image, and we know already some of its properties, we can check that we can retrieve the same properties. Right?

1. Add a new unit test in `CMakeLists.txt`. I called it `test-load-save.cxx`

2. In docs, there is a test image called `tulips.png`.

![`tulips.png`](docs/tulips.png)

Copy it in your binary directory using in `CMakeLists.txt`:

```cmake
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/docs/tulips.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
```

3. Open the file in ImageJ/Fiji and look at the image statistics (`<CTRL+M>`). Make a note of the image size, the average pixel value, etc.

| Width | Height | Number of pixels | Mean | StdDev | Min | Max |
|-------|--------|------------------|------|--------|-----|-----|
| 768   | 512    |	393216	        |101.540 |	59.634 |	3	| 242|

To test our functions, load the PNG image and check if you can retrieve all this values:

```cpp
// Test the load method
TEST(LoadSave, LoadPNG)
{
    Image input_image("tulips.png");

    ASSERT_EQ(input_image.getWidth(), xxx);
    ASSERT_EQ(input_image.getHeight(), xxx);
    ASSERT_EQ(input_image.getWidth() * input_image.getHeight(), xxx);

    ASSERT_NEAR(input_image.getMean(), xxx, 1);
    ASSERT_NEAR(input_image.getStdDev(), xxx, 1);
    ASSERT_NEAR(input_image.getMinValue(), xxx, 1);
    ASSERT_NEAR(input_image.getMaxValue(), xxx, 1);
}
```

(replace `xxx` above with the right values).

Now, it's about time to add `getMean()` and `getStdDev()`. Add the methods in `Image.h` and `Image.cxx`. Use the same lazy evaluation as in `getMinValue()`.

Now you may compile and run your test.

4. We now need to test the save method:

```cpp
TEST(LoadSave, SavePNG)
{
    Image input_image("tulips.png");
    input_image.save("output.jpg");

    Image output_image("output.jpg");

    ASSERT_EQ(output_image.getWidth(), 768);
    ASSERT_EQ(output_image.getHeight(), 512);
    ASSERT_EQ(output_image.getWidth() * output_image.getHeight(), 393216);

    ASSERT_NEAR(output_image.getMean(), 101.540, 2);
    ASSERT_NEAR(output_image.getStdDev(), 59.634, 2);
    ASSERT_NEAR(output_image.getMinValue(), 3, 2);
    ASSERT_NEAR(output_image.getMaxValue(), 242, 2);
}
```

5. What about ASCII files?

We'll create a known test image and apply the same methodology:

```cpp
// Test ASCII files
TEST(LoadSave, LoadSaveASCII)
{
    // Create a 3x2 image
    Image input_image({1, 2, 3, 4, 5, 6}, 3, 2);

    // Save the image in a text file
    input_image.save("output.txt");

    // Load the text file
    Image output_image("output.txt");

    // Check the image size
    ASSERT_EQ(output_image.getWidth(), 3);
    ASSERT_EQ(output_image.getHeight(), 2);
    ASSERT_EQ(output_image.getWidth() * output_image.getHeight(), 6);

    // Check the image stats
    ASSERT_NEAR(output_image.getMean(), (1 + 2 + 3 + 4 + 5 + 6) / 6.0, 1.0 / 6.0);
    ASSERT_NEAR(output_image.getMinValue(), 1, 1.0 / 6.0);
    ASSERT_NEAR(output_image.getMaxValue(), 6, 1.0 / 6.0);

    // Check all the pixel values
    ASSERT_NEAR(output_image(0, 0), 1, 1.0 / 6.0);
    ASSERT_NEAR(output_image(1, 0), 2, 1.0 / 6.0);
    ASSERT_NEAR(output_image(2, 0), 3, 1.0 / 6.0);
    ASSERT_NEAR(output_image(0, 1), 4, 1.0 / 6.0);
    ASSERT_NEAR(output_image(1, 1), 5, 1.0 / 6.0);
    ASSERT_NEAR(output_image(2, 1), 6, 1.0 / 6.0);

}
```

Look at the content of `output.txt`. It should be:

```
1 2 3
4 5 6
```


# Contrast enhancement

See Slides 44-48/54 of [ICP3038-Chapter_03-Introduction_image_processing.html](https://blackboard.bangor.ac.uk/bbcswebdav/pid-3305945-dt-content-rid-9603869_1/courses/1542.202021/3-Introduction_image_processing/ICP3038-Chapter_03-Introduction_image_processing.html#(44)) for a recap.


If you haven't done it yet, you can create a new program, e.g. `contrastEnhancement.cxx` with:

```cpp
#include <iostream>
#include <exception>
#include <string>

#include "Image.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        if argc == 3)
        {
            Image input(argv[1]);

            input -= input.getMinValue();
            input /= input.getMaxValue();
            input *= 255.0;

            // Same as
            // input = 255.0 * (input - input.getMinValue()) /
            //     (input.getMaxValue() - input.getMinValue());


            // Same as
            // input = 255.0 * input.normalise();

            image.save(argv[2]);
        }
        else
        {
            string error_message = std::string("Usage: ") + argv[0] + " input_image output_image";
            throw error_message;
        }
    }
    catch (const exception& e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e.what() << endl;
        return 1;
    }
    catch (const string& e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e << endl;
        return 2;
    }
    catch (const char* e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e << endl;
        return 3;
    }

    return 0;
}
```

In CMakeLists.txt, you need:

```cmake
# Compilation
ADD_EXECUTABLE(contrastEnhancement
    include/Image.h
    src/Image.cxx
    src/contrastEnhancement.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(contrastEnhancement PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(contrastEnhancement PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(contrastEnhancement ${OpenCV_LIBS})
```

To test your new program, use `docs/tulips-poor-contrast.png`. As you can see below, the contrast is VERY poor. Compile and run and visually check the output image.

![`tulips-poor-contrast.png`](docs/tulips-poor-contrast.png)

When I run

```bash
$ ./contrastEnhancement tulips-poor-contrast.png improved-poor-contrast.png
```

I get:

![`improved-poor-contrast.png`](docs/improved-poor-contrast.png)

**Remember, compile often, test often.**

In MSVC++, to pass command line arguments to a project:

1. Do a right-click on the project name in the Solution Explorer.
2. Click on `Properties` (bottom entry).
3. Go to `Debugging`.
4. Type your arguments in `Command Arguments`.
  - Remember to put paths between "" is you use the \\ character.

# Negative image

1. In CMakeLists.txt, you need:

```cmake
# Compilation
ADD_EXECUTABLE(negative
    include/Image.h
    src/Image.cxx
    src/negative.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(negative PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(negative PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(negative ${OpenCV_LIBS})
```

2. In `Image.h` add the declaration of the negation operator:

```cpp
//--------------------------------------------------------------------------
/// Compute the negative image
/**
* @return the negative image
*/
//--------------------------------------------------------------------------
Image operator!();
```

3. In `Image.cxx`, add its definition:

```cxx
Image Image::operator!()
{
    ...
}
```

Replace `...` with the appropriate formula using point operators. See Slide 53/54 of [ICP3038-Chapter_03-Introduction_image_processing.html](https://blackboard.bangor.ac.uk/bbcswebdav/pid-3305945-dt-content-rid-9603869_1/courses/1542.202021/3-Introduction_image_processing/ICP3038-Chapter_03-Introduction_image_processing.html#(53)):

```cxx
    return getMinValue() + getMaxValue() − *this;
```

4. Copy paste the content of `contrastEnhancement.cxx` into `negative.cxx`.
The only thing that the code really does is:

```cpp
            Image image(argv[1]);
            (!image).save(argv[2]);
```

**Don't forget the brackets around `!image`.**

5. When you compile it does not work. On my Linux box, I get:

```bash
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-07-Blending-segmentation/src/Image.cxx: In member function ‘Image Image::operator!()’:
/home/franck/PROGRAMMING/GitHub/ICP3038/Labs/Lab-07-Blending-segmentation/src/Image.cxx:557:42: error: no match for ‘operator-’ (operand types are ‘float’ and ‘Image’)
     return getMinValue() + getMaxValue() - *this;
            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~
make[2]: *** [CMakeFiles/contrastEnhancement.dir/build.make:80: CMakeFiles/contrastEnhancement.dir/src/Image.cxx.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:130: CMakeFiles/contrastEnhancement.dir/all] Error 2
make[1]: *** Waiting for unfinished jobs....
```

`Image operator-(float aValue, const Image& anImage);` is not declared. Let's address this problem. Add the declaration at the top of the `Image.h` file.
And the definition in `Image.cxx`:

Create a black image of the right size:

```cpp
    Image temp(0.0, anImage.getWidth(), anImage.getHeight());
```

Create two pointers on the raw pixel data of the input and output respectively:

```cpp
    float* p_output_data = temp.getPixelPointer();
    size_t number_of_pixels = temp.getWidth() * temp.getHeight();
```

Now you need to process all the pixels in a for loop:

```cpp
    size_t number_of_pixels = temp.getWidth() * temp.getHeight();
    for (size_t i = 0; i < number_of_pixels; ++i)
    {
        *p_output_data++ = aValue - *p_input_data++;
    }
```

You can now return the `temp` image.

The function should be:

```cpp
//-------------------------------------------------
Image operator-(float aValue, const Image& anImage)
//-------------------------------------------------
{
    // Create a black image of the right size:
    Image temp(0.0, anImage.getWidth(), anImage.getHeight());

    // Create two pointers on the raw pixel data of the input and output respectively:
    const float* p_input_data = anImage.getPixelPointer();
    float* p_output_data = temp.getPixelPointer();

    // Process all the pixels in a for loop:
    size_t number_of_pixels = temp.getWidth() * temp.getHeight();
    for (size_t i = 0; i < number_of_pixels; ++i)
    {
        *p_output_data++ += aValue - *p_input_data++;
    }

    // Return the new image
    return temp;
}
```

When I run

```bash
$ ./negative tulips.png negative.png
```

I get:

![`negative.png`](docs/negative.png)

# Blending

1. We are now going to write a program to blend tow images together, and create an animation.
The blending formula is:

(1.0 - alpha) * img1 + alpha * img2

with alpha between 0 and 1.

So, we need a new function:

```cxx
Image blending(float alpha, const Image& img1, const Image& img2)
```

that just returns:

```cxx
(1.0f - alpha) * img1 + alpha * img2
```
Go on, add the declaration at the top of `Image.h` and the definition in `Image.cxx`.

2. Now, the trouble is that `Image Image::operator+(const Image& img) const` does not exist as yet.
It corresponds to a pixel-wise addition of two images.
Add the declaration somewhere in the `Image` class in `Image.h`.

For the definition in `Image.cxx`, be careful. Let's start with a naive implementation:

```cxx
//--------------------------------------------
Image Image::operator+(const Image& img) const
//--------------------------------------------
{
    Image temp(0.0, m_width, m_height);

    for (size_t j = 0; j < temp.m_height; ++j)
    {
        for (size_t i = 0; i < temp.m_width; ++i)
        {
            temp(i,j) = (*this)(i, j) + img(i, j);
        }
    }
    return temp;
}
```

3. **What's the matter?**

Don't trust the user of your class. What if the two images do not have the same size?
Let's the program CRASH?? Nah. We've got to check if any error could occur. It's actually fairly easy. We limit the output image to the larger common area between the two input images:
Just change the declaration of `temp` into:

```cpp
Image temp(0.0, std::min(m_width, img.m_width), std::min(m_height, img.m_height));
```

To use `std::min` you nee to add the header inclusion of `<algorithm>` at the top of `Image.cxx`.

4. For completeness, and as they'll be needed later, add to your code the following operators:

    - `Image Image::operator-(const Image& img) const`
    - `Image Image::operator*(const Image& img) const`
    - `Image Image::operator/(const Image& img) const`
    - `Image& Image::operator+=(const Image& img)`
    - `Image& Image::operator-=(const Image& img)`
    - `Image& Image::operator*=(const Image& img)`
    - `Image& Image::operator/=(const Image& img)`


**Don't forget what I said in the past, COMPILE OFTEN**.

5. Edit CMakeLists.txt to support the new program:

```cmake
# Compilation
ADD_EXECUTABLE(blending
    include/Image.h
    src/Image.cxx
    src/blending.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(blending PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(blending PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(blending ${OpenCV_LIBS})
```

6. Add a new program, `blending.cxx`. It'll be used as follows:

```bash
$ ./blending input1 input2 NUM output
```

The program will create `NUM` images, transitioning smoothly from `input1` to `input2`.
The output images will be saved in `output_%i.png`.

In the main, we need to open the two input images, and retrieve `NUM`.
We then have a for loop. In the loop we:

- compute alpha using linear interpolation,
- perform the blending operation,
- create a filename with leading 0s, and
save the image.

```cpp
#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <iomanip>

#include "Image.h"

using namespace std;

int main(int argc, char** argv)
{
    try
    {
        if (argc == 5)
        {
            Image image1(argv[1]);
            Image image2(argv[2]);

            string number_of_frames_str = argv[3];

            int number_of_frames = stoi(number_of_frames_str);

            for (int i = 0; i < number_of_frames; ++i)
            {
                // Compute alpha
                float alpha = float(i) / (number_of_frames - 1);

                // Blend the images
                Image blend = blending(alpha, image1, image2);

                // Create a filename with leading 0s
                std::ostringstream filename;
                filename << argv[4] << "_" << std::setw(number_of_frames_str.size() - 1) << std::setfill('0') << i << ".png";

                // Save the image
                blend.save(filename.str());
            }
        }
        else
        {
            string error_message = "Usage: ";
            error_message += argv[0];
            error_message += " input1 input2 NUM output";
            throw error_message;
        }
    }
    catch (const exception& e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e.what() << endl;
        return 1;
    }
    catch (const string& e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e << endl;
        return 2;
    }
    catch (const char* e)
    {
        cerr << "An error occured, see the message below." << endl;
        cerr << e << endl;
        return 3;
    }

    return 0;
}
```

When I run on Linux or Mac:

```cpp
$ ./blending tulips.png negative.png 50 blend
$ convert blend_*.png blend.gif   # Only work on systems where ImageMagick is installed
```

I obtain this nice GIF file:

![blend.gif](docs/blend.gif)

If you use Windows (or even Linux or Mac), you could use ImageJ/Fiji to view your animation. Just use the `File->Import->Image sequence` menu.

# My final `CMakeLists.txt` file

```cmake
cmake_minimum_required(VERSION 3.10)

PROJECT (ICP3038-img-class VERSION 0.2)


# Use C++ 11
set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++11 is required (i.e. not optional)
set(CMAKE_CXX_EXTENSIONS OFF) # without compiler extensions like gnu++11

# Find OpenCV
LIST(APPEND CMAKE_PREFIX_PATH  "C:/opencv/build")
FIND_PACKAGE(OpenCV REQUIRED)
IF(OpenCV_FOUND)
    add_definitions(-DHAS_OPENCV)

    # If windows is used, copy the dlls into the project directory
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

ELSE(OpenCV_FOUND)
    MESSAGE(WARNING "OpenCV not found.")
ENDIF(OpenCV_FOUND)


# Build GoogleTest
INCLUDE(cmake/External_GTest.cmake)

# Enable unit testing
enable_testing()

# Compilation
ADD_EXECUTABLE(test-constructors
    include/Image.h
    src/Image.cxx
    src/test-constructors.cxx)

# Add dependency
ADD_DEPENDENCIES(test-constructors googletest)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-constructors PUBLIC include)
target_include_directories(test-constructors PUBLIC ${GTEST_INCLUDE_DIRS})

IF(OpenCV_FOUND)
    target_include_directories(test-constructors PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_directories(test-constructors PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-constructors ${GTEST_LIBRARIES} ${OpenCV_LIBS})

# Add the unit test
add_test (Constructors test-constructors)


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

IF(OpenCV_FOUND)
    target_include_directories(test-operators PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_directories(test-operators PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-operators ${GTEST_LIBRARIES} ${OpenCV_LIBS})

# Add the unit test
add_test (Operators test-operators)


# Compilation
ADD_EXECUTABLE(test-load-save
    include/Image.h
    src/Image.cxx
    src/test-load-save.cxx)

# Add dependency
ADD_DEPENDENCIES(test-load-save googletest)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-load-save PUBLIC include)
target_include_directories(test-load-save PUBLIC ${GTEST_INCLUDE_DIRS})

IF(OpenCV_FOUND)
    target_include_directories(test-load-save PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_directories(test-load-save PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-load-save ${GTEST_LIBRARIES} ${OpenCV_LIBS})

# Add the unit test
add_test (LoadSave test-load-save)


# Compilation
ADD_EXECUTABLE(contrastEnhancement
    include/Image.h
    src/Image.cxx
    src/contrastEnhancement.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(contrastEnhancement PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(contrastEnhancement PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(contrastEnhancement ${OpenCV_LIBS})


# Compilation
ADD_EXECUTABLE(negative
    include/Image.h
    src/Image.cxx
    src/negative.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(negative PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(negative PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(negative ${OpenCV_LIBS})


# Compilation
ADD_EXECUTABLE(blending
    include/Image.h
    src/Image.cxx
    src/blending.cxx)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(blending PUBLIC include)

IF(OpenCV_FOUND)
    target_include_directories(blending PUBLIC ${OpenCV_INCLUDE_DIRS})
ENDIF(OpenCV_FOUND)

# Add linkage
target_link_libraries(blending ${OpenCV_LIBS})



# The documentation build is an option. Set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)

    SET (PROJECT_NAME ICP3038-img-class)
    SET (PROJECT_DESCRIPTION "An Image class used in ICP3038 at Bangor University")

    # set input and output files
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

FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/docs/tulips.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
```

# Next  week

Image filtering.
