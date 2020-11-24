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

| +1 | 0 | -1 |
| +2 | 0 | -2 |
| +1 | 0 | -1 |

$\mathbf{G}_x = \left[\begin{array}{ccc}
+1 & 0 & -1\\
+2 & 0 & -2\\
+1 & 0 & -1\\
\end{array}\right]$

$\mathbf{G}_y = \left[\begin{array}{ccc}
+1 & +2 & +1\\
0 & 0 & 0\\
-1 & -2 & -1\\
\end{array}\right]$
