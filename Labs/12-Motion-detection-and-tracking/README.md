---
title: Lab 3 of Semester 2 -- Motion detection and Tracking
author: Dr Franck P. Vidal
subtitle: ICP-3038 Computer Vision 202021
date: Semester 2
keywords: ICP3038, Computer Vision, C++, Image processing, OpenCV, Bangor University, School of Computer Science and Electronic Engineering
institute: School of Computer Science and Electronic Engineering, Bangor University
fontsize: 11pt
lang: en-gb
---

# 1. Synopsis

This lab relies on the 4th lecture of Semester 2: Motion Detection and Tracking.
The technique you will use today:

- Open a video from a file,
- Save a video into a file,
- Implement the background subtraction algorithm,
  - Update the background,
  - Absolute difference between two images,
  - Binary thresholding,
  - Slider to control the threshold,
  - Cleaning a binary image using mathematical morphology (opening and closing),
  - Highlight moving objects,
  - Remove small objects,
- Estimate the motion of a moving object.

You'll write your code in a single file (two if you count `CMakeLists.txt`):

- `MotionDetection.cxx`.

# 2. Preliminaries

1. Edit the `CMakeLists.txt` file from last time to add the new program:

    ```cmake
    ADD_EXECUTABLE (MotionDetection MotionDetection.cxx)
    TARGET_INCLUDE_DIRECTORIES (MotionDetection PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
    TARGET_LINK_LIBRARIES (MotionDetection   ${OpenCV_LIBS})
    ```

2. Create the new file, `MotionDetection.cxx`.
3. Download the videos I provided:
    - ![one_moving_object.gif](./one_moving_object.gif)
      [one_moving_object.avi](./one_moving_object.avi)
    - ![change_of_lighting_conditions.gif](./change_of_lighting_conditions.gif)
      [change_of_lighting_conditions.avi](./change_of_lighting_conditions.avi)
    - ![two_moving_objects.gif](./two_moving_objects.gif)
      [two_moving_objects.avi](./two_moving_objects.avi)
4. Edit the `CMakeLists.txt` file again, this time to copy the image in your binary directory:

    ```cmake
    FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/one_moving_object.avi"
          DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

    FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/change_of_lighting_conditions.avi"
          DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

    FILE (COPY "${CMAKE_CURRENT_SOURCE_DIR}/two_moving_objects.avi"
          DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ```

    This way it will be easy for `MotionDetection.cxx` to locate the input video files.

# 3. Have you done your homework?

This week we will reply on the knowledge learnt in the 4th lecture of Semester 2, on *Motion Detection and Tracking*. If you don't know what I am talking about, have a look at the slides now.

You are expected to have studied the code in the following Jupyter Notebooks too:

