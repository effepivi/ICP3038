# ICP3038 - Computer Vision (CV)
## Lab 10: Background subtraction
### Tutor: Franck Vidal

## Objectives

The aims of today's lab are:

  - Processing a video stream, either from a file or the computer's webcam (note that the camera as to be static);
  - Implement a background subtraction (BS) algorithm:
    - Initialising the background;
    - Updating the background;
    - Generating the foreground mask;
    - Highlighting the pixels corresponding to moving components.

## Introduction
We want to generate a binary mask of the foreground.
The foreground corresponds to moving objects in the video stream.
The background corresponds to static elements in the video stream.
In both the foreground and background masks, pixel values are either 0 or 1. One mask is the negative of the other mask.

|   | Foreground      | Background      |
|---|-----------------|-----------------|
| 0 | Static elements | Moving elements |
| 1 | Moving elements | Static elements |

Background subtraction is very commonly used for generating such masks.

## Create a new project

 1. Create a new directory with a meaningful name, e.g. `Lab10-background_subtraction/`.
 2. Copy `CMakeLists.txt` from last week and create a new source file, e.g. `background_subtractor.cxx`.
 3. Modify the new `CMakeLists.txt` file accordingly.

## Create a template program

Reuse the code from last week, so that your program can:

  - Read a video stream (either from a file or the webcam);
  - Display the input frames from the video stream;
  - Display 4 other images next to it.

## Background initialisation

At the start of the video processing, add your own function to initialise the background (BG). We discussed 3 ways to initialise the background:

  - Use the first frame (assuming there is no moving object in the image). Just clone the incoming frame into BG. It's not robust but quick to implement.
  - Use a temporal mean filter: Average the pixel values of the last *N* frames. It's a bit harder to implement, but it's more robust.
  - Use a temporal median filter of the last *N* frames. It's definitely harder to implement, but it's more robust.

(be strategic: i) impelement the easiest one, ii) then the rest of the functionalities of the program, and iii) if you have more time revisit the background initialisation function to implement a more robust algorithm).

## Background subtraction

In the loop,

 1. Read the new frame (NF);
 2. Perform the background subtraction to compute:

    1. The background mask (BM):
      
      - For each pixel (i,j) if |NF(i,j) - BG(i,j)| >= T, then BM(i,j) = 1, else BM(i,j) = 0;
      - Make sure BM is in greyscale, luminance, and that pixel values are in the range [0-1].
      
      (note: T is a threshold. You saw how to control a threshold value interactively using a trackbar).
      
    2. The foreground mask (FM):
    
      - Use the negative of BM;
        
    3. Combine FM and NF so that a pixel value is equal:

      - to 0 if its pixel location corresponds to the background;
      - to NF's pixel colour if its location corresponds to the foreground;
      - this is achieved using a pixel-wise product between FM and NF, which is why we need to use the range [0-1] in BM and FM. 
      
      (note: Before you can use the *mul* method, e.g. *FM.mul(NF)*, you have to convert FM into RGB.

## Background update

At the end of the loop, add your own function to update BG.

## Output

In the output window, we will display five images side by side. Make sure to use RGB in the visualisation. You need to create one large RGB image big enoguh to display five images.

  - NF is a RGB image;
  - BG is a RGB image;
  - NF * FM is a RGB image;
  - BM and FM are binary images. They should be stored in greyscale encoding with unsigned char. Pixel values will be between 0 and 1. To visualise them, don't forget i) to use a temporary image where ii)  to convert them into RGB and iii) to multiply all the pixels by 255.

The large output image/window will be formatted as fallows:

| img1 | img2 |   img3  | img4 | img5 |
|------|------|---------|------|------|
|  NF  |  BG  | NF * FM |  BM  |  FM  |

You can use `cv::putText` to label each sub-image in the output.


Note: Don't forget that you'll have to provide evidence of a working program when submitting your assignment.
<!--For example, Fig.~\ref{fig:screenshot2} shows my fish tank. -->For example you can upload your video files on YouTube or Blackboard<!--, see [https://www.youtube.com/watch?v=RbH2bdrNGbc](https://www.youtube.com/watch?v=RbH2bdrNGbc)-->.
