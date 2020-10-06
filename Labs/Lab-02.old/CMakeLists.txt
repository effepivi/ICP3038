cmake_minimum_required(VERSION 2.6)

project(ICP3038--Lab02)

include_directories(include)

add_executable(Task1 src/TestInteger.cpp include/Integer.h src/Integer.cpp)
