# SPDX-License-Identifier: BSD-3-Clause
cmake_minimum_required(VERSION 4.1.2)

# Project info
set(PROJECT_NAME ctsa)
project(${PROJECT_NAME} CXX C)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -O2")
set(CMAKE_C_STANDARD 23)

# Find JNI
find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

# cleanup prefix lib for Unix-like OSes
set(CMAKE_SHARED_LIBRARY_PREFIX)

# collect all ctsa source files
file(GLOB CTSA_SOURCES src/*.c)

add_library(ctsa SHARED library.c ${CTSA_SOURCES})
target_link_libraries(ctsa ${JNI_LIBRARIES})
