# CMakeLists.txt
# Copyright (c) 2019 Jonathan Archer

# Minimum version allowed to be used.
cmake_minimum_required(VERSION 3.2)

# Our C flags.
if (UNIX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Og")
endif (UNIX)

# Project name.
project(easykey)

# Version number.
set (easykey_VERSION_MAJOR 0)
set (easykey_VERSION_MINOR 05)

# Configure our header.
configure_file (
  "${PROJECT_SOURCE_DIR}/include/easykey.h.in"
  "${CMAKE_BINARY_DIR}/include/easykey.h"
)

# Specify (and create) our output directory.
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Glob all our source files into a variable.
file(GLOB easykey_source "${PROJECT_SOURCE_DIR}/source/*.c")

# Build our library.
ADD_LIBRARY(easykey STATIC "${easykey_source}")

# Specify include directories.
target_include_directories(easykey PRIVATE "${CMAKE_BINARY_DIR}/include")

# Install rules.
install(TARGETS easykey ARCHIVE DESTINATION /usr/local/lib)
install(DIRECTORY "${CMAKE_BINARY_DIR}/include" DESTINATION /usr/local)