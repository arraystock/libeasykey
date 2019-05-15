# CMakeLists.txt
# Copyright (c) 2019 Jonathan Archer

# Minimum version allowed to be used.
cmake_minimum_required(VERSION 2.9)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

# Project name.
project(easykey)

# Specify our output directory.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

# Glob all our source files into a variable.
file(GLOB easykey_source "${PROJECT_SOURCE_DIR}/source/*.c")

# Build our library.
ADD_LIBRARY(easykey STATIC "${easykey_source}")

# Specify include directories.
target_include_directories(easykey PRIVATE "${PROJECT_SOURCE_DIR}/include")