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
Consider the following images. **Img** is the input image.

| **Img** | Vertical derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x=\mathrm{g}_x * \mathrm{Img}" alt="Gx = gx * Img" /> | Horizontal derivative: <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y=\mathrm{g}_y * \mathrm{Img}" alt="Gy = gy * Img" /> |
|-------|-------|-------|
![Example image: Img](img/Img.png) | ![$G_x$](img/vertical-derivative.png) |![$G_y$](img/horizontal-derivative.png)|

Convolutions using <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_x" alt="gx" /> and <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_y" alt="gy" /> produce output images with pixels values that are negative, null and positive.

| Image  | Mean    | Std dev | Min      | Max     |
|--------|---------|---------|----------|---------|
| **Img**| 135.511 | 25.599  | 5        | 253.667 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_x" alt="Gx" /> | -0.160  | 38.756  | -659.333 | 432.000 |
| <img src="https://render.githubusercontent.com/render/math?math=\mathrm{G}_y" alt="Gy" /> | 0.078   | 41.165  | -580.667 | 520.000 |
