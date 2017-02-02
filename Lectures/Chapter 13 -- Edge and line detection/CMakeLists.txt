# Check the version of CMake.
# It needs to be at least 3.1 to enable C++ 11
CMAKE_MINIMUM_REQUIRED (VERSION 3.1.0 FATAL_ERROR)

# Set the name of the project
PROJECT (edgeDetectors)

# Use of C++ 11
# (necessary to use High resolution clock
SET (CMAKE_CXX_STANDARD 11)


# Find OpenCV
FIND_PACKAGE(OpenCV REQUIRED)

# OpenCV has been found
IF (OpenCV_FOUND)
    # Add the libraries for OpenCV
    SET (requiredLibs ${requiredLibs} ${OpenCV_LIBS})
# OpenCV has not been found
ELSE (OpenCV_FOUND)
    # Display an error message
    MESSAGE(FATAL_ERROR "OpenCV not found.")
ENDIF (OpenCV_FOUND)

IF (NOT APPLE AND NOT WIN32)
    SET (requiredLibs ${requiredLibs} flycapture)
ENDIF()


# The executable programs
ADD_EXECUTABLE(sobel_image ../../src/utils.h sobel_image.cxx)



# Add the libraries for OpenCV
TARGET_LINK_LIBRARIES(sobel_image ${requiredLibs} )


