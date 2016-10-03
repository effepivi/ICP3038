project(example1)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})

add_executable(example1 include/Window.h src/Window.cpp src/main.cpp)
target_link_libraries(example1 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
