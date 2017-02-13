CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(ICP3038--Lab8--VideosIn2OpenCV)

# Add where OpenCV might be installed (look in D: first, then in C:)
IF (WIN32)
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:\\opencv\\build")
    SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\opencv\\build")
ENDIF (WIN32)


# Find OpenCV
FIND_PACKAGE(OpenCV REQUIRED)

# Add OpenCV's header path
INCLUDE_DIRECTORIES (${OpenCV_INCLUDE_DIRS})

# Add the libraries for OpenCV
SET (requiredLibs ${requiredLibs} ${OpenCV_LIBS})


# The executable programs
ADD_EXECUTABLE (videoFromFile    videoFromFile.cxx)
#ADD_EXECUTABLE (videoFromCamera  videoFromCamera.cxx)
#ADD_EXECUTABLE (Pyramids         Pyramids.cpp)


# Add OpenCV libraries to each executable programs
TARGET_LINK_LIBRARIES (videoFromFile    ${requiredLibs})
#TARGET_LINK_LIBRARIES (videoFromCamera  ${requiredLibs})
#TARGET_LINK_LIBRARIES (Pyramids         ${requiredLibs})


# If windows is used, copy the dlls into the project directory
IF (WIN32)
	
    IF (EXISTS "${OpenCV_DIR}/x64/vc14/bin/opencv_ffmpeg320_64.dll")
        FILE (COPY        "${OpenCV_DIR}/x64/vc14/bin/opencv_ffmpeg320_64.dll"
              DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ELSE ()
	    MESSAGE (WARNING "opencv_ffmpeg320_64.dll is not in ${OpenCV_DIR}/x64/vc14/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
    ENDIF ()

    IF (EXISTS "${OpenCV_DIR}/x64/vc14/bin/opencv_world320.dll")
        FILE (COPY        "${OpenCV_DIR}/x64/vc14/bin/opencv_world320.dll"
              DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ELSE ()
	    MESSAGE (WARNING "opencv_world320.dll is not in ${OpenCV_DIR}/x64/vc14/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
    ENDIF ()
	
    IF (EXISTS "${OpenCV_DIR}/x64/vc14/bin/opencv_world320d.dll")
        FILE (COPY        "${OpenCV_DIR}/x64/vc14/bin/opencv_world320d.dll"
              DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")
    ELSE ()
        MESSAGE (WARNING "opencv_world320d.dll is not in ${OpenCV_DIR}/x64/vc14/bin/, you have to make sure is it in the PATH or to copy it manually in your project binary directory")
    ENDIF ()
    
ENDIF (WIN32)