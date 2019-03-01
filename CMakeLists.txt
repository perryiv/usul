
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
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
#  https://stackoverflow.com/questions/2368811/how-to-set-warning-level-in-cmake/50882216
#  https://docs.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=vs-2017
#  https://softwareengineering.stackexchange.com/questions/88532/whether-to-use-pedantic-flag-in-g-or-not
#  https://stackoverflow.com/questions/4001736/whats-up-with-the-thousands-of-warnings-in-standard-headers-in-msvc-wall
#
################################################################################

# We use the add_compile_definitions command.
# https://cmake.org/cmake/help/v3.12/release/3.12.html
cmake_minimum_required ( VERSION 3.12.0 )

# The name of this project.
project ( usul )

# Use this C++ standard unless the user specifies otherwise with:
# cmake path/to/source/dir -DCMAKE_CXX_STANDARD=14
if ( NOT DEFINED CMAKE_CXX_STANDARD )
  set ( CMAKE_CXX_STANDARD 17 )
endif()

# Turn off compiler-specific extensions by default.
if ( NOT DEFINED CMAKE_CXX_EXTENSIONS )
  set ( CMAKE_CXX_EXTENSIONS OFF )
endif()

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

# Does the user want an atomic reference counter?
option ( USUL_USE_ATOMIC_REFERENCE_COUNTER
  "Use std::atomic for the reference counter in Usul/Base/Referenced.cpp" ON )

# Let the user change the plugin extension.
set ( USUL_PLUGIN_EXTENSION "plug" CACHE STRING "File extension for plugins" )

# Now that we have all the configuration options we can write the file.
configure_file (
  ${CMAKE_CURRENT_SOURCE_DIR}/config/Config.h.in
  ${USUL_INC_DIR}/Usul/Config.h
)

# Does the user want all warnings?
option ( USUL_ENABLE_ALL_WARNINGS "Enable all warnings" ON )
if ( USUL_ENABLE_ALL_WARNINGS )
  if ( MSVC )
    add_compile_options ( /W4 )
  else()
    add_compile_options ( -Wall -Wextra -pedantic -pedantic-errors )
  endif()
endif()

# Does the user want to treat warnings the same as errors?
option ( USUL_TREAT_WARNINGS_LIKE_ERRORS "Treat warnings like errors" ON )
if ( USUL_TREAT_WARNINGS_LIKE_ERRORS )
  if ( MSVC )
    add_compile_options ( /WX )
  else()
    add_compile_options ( -Werror )
  endif()
endif()

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# Everybody in the subdirectories will need to include files from here.
include_directories ( ${USUL_INC_DIR} )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( source )
add_subdirectory ( tests )
