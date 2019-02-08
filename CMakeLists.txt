
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

# We're using conan.
# https://docs.conan.io/en/latest/getting_started.html
include ( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )

# More efficient command-line for compiler and linker.
# With TARGETS here I need "CONAN_PKG::Catch2" below.
conan_basic_setup ( TARGETS )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  tests/Usul/Math/Base.cpp
  tests/Usul/Math/CloseFloat.cpp
  tests/Usul/Math/Functions.cpp
  tests/Usul/Math/Vector2.cpp
  tests/Usul/Math/Vector3.cpp
  tests/Usul/Main.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME} ${SOURCE_FILES} )

# We're going to use this library.
# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME} PRIVATE usul_math CONAN_PKG::Catch2 )

# Define a variable that points to the top-level include directory.
set ( USUL_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# Also process the CMakeLists.txt found in this directory.
add_subdirectory ( src/Usul/Math )
