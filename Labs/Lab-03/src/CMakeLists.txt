# Wehre the header files are (in relation to ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../include)
message(STATUS "The header files are located in ${CMAKE_CURRENT_SOURCE_DIR}/../include")

add_executable(Task1 TestVector.cpp)
add_executable(Task2 TestUtils.cpp ../include/utils.h)
