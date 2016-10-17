cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(Chapter4)

set (CMAKE_CXX_STANDARD 11)

add_executable(example01 src/example1.h src/example1.cpp)
add_executable(example02                src/example2.cpp)
add_executable(example03                src/example3.cpp)
add_executable(example04 src/example4.h src/example4.cpp)
add_executable(example05 src/example5.h src/example5.cpp)
add_executable(example06 
	src/example6/Circle.h
	src/example6/Circle.cpp
	src/example6/Rectangle.h
	src/example6/Rectangle.cpp
	src/example6/Square.h
	src/example6/Square.cpp
	src/example6/main.cpp)
add_executable(example07 
	src/example7/Circle.h
	src/example7/Circle.cpp
	src/example7/Rectangle.h
	src/example7/Rectangle.cpp
	src/example7/Shape.h
	src/example7/Shape.cpp
	src/example7/Square.h
	src/example7/Square.cpp
	src/example7/main.cpp)
add_executable(example08  src/example8.h  src/example8.cpp)
add_executable(example09  src/example9.h  src/example9.cpp)
add_executable(example10  src/example10.h src/example10.cpp)
add_executable(example11  src/example11.h src/example11.cpp)
add_executable(example12a                 src/example12a.cpp)
add_executable(example12b                 src/example12b.cpp)
add_executable(example13a                 src/example13a.cpp)
add_executable(example13b                 src/example13b.cpp)
add_executable(example14                  src/example14.cpp)
add_executable(example15                  src/example15.cpp)
add_executable(example16a                 src/example16a.cpp)
add_executable(example16b                 src/example16b.cpp)
add_executable(example17                  src/example17.cpp)
add_executable(example18                  src/example18.cpp)
add_executable(example19                  src/example19.cpp)
add_executable(example20                  src/example20.cpp)
add_executable(example21                  src/example21.cpp)
add_executable(example22                  src/example22.cpp)
