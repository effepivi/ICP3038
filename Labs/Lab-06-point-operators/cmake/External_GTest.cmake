cmake_minimum_required(VERSION 2.8.2)

SET (GTEST_URL_REPOSITORY "https://github.com/google/googletest/archive/master.zip" CACHE  STRING "Google Test repository")
SET (GTEST_GIT_REPOSITORY "https://github.com/google/googletest.git" CACHE  STRING "Google Test repository")
SET (GTEST_GIT_TAG "0fe96607d85cf3a25ac40da369db62bbee2939a5" CACHE STRING "Tag or hash for GTtest git repo")

if(POLICY CMP0048)
    cmake_policy (SET CMP0048 NEW)
    PROJECT(googletest-dow VERSION 1.0.0)
else ()
    PROJECT(googletest-dow)
endif()


find_package(Threads REQUIRED)

include(ExternalProject)

set(GTEST_DISABLE_PTHREADS ON)
set(GTEST_FORCE_SHARED_CRT ON)

get_filename_component(GTEST_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}" REALPATH)
SET (GTEST_INSTALL_DIR ${GTEST_INSTALL_DIR}/third_party)

FIND_PACKAGE(Git)
IF (GIT_FOUND)

    ExternalProject_Add(googletest
        GIT_REPOSITORY ${GTEST_GIT_REPOSITORY}
        GIT_TAG ${GTEST_GIT_TAG}
	INSTALL_DIR ${GTEST_INSTALL_DIR}
        CMAKE_ARGS
            ${LOCAL_CMAKE_BUILD_OPTIONS}
            -DBUILD_UTILS:BOOL=OFF
            -Dgtest_force_shared_crt=${GTEST_FORCE_SHARED_CRT}
            -Dgtest_disable_pthreads=${GTEST_DISABLE_PTHREADS}
            -DBUILD_GTEST=ON
            -DBUILD_GMOCK=OFF
            -DBUILD_UTILS=OFF
            -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        # Disable install step
	#INSTALL_COMMAND ""
    )
ELSE (GIT_FOUND)
    ExternalProject_Add(googletest
        URL ${GTEST_URL_REPOSITORY}
	INSTALL_DIR ${GTEST_INSTALL_DIR}
        CMAKE_ARGS
            ${LOCAL_CMAKE_BUILD_OPTIONS}
            -DBUILD_UTILS:BOOL=OFF
            -Dgtest_force_shared_crt=${GTEST_FORCE_SHARED_CRT}
            -Dgtest_disable_pthreads=${GTEST_DISABLE_PTHREADS}
            -DBUILD_GTEST=ON
            -DBUILD_GMOCK=OFF
            -DBUILD_UTILS=OFF
            -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}

        PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
        # Disable install step
	#INSTALL_COMMAND ""
    )
ENDIF (GIT_FOUND)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${GTEST_INSTALL_DIR}/include)

IF (UNIX)
    IF (APPLE)
        set (GTEST_LIBS_DIR "${GTEST_INSTALL_DIR}/lib")
    ELSE (APPLE)
        set (GTEST_LIBS_DIR "${GTEST_INSTALL_DIR}/lib64")
    ENDIF (APPLE)
ELSE (UNIX)
    set (GTEST_LIBS_DIR "${GTEST_INSTALL_DIR}/lib")
ENDIF (UNIX)


# Specify MainTest's link libraries
IF (UNIX)
    list(APPEND GTEST_LIBRARIES gtest gtest_main)
ELSE (UNIX)
    SET (GTEST_LIBRARIES
      debug gtestd
      optimized gtest
      debug gtest_maind
      optimized gtest_main
    )
ENDIF (UNIX)
