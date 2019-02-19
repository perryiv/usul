
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

# Need to use this version or newer.
cmake_minimum_required ( VERSION 3.1.0 )

# The name of this project.
project ( usul )

# Use modern C++
set ( CMAKE_CXX_STANDARD 11 )

# Define some variables that point to top-level directories.
set ( USUL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# This is where we want output files to go.
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( src/Usul/Math )
add_subdirectory ( tests/Usul/Math )
