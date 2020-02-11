# ICP3038 - Computer Vision (CV)
## Lab 10: Background subtraction
### Tutor: Franck Vidal

## Objectives

The aims of today's lab are:

- Processing a video stream, either from a file or the computer's webcam (note the camera as to be static);
- Implement a background subtraction (BS) algorithm:
    - Initialising the background;
    - Updating the background;
    - Generating the foreground mask.

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

##



You can create and process your own videos... Don't forget that you'll have to provide evidence of a working program when submitting your assignment.
<!--For example, Fig.~\ref{fig:screenshot2} shows my fish tank. -->For example you can upload your video files on YouTube<!--, see [https://www.youtube.com/watch?v=RbH2bdrNGbc](https://www.youtube.com/watch?v=RbH2bdrNGbc)-->.
