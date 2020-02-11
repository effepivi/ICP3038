# ICP3038 - Computer Vision (CV)
## Lab 10: Background subtraction
### Tutor: Franck Vidal

## Objectives

The aims of today's lab are:

- Processing a video stream, either from a file or the computer's webcam (note the camera as to be static);
- Implement a background subtraction (BS) algorithm:
    - Initialising the background;
    - Updating the background;
    - Generating the foreground mask;
    - Highlighting the pixels corresponding to moving components.

## Introduction
We want to generate a binary mask of the foreground.
The foreground corresponds to moving objects in the video stream.
The background corresponds to static elements in the video stream.
In both the foreground and background masts, pixel values are either 0 or 1. One mask is the negative of the other mask.

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

Reuse the code from last week, so that your program can
- read a video stream (either from a file or the webcam);
- display the input frames from the video stream;
- display 3 other images next to it.

## Background initialisation

At the start of the video processing, add your own function to initialise the background.

## Background subtraction

In the loop,

1. Read the new frame (NF);
2. perform the background subtraction to compute:

    1. The background mask (BM);
    2. The foreground mask (FM);
    3. Combine FM and NF so that a pixel value is equal:

        - to 0 if its pixel location corresponds to the background;
        - to NF's pixel colour if its location corresponds to the foreground.

## Background update

At the end of the loop, add your own function to update the background.

## Output

In the output window, we will display four images side by side. Make sure to use RGB in the visualisation. You need to create one large RGB image big enoguh to display four images.
BM and FM are binary images. They should be stored in greyscale encoding with unsigned char. Pixel values will be between 0 and 1. To visualise them, don't forget i) to use a temporary image where ii) to multiply all the pixels by 255, and iii) to convert them into RGB.

|----|---------|----|----|
| NF | NF * FM | BM | FM |


Note: Don't forget that you'll have to provide evidence of a working program when submitting your assignment.
<!--For example, Fig.~\ref{fig:screenshot2} shows my fish tank. -->For example you can upload your video files on YouTube or Blackboard<!--, see [https://www.youtube.com/watch?v=RbH2bdrNGbc](https://www.youtube.com/watch?v=RbH2bdrNGbc)-->.
