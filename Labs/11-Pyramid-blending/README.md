---
title: Lab 2 of Semester 2 -- Multi-scale image processing (pyramids)
author: Dr Franck P. Vidal
subtitle: ICP-3038 Computer Vision 202021
date: Semester 2
keywords: ICP3038, Computer Vision, C++, Image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
fontsize: 11pt
lang: en-gb
---

# 1. Synopsis

We will rely on multi-scale processing using pyramids to operates on an image represented at several sizes (scales):
  * Fine level
  * Coarse level

![Source:[https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/Image_pyramid.svg/500px-Image_pyramid.svg.png](https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/Image_pyramid.svg/500px-Image_pyramid.svg.png)](https://upload.wikimedia.org/wikipedia/commons/thumb/4/43/Image_pyramid.svg/500px-Image_pyramid.svg.png)

We will deploy what is called "pyramid blending" to merge two images together. Without pyramid blending, merging images produces a sharp edge were objects from the two images are merged:

![Stitching without blending](img/stitching1.png)

It is not the case with pyramid blending:

![Stitching with and without pyramid blending](img/stitching5.png)

You'll write your code in three different files (four if you count `CMakeLists.txt`):

- `Pyramid.h`: Guess what? In this file we will write the declarations of the functions to:
    - Create a Gaussian pyramid from an image;
    - Create a Laplacian pyramid from a Gaussian pyramid;
    - Display a pyramid; and
    - Reconstruct an image from its Laplacian pyramid.
- `Pyramid.cxx`: we will write the definition of the functions.
- `Orangeapple.cxx`: we will deploy the functions written in `Pyramid.cxx` in a program to blend the Laplacian pyramid of two images.

# 2. Have you done your homework?

This week we will reply on the knowledge learnt in the 2nd lecture of Semester, on *Multi-resolution images using Pyramids*. If you don't know what I am talking about, have a look at the slides now.

There are two main types of pyramids:

- Gaussian pyramid:
  ![Gaussian pyramid](img/orange_gaussian_pyramid.png)

- Laplacian pyramid:
  ![Laplacian pyramid](img/orange_laplacian_pyramid.png)


We will use both:

- We are going to merge the Laplacian pyramids of two images to create a new image.
- A Gaussian pyramid is needed to compute Laplacian a pyramid.

You are expected to study the code in the following Jupyter Notebook: [https://github.com/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb](https://nbviewer.jupyter.org/github/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb).






Let's start with the beginning, the declarations in the header file.
Remember, put a preamble at the top of your files. ALL YOUR FILES. See here for a real example: [https://sourceforge.net/p/gvirtualxray/code/HEAD/tree/trunk/gvxr/include/gVirtualXRay/PolygonMesh.h](https://sourceforge.net/p/gvirtualxray/code/HEAD/tree/trunk/gvxr/include/gVirtualXRay/PolygonMesh.h). The preamble helps identify who wrote the file, when, and what the code does.

## In `Pyramid.h`

1. Add the `#ifndef/#define/#endif`. I always like to do that first when I create a header file (just because we must not forget).

```cpp
#ifndef __Pyramid_h
#define __Pyramid_h

// The declarations go here


#endif // __Pyramid_h
```

2. Add the preamble

In `Pyramid.h`

```cpp
#ifndef __Pyramid_h
#define __Pyramid_h

/**
********************************************************************************
*
*   @file       PUT THE FILE NAME HERE
*
*   @brief      DESCRIBE WHAT THE FILE DOES IN ONE OR TWO LINES
*
*   @date       PUT THE DATE HERE
*
*   @author     PUT YOUR NAME HERE
*
*   @todo       PUT HERE ANYTHING THAT NEEDS DOING
*
********************************************************************************
*/


#endif // __Pyramid_h
```

3. Add the declarations.

Look at the Jupyter notebook ([https://github.com/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb](https://github.com/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb)) and identify all the functions.


4. Add the header files.

```cpp
#ifndef __Pyramid_h
#define __Pyramid_h

/**
********************************************************************************
*
*   @file       PUT THE FILE NAME HERE
*
*   @brief      DESCRIBE WHAT THE FILE DOES IN ONE OR TWO LINES
*
*   @date       PUT THE DATE HERE
*
*   @author     PUT YOUR NAME HERE
*
*   @todo       PUT HERE ANYTHING THAT NEEDS DOING
*
********************************************************************************
*/


//******************************************************************************
// Headers
//******************************************************************************
#include <vector>
#include <opencv2/opencv.hpp>


#endif // __Pyramid_h
```

5. Add the declarations.

```cpp
#ifndef __Pyramid_h
#define __Pyramid_h

/**
********************************************************************************
*
*   @file       PUT THE FILE NAME HERE
*
*   @brief      DESCRIBE WHAT THE FILE DOES IN ONE OR TWO LINES
*
*   @date       PUT THE DATE HERE
*
*   @author     PUT YOUR NAME HERE
*
*   @todo       PUT HERE ANYTHING THAT NEEDS DOING
*
********************************************************************************
*/


//******************************************************************************
// Headers
//******************************************************************************
#include <vector>
#include <opencv2/opencv.hpp>


//--------------------------------------------------------------------------
/// Create a Gaussian pyramid.
/**
 * @param anOriginalImage:    the image to process
 * @param aNumberOfLevels:    the number of levels in the pyramid
 * @return the Gaussian pyramid
 */
//--------------------------------------------------------------------------
std::vector<cv::Mat> createGaussianPyramid(const cv::Mat& anOriginalImage,
                                           size_t aNumberOfLevels);

//--------------------------------------------------------------------------
/// Create an image to visualise a pyramid (Gaussian or Laplacian).
/**
 * @param aPyramid:    the pyramid to visualise
 * @return the visualisation of the pyramid
 */
//--------------------------------------------------------------------------
cv::Mat displayPyramid(const std::vector<cv::Mat>& aPyramid);


//--------------------------------------------------------------------------
/// Create a Laplacian pyramid from a Gaussian pyramid.
/**
 * @param aGaussianPyramid:    the Gaussian pyramid
 * @return the corresponding Laplacian pyramid
 */
//--------------------------------------------------------------------------
std::vector<cv::Mat> createLaplacianPyramid(const std::vector<cv::Mat>& aGaussianPyramid);


//--------------------------------------------------------------------------
/// Reconstruct an image from the Laplacian pyramid at a given level.
/**
 * @param aLaplacianPyramid:    the Laplacian pyramid
 * @param aLevel:    the level
 * @return the corresponding reconstructed image
 */
//--------------------------------------------------------------------------
cv::Mat reconstruct(const std::vector<cv::Mat>& aLaplacianPyramid, int aLevel);


#endif // __Pyramid_h
```

## In `Pyramid.cxx`

1. Add the same preamble as what you have in `Pyramid.h` (just change the file name).
2. Include the header file (`Pyramid.h`).
3. Add the definitions. You can find the code in the Jupyter notebook ([https://github.com/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb](https://github.com/effepivi/ICP3038/blob/master/Lectures/9-Pyramids/notebooks/4-Image-stitching-with-pyramids-using-opencv.ipynb)).

We will exploit this code in the image stitching.




1. Write your **preamble** to identify your file.
2. Include the **header files**.
3. Add the **namespaces**.
4. Add the **`main`** function.
5. Load the image file of the **orange** in colour.
6. Check if the image **is loaded**
7. Check if the image size is a **power of two**.
8. Repeat steps 5, 6 and 7 with the image file of the apple.
9. **Display** both images for testing purposes.
10 Choose the **number of levels** in the pyramids, e.g. 6.
11. Compute the **Gaussian pyramid** of the orange.
12. Compute the **Gaussian pyramid** of the apple.
13. **Display** both Gaussian pyramids for testing purposes.
14. Compute the **Laplacian pyramid** of the orange.
15. Compute the **Laplacian pyramid** of the apple.
16. **Display** both Laplacian pyramids for testing purposes.
17. **For each level** of the Laplacian pyramids:
  - **Swap the two halves**.
