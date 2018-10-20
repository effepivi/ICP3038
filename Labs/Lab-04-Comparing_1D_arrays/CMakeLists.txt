cmake_minimum_required(VERSION 2.6)

project(Lab4)

include_directories(include)

add_executable(test_my_vector src/test_my_vector.cpp include/MyVector.h src/MyVector.cpp)