- [https://github.com/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/1-How_to_use_webcam_using_OpenCV.ipynb](https://nbviewer.jupyter.org/github/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/1-How_to_use_webcam_using_OpenCV.ipynb), and
- [https://github.com/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/2-Basic_Background_Subtraction.ipynb](https://nbviewer.jupyter.org/github/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/2-Basic_Background_Subtraction.ipynb).

You must read and understand both the text in English and the code.

# 4. Preamble

In  `MotionDetection.cxx`, add the preamble to identify the file: which file? what for? when? who? anything missing/any bug?

```cpp
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
```

# 5. Add the header files

# 6. Add the `namespaces`

I personally use `std` and `cv`.

# 7. Add an empty `main` function

Make sure you take care of the command line with `(int argc, char** argv)`.

# 8. Compile

At this stage you have an empty program, I know. However, I would still do it. The compilation is to test that `CMakeLists.txt` is working well and that I can start the fun part, coding.

# 9. Adapt the code from the Jupyter Notebook

We can use the code from [https://github.com/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/2-Basic_Background_Subtraction.ipynb](https://nbviewer.jupyter.org/github/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/2-Basic_Background_Subtraction.ipynb) as a starting point.

- Copy the two functions to your own program:
    - `Mat cleanBinaryImage(const Mat& aBinaryImage, int elementSize = 5)`, and
    - `Mat getForegroundMask(const Mat& aBackground, const Mat& aNewFrame, int aThreshold)`,
- In the `main` function, you need most of the rest of the code:
    - Open the `VideoCapture`,
    - Create the windows (optional),
    - Create the `threshold` and the slider (called `trackbar` in OpenCV),
    - Declare the `background` variable,
    - Add the event loop,
    - Destroy the windows (optional), and
    - Release the VideoCapture (optional).
- Compile and run:
    - The program is using the webcam by default,
    - Press `B` to pick up a background,
    - Press `ESC` or `Q` to quit.

# 10. Load the video from a file

The program needs to know:

1. the name of the input video file, and
2. the name of the output video file.

You must perform this action at the beginning of your `main` function. You have two options. The nice one and the ugly one:

- Use the arguments of the command line, or
- Hard code the file names,
    - it is not as elegant,
    - you'll need to re-compile when changing the file names, but then
    - the point of the lab is not parsing the command line arguments.

To open a video file, use the appropriate `VideoCapture` constructor. See [here](https://docs.opencv.org/3.4/d8/dfe/classcv_1_1VideoCapture.html#a949d90b766ba42a6a93fe23a67785951) for the documentation. For example, we can use

```cpp
VideoCapture video_input("one_moving_object.avi");
```

or

```cpp
VideoCapture video_input(argv[1]);
```

- Compile and run.
- You'll see that the video plays very quickly.
    - Once all the frames from the input video file are read, `video_input >> frame;` will produce an empty frame, which will end the event loop.
    - To loop through the video, replace:

    ```cpp
    video_input.release(); // We are now done with the camera, stop it
    throw runtime_error("OpenCV cannot grab a new frame from the camera, the program will terminate");
    ```

    with

    ```cpp
    video_input.set(CAP_PROP_POS_FRAMES, 0);
    ```

- Compile and run.

# 11. Save a video file

We saw how to do that in [https://github.com/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/1-How_to_use_webcam_using_OpenCV.ipynb](https://nbviewer.jupyter.org/github/effepivi/ICP3038/blob/master/Lectures/11-motion-tracking/notebooks/1-How_to_use_webcam_using_OpenCV.ipynb). Before the event loop,

- You need a `VideoWriter` (see Step `[13]` of the notebook),
- For a `VideoWriter`, you need to know
    - the frame size (Step `[11]`)
    - the frame rate (Step `[12]`)
- To add a new image (called frame) in your output video, use `operator<<` (just like a `cout`), e.g.
    - see `video << frame;` in Step `[14]`.
    - We could save the detected foreground, e.g. `clean` in the event loop. Just use `video << clean;`.
- Compile and run.

# 12. Choose an appropriate background

In all the videos I provided, there is no motion in the first few frames, i.e. we can use the first frame as the background.
Don't forget to remove the `if (key == 'b')` statement in the event loop. Also, don't forget how the frame was processed to produce the background:
- RGB to greyscale;
- blur;
- UCHAR to float32.

Now, compile and run the code. If you are unhappy with the foreground mask (e.g. presence of holes or tiny islands), you can increase the size of your structuring element (mathematical morphology) and/or the size of your median filters.

# 13. Locating moving objects

Moving objects, will be white in the `foreground_mask`.
We can easily find them using OpenCV's `findContours` function. See [here](https://docs.opencv.org/master/df/d0d/tutorial_find_contours.html) for the corresponding documentation.

- Use `findContours` to find the contours in `foreground_mask`.
- Use `drawContours` to draw the contours in `clean`.

# 14. Ignoring "objects" that are too small

Some of the detected objects are far too small. We can compute the area (number of pixels). For each contour (i.e. detected objects), compute its area using `contourArea`. See [here](https://docs.opencv.org/master/d3/dc0/group__imgproc__shape.html#ga2c759ed9f497d4a618048a2f56dc97f1) for the documentation.
If the area is large enough, draw the contour, if not ignore it. To define how big "large enough" is, define your own threshold. You may adjust it by hand (hard coded), or with a slider.

# 15. Updating the background

Bonus point: After all, the first frame as the background may not have been so clever. Something started to move, and the static object from the first frame was detected as something that moved. To further improve your code, update the background so that static objects are not detected.

# 16. Compute the speed of the car

Bonus point: Compute the speed of each detected object.
