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

The Sobel operator makes use of two 3×3 convolution kernels **g**x and **g**y.

![$g_x$ Sobel kernel](img/g_x.png)
<!-- mathbf{g}_x=\left[\begin{array}{ccc}+1&0&-1\\+2&0&-2\\+1&0&-1\\\end{array}\right]" alt="g_x Sobel kernel" /> -->

![$g_y$ Sobel kernel](img/g_y.png)
<!-- \mathbf{G}_y=\left[\begin{array}{ccc}+1&+2&+1\\0&0&0\\-1&-2&-1\\\end{array}\right]-->

The first one is used to compute an approximation of the vertical derivative (**G**x); the second to compute an approximation of the horizontal derivative (**G**y).
Consider the image **Img** as follows:

![Example image: Img](img/Img.png)

**G**x =  **g**x * **Img**:

![$G_x$](img/vertical-derivative.png)
<!-- mathbf{g}_x=\left[\begin{array}{ccc}+1&0&-1\\+2&0&-2\\+1&0&-1\\\end{array}\right]" alt="g_x Sobel kernel" /> -->

**G**y =  **g**y * **Img**:

![$G_y$](img/horizontal-derivative.png)

<!-- \mathbf{G}_y=\left[\begin{array}{ccc}+1&+2&+1\\0&0&0\\-1&-2&-1\\\end{array}\right]-->


Convolutions using <img src="https://render.githubusercontent.com/render/math?math=\mathrm{g}_x" / alt="gx"> and **g**y produce output images with pixels values that are negative, null and positive.

| Image  | Mean    | Std dev | Min      | Max     |
|--------|---------|---------|----------|---------|
| Im     | 135.511 | 25.599  | 5        | 253.667 |
| **G**x | -0.160  | 38.756  | -659.333 | 432.000 |
| **G**y | 0.078   | 41.165  | -580.667 | 520.000 |
