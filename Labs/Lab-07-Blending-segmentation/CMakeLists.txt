cmake_minimum_required(VERSION 3.10)

PROJECT (ICP3038-img-class VERSION 0.2)


# Use C++ 11
set(CMAKE_CXX_STANDARD 11) # C++11
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++11 is required (i.e. not optional)
set(CMAKE_CXX_EXTENSIONS OFF) # without compiler extensions like gnu++11

# Find the libJPEG
FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
    add_definitions(-DHAS_LIBJPEG)
ELSE(JPEG_FOUND)
    MESSAGE(WARNING "JPEG not found.")
ENDIF(JPEG_FOUND)


# Build GoogleTest
INCLUDE(cmake/External_GTest.cmake)

# Enable unit testing
enable_testing()

# Compilation
ADD_EXECUTABLE(test-constructors
    include/Image.h
    src/Image.cxx
    src/test-constructors.cxx)

# Add dependency
ADD_DEPENDENCIES(test-constructors googletest)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-constructors PUBLIC include)
target_include_directories(test-constructors PUBLIC ${GTEST_INCLUDE_DIRS})

IF(JPEG_FOUND)
    target_include_directories(test-constructors PUBLIC ${JPEG_INCLUDE_DIR})
ENDIF(JPEG_FOUND)

# Add linkage
target_link_directories(test-constructors PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-constructors ${GTEST_LIBRARIES} ${JPEG_LIBRARY})

# Add the unit test
add_test (Constructors test-constructors)


# Compilation
ADD_EXECUTABLE(test-operators
    include/Image.h
    src/Image.cxx
    src/test-operators.cxx)

# Add dependency
ADD_DEPENDENCIES(test-operators googletest)

# Add include directories
TARGET_INCLUDE_DIRECTORIES(test-operators PUBLIC include)
target_include_directories(test-operators PUBLIC ${GTEST_INCLUDE_DIRS})

IF(JPEG_FOUND)
    target_include_directories(test-operators PUBLIC ${JPEG_INCLUDE_DIR})
ENDIF(JPEG_FOUND)

# Add linkage
target_link_directories(test-operators PUBLIC ${GTEST_LIBS_DIR})
target_link_libraries(test-operators ${GTEST_LIBRARIES} ${JPEG_LIBRARY})

# Add the unit test
add_test (Operators test-operators)


# The documentation build is an option. Set it to ON by default
option(BUILD_DOC "Build documentation" ON)

# Check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)

    SET (PROJECT_NAME ICP3038-img-class)
    SET (PROJECT_DESCRIPTION "An Image class used in ICP3038 at Bangor University")
    
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # Configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Add a custom target
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

