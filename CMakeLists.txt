# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 3.31.6)

# Project info
set(PROJECT_NAME ctsa)
project(${PROJECT_NAME} CXX C)

set(CMAKE_C_FLAGS_RELEASE "-O2")
set(CMAKE_C_STANDARD 23)

# Find JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# Cleanup prefix lib for Unix-like OSes
set(CMAKE_SHARED_LIBRARY_PREFIX)

# Collect all ctsa source files
file(GLOB CTSA_SOURCES src/*.c)
file(GLOB CTSA_HEADERS src/*.h)

add_library(ctsa SHARED library.c library.h ${CTSA_SOURCES} ${CTSA_HEADERS})
target_link_libraries(ctsa PRIVATE ${JNI_LIBRARIES})

# Platform extensions
if(WIN32)
    set_target_properties(ctsa PROPERTIES SUFFIX ".dll")
elseif(APPLE)
    set_target_properties(ctsa PROPERTIES SUFFIX ".dylib")
else()
    set_target_properties(ctsa PROPERTIES SUFFIX ".so")
endif()
