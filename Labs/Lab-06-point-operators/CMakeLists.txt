cmake_minimum_required(VERSION 3.10)

PROJECT (ICP3038-img-class VERSION 0.1)

ADD_EXECUTABLE(test-constructors
    include/Image.h
    src/Image.cxx
    src/test-constructors.cxx)

TARGET_INCLUDE_DIRECTORIES(test-constructors PUBLIC include)
