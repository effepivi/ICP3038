---
title: Lab 8 -- Image comparison and spatial convolution
author: Dr Franck P. Vidal
subtitle: ICE-3038-0 Computer Vision 202021
date: Week 8
keywords: ICP3038, Computer Vision, C/C++, image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
---

# Introduction

Last week we replaced the use of the LibJPEG with OpenCV. We also wrote a few programs:

1. Contrast enhancement, ![Original image](img/original.jpg) ![Contrast enhancement](img/improved_contrast.jpg)
2. Negative, ![Original image](img/original.jpg) ![Negative image](img/negative.jpg)
3. Blending of two images. This is the technique used to create a smooth and seamless transitions between two video sequences in films.![Image 1](img/original.jpg) ![Image 2](img/negative.jpg)  ![Blending of Images 1 and 2](img/blend.gif)  

This week, we will see how to

- Compare two images using he Root Mean Squared Error (RMSE) and the Zero mean Normalised-Cross Correlation (NCC).
- Filter images using the convolution.

# RMSE

**Don't compare two floating point numbers together**
If you are not convinced, look at my video here.
If you are still not convinced, look at this guide: [https://floating-point-gui.de/errors/comparison/](https://floating-point-gui.de/errors/comparison/)

For images, the Root Mean Squared Error (RMSE) and the Mean Absolute Error (MAE) are amongst the two most popular metrics used to compared images. There are widely used in statistics, computer vision, image analysis and machine learning. The RMSE between two images <img src="https://render.githubusercontent.com/render/math?math=I_1" /> and <img src="https://render.githubusercontent.com/render/math?math=I_2" /> is defined as:

<!-- ![RMSE formula](https://render.githubusercontent.com/render/math?math=RMSE(I_1, I_2)=\sqrt{\frac{1}{w\times h}\sum_j\sum_i\left(I_1(i,j)-I_1(i,j)\right)^2}) -->

<img src="https://render.githubusercontent.com/render/math?math=RMSE(I_1, I_2)=\sqrt{\frac{1}{w\times h}\sum_j\sum_i\left(I_1(i,j)-I_1(i,j)\right)^2}" alt="RMSE formula" />

with <img src="https://render.githubusercontent.com/render/math?math=w" /> and <img src="https://render.githubusercontent.com/render/math?math=h" /> the number of pixels along the horizontal and vertical axes respectively.

The errors in RMSE are squared. It means that a much larger weight is assigned to larger errors: An error of 10, is 100 times worse than an error of 1.


<!--


between two images
(hint: if the images have different sizes, throw an error or return a large number, e.g.
FLT_MAX that is declared in the cfloat header file). The RMSE can be used to measure
how different two images are. It is:
• 0 if they are the same; and
• > 0 if they are different.
2. The Zero mean Normalised-Cross Correlation (NCC) between two images
(hint: if the images have different sizes, throw an error). The ZNCC can be used to
measure how similar two images are. It is:
• 1 if they are fully correlated (i.e. they are extremely close to each other);
• 0 if they are fully uncorrelated (i.e. they are extremely different); and
• -1 if they are fully anticorrelated (i.e. one if the negative of the other one).
(hint: if the images have different sizes, throw an error or return 0) -->
