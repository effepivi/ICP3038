---
title: Lab 9 -- Gradient magnitude and Sharpening of a blurry image
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 9
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---

# Introduction

Last week we implemented the spatial convolution. We will use it this week. We will also use our point operators.

# Gradient magnitude using the Sobel operator

The Sobel operator makes use of two 3×3 convolution kernels <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_x" alt="gx" /> and <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_y" alt="gy" />.

![$g_x$ Sobel kernel](img/g_x.png)
<!-- mathbf{g}_x=\left[\begin{array}{ccc}+1&0&-1\\+2&0&-2\\+1&0&-1\\\end{array}\right]" alt="g_x Sobel kernel" /> -->

![$g_y$ Sobel kernel](img/g_y.png)
<!-- \mathbf{G}_y=\left[\begin{array}{ccc}+1&+2&+1\\0&0&0\\-1&-2&-1\\\end{array}\right]-->

The first one is used to compute an approximation of the vertical derivative (<img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x" alt="Gx" />); the second to compute an approximation of the horizontal derivative (<img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y" alt="Gy" />).
Consider the following images.

|  Input: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{Img}" alt="Img" /> | Vertical derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x=\mathrm{g}_x * \mathrm{Img}" alt="Gx = gx * Img" /> | Horizontal derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y=\mathrm{g}_y * \mathrm{Img}" alt="Gy = gy * Img" /> |
|-------|-------|-------|
![Example image: Img](img/Img.png) | ![$G_x$](img/vertical-derivative.png) |![$G_y$](img/horizontal-derivative.png)|

Convolutions using <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_x" alt="gx" /> and <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_y" alt="gy" /> produce output images with pixels values that are negative, null and positive.

| Image  | Mean    | Std dev | Min      | Max     |
|--------|---------|---------|----------|---------|
| **Img**| 135.511 | 25.599  | 5        | 253.667 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x" alt="Gx" /> | -0.160  | 38.756  | -659.333 | 432.000 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y" alt="Gy" /> | 0.078   | 41.165  | -580.667 | 520.000 |

There are two ways to compute the gradient magnitude from <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x" alt="Gx" /> and <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y" alt="Gy" />:

1. A fast approximation: ![G=|Gx| + |Gy|](img/G-abs.png)
<!-- <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G} = |\mathrm{G}_x| + |\mathrm{G}_y|" alt="G=|Gx| + |Gy|" /> -->

2. A slower, but more accurate, calculation: ![sqrt(Gx^2 + Gy^2)](img/G-square.png)
<!-- <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G} = \sqrt{\mathrm{G}_x^2 + \mathrm{G}_y^2}" alt="G=sqrt(Gx^2 + Gy^2)" /> -->

Both methods are equally fine. Choose one.
If you choose 1., well maybe you want to add a new point operator `Image Image::abs() const` (hint, hint).
If you choose 2., maybe you want to add two new point operators `Image Image::square() const` and `Image Image::sqrt() const`.
The table below shows the statistics for the different images.

| Image  | Mean    | Std dev | Min      | Max     |
|--------|---------|---------|----------|---------|
| **Img**| 135.511 | 25.599  | 5        | 253.667 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x" alt="Gx" /> | -0.160  | 38.756  | -659.333 | 432.000 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y" alt="Gy" /> | 0.078   | 41.165  | -580.667 | 520.000 |
| <img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_x\|" alt="\|Gx\|" /> | 27.056 | 31.024 |0 |580.667 |
| <img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_y\|" alt="\|Gy\|" /> | 25.560 | 29.132 | 0 | 659.333 |
| <img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_x\|" alt="\|Gx\|" /> + <img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_y\|" alt="\|Gy\|" /> | 52.617 | 49.340 | 0 | 848.667 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x^2" alt="Gx^2" /> | 1694.552 | 5247.248 | 0 | 337173.812 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y^2" alt="Gy^2" /> | 1502.017 | 4540.478 | 0 | 434720.500 |
| <img src="https://render.githubusercontent.com/render/math?math=\sqrt{\mathrm{G}_x^2 + \mathrm{G}_y^2}" alt="G=sqrt(Gx^2 + Gy^2)" /> |  41.438 | 38.464 | 0 | 659.527 |


|  Input: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{Img}" alt="Img" /> | Vertical derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x=\mathrm{g}_x * \mathrm{Img}" alt="Gx = gx * Img" /> | Horizontal derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y=\mathrm{g}_y * \mathrm{Img}" alt="Gy = gy * Img" /> |<img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_x\|" alt="\|Gx\|" /> + <img src="https://render.githubusercontent.com/render/math?math=\|\mathrm{G}_y\|" alt="\|Gy\|" /> |
|-------|-------|-------|-------|
![Example image: Img](img/Img.png) | ![$G_x$](img/vertical-derivative-abs.png) |![$G_y$](img/horizontal-derivative-abs.png) |![$G_y$](img/img-G-abs.png)|



**As you can see, even if the dynamic range of the input image is withn the [0,255] range, the output images are not.** In other words, before saving the data in an image file format such as JPEG, make sure to normalise the image. For an ASCII file, do not normalise the image. You may wish to use the code below:

```cpp
std::string output_filename = argv[2];
std::string capital_filename;

// Capitalise
for (int i = 0; i < temp_filename.size(); ++i)
    capital_filename += std::toupper(temp_filename[i]);

if (std::string(aFilename).size() > 4)
{
    // Save an ASCII image file: Do not normalise
    if(capital_filename.substr( capital_filename.length() - 4 ) == ".TXT")
    {
        output.save(output_filename);
    }
    // Save the data using an image file format: Normalise
    else
    {
        (output.normalise() * 255).save(output_filename);
    }
}
```
