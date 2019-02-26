
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  Top-level CMake file for the usul project.
#
#  Sources:
#  https://doc.qt.io/qt-5/cmake-manual.html
#  https://vicrucann.github.io/tutorials/cmake-qt-osg-1/
#  https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
#  https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
#
################################################################################

# We use the add_compile_definitions command.
# https://cmake.org/cmake/help/v3.12/release/3.12.html
cmake_minimum_required ( VERSION 3.12.0 )

# The name of this project.
project ( usul )

# Use modern C++
set ( CMAKE_CXX_STANDARD 11 )

# Define some variables that point to top-level directories.
set ( USUL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source )

# This is where we want output files to go.
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Set the version.
set ( USUL_VERSION_MAJOR 0 )
set ( USUL_VERSION_MINOR 1 )
set ( USUL_VERSION_PATCH 0 )
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Version.h.in
  ${USUL_INC_DIR}/Usul/Version.h
)

# Some options and their defaults.
option ( USUL_USE_ATOMIC_REFERENCE_COUNTER
  "Use std::atomic for the reference counter in Usul/Base/Referenced.cpp" ON )
if ( USUL_USE_ATOMIC_REFERENCE_COUNTER )
  add_compile_definitions ( USUL_USE_ATOMIC_REFERENCE_COUNTER )
endif()

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# Everybody in the subdirectories will need to include files from here.
include_directories ( ${USUL_INC_DIR} )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( source )
add_subdirectory ( tests )
