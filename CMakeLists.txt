
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  Following this tutorial ...
#  https://vicrucann.github.io/tutorials/cmake-qt-osg-1/
#
################################################################################

# https://doc.qt.io/qt-5/cmake-manual.html
cmake_minimum_required ( VERSION 3.1.0 )

# The name of this project.
project ( usul_test )

# Use modern C++
# https://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
set ( CMAKE_CXX_STANDARD 11 )

# Look in the current directory for include files.
set ( CMAKE_INCLUDE_CURRENT_DIR ON )

# We're using conan.
# https://docs.conan.io/en/latest/getting_started.html
include ( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
conan_basic_setup()

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  tests/Math.cpp
  tests/Main.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME} ${SOURCE_FILES} )
