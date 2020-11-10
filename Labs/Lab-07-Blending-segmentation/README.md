# This week

- We'll replace [libjpeg-turbo](https://libjpeg-turbo.org/) with [OpenCV 4.5.0](https://sourceforge.net/projects/opencvlibrary/files/4.5.0/opencv-4.5.0-vc14_vc15.exe/download) to load image files. Somehow the binaries for Windows don't work :-(


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
FIND_PACKAGE(OpenCV REQUIRED)
IF(OpenCV_FOUND)
    add_definitions(-DHAS_OPENCV)
ELSE(OpenCV_FOUND)
    MESSAGE(WARNING "OpenCV not found.")
ENDIF(OpenCV_FOUND)
```

`${JPEG_INCLUDE_DIR}` becomes `${OpenCV_INCLUDE_DIRS}`

`${JPEG_LIBRARY}` becomes `${OpenCV_LIBS}`

`${JPEG_FOUND}` becomes `${OpenCV_FOUND}`

```cmake
${JPEG_LIBRARY}
```

becomes

```cmake
${OpenCV_LIBS}
```

and

JPEG_FOUND


2. In `Image.cxx`, change the header file inclusion:

```cxx
#ifdef HAS_LIBJPEG
#include <jerror.h>
#include <jpeglib.h>
#endif
```

becomes

```cxx
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
    Image input_image({1, 2, 3, 4, 5, 6}, 3, 2); // Create a 3x2 image
    input_image.save("output.txt");

    Image output_image("output.txt");

    ASSERT_EQ(output_image.getWidth(), 3);
    ASSERT_EQ(output_image.getHeight(), 2);
    ASSERT_EQ(output_image.getWidth() * output_image.getHeight(), 6);

    ASSERT_NEAR(output_image.getMean(), (1 + 2 + 3 + 4 + 5 + 6) / 6.0, 1.0 / 6.0);
    //ASSERT_NEAR(output_image.getStdDev(), 59.634, 2);
    ASSERT_NEAR(output_image.getMinValue(), 1, 1.0 / 6.0);
    ASSERT_NEAR(output_image.getMaxValue(), 6, 1.0 / 6.0);
}
```

Look at the content of `output.txt`. It should be:

```
1 2 3
4 5 6
```


# Contrast enhancement

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
            Image image(argv[1]);

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
            string error_message = "Usage: " + argv[0] + " input_image output_image";
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

# Negative image





# Next  week

We will add another 9 operators and we will perform some image processing tasks on actual images. Why not even create an animation!
