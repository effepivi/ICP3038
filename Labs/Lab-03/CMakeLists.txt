cmake_minimum_required(VERSION 2.6)

project(ICP3038--Lab03)

include_directories(include)

add_executable(Task1 src/TestVector.cpp)
add_executable(Task2 src/TestUtils.cpp include/Utils.h)
