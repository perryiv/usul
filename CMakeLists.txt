
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
################################################################################

# Feedback.
message ( "<>\n<> Start ${CMAKE_CURRENT_LIST_FILE}\n<>" )

# Without this version or greater we get this error in Azure Pipelines:
# "make: *** No rule to make target 'test'.  Stop."
cmake_minimum_required ( VERSION 3.15.0 )

# Include these functions.
include ( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/functions.cmake )

# Get the version from this file.
file ( STRINGS ${CMAKE_CURRENT_LIST_DIR}/version.txt PROJECT_VERSION )

# The name of this project.
project ( usul VERSION ${PROJECT_VERSION} LANGUAGES CXX )

# Changes to the version file should trigger a re-configuration.
set_property ( DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/version.txt )

# Default to building usul as a shared library
if ( NOT DEFINED BUILD_SHARED_LIBS )
  set ( BUILD_SHARED_LIBS ON )
endif()

# Use this C++ standard unless the user specifies otherwise with:
# cmake path/to/source/dir -DCMAKE_CXX_STANDARD=14
if ( NOT DEFINED CMAKE_CXX_STANDARD )
  set ( CMAKE_CXX_STANDARD 17 )
endif()

# Turn off compiler-specific extensions by default.
if ( NOT DEFINED CMAKE_CXX_EXTENSIONS )
  set ( CMAKE_CXX_EXTENSIONS OFF )
endif()

# If there is an environment for verbose output then use it.
# Note: Conan is passing -DCMAKE_VERBOSE_MAKEFILE=OFF even though it's set
# to ON in the conanfile.py. This is the only way (that I know of) that it
# can be set to ON.
if ( DEFINED ENV{USE_VERBOSE_MAKEFILE} )
  if ( "$ENV{USE_VERBOSE_MAKEFILE}" STREQUAL "1" )
    set ( CMAKE_VERBOSE_MAKEFILE ON )
  else()
    set ( CMAKE_VERBOSE_MAKEFILE OFF )
  endif()
endif()

# Make VC++ more standard compliant.
if ( MSVC )
  add_compile_options ( /permissive- /Zc:__cplusplus )
endif()

# Make default __attribute__ visibility hidden not public to hide non-exported symbols.
# It is not working on Mac so we disable it.
if ( NOT APPLE )
  set ( CMAKE_CXX_VISIBILITY_PRESET hidden )
  set ( CMAKE_VISIBILITY_INLINES_HIDDEN ON )
endif()

# A convenient variable for telling the compiler to use these header files.
set ( USUL_CONFIG_DIR_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/config )
set ( USUL_CONFIG_DIR_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/config )

# Tell CMake to not skip using rpath.
set ( CMAKE_SKIP_RPATH OFF )

# Tell the linkers to write their output files here.
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Set the version.
configure_file (
  ${USUL_CONFIG_DIR_INPUT}/Version.h.in
  ${USUL_CONFIG_DIR_OUTPUT}/Usul/Version.h )

# Does the user want an atomic reference counter?
option ( USUL_USE_ATOMIC_REFERENCE_COUNTER
  "Use std::atomic for the reference counter in Usul/Base/Referenced.cpp" ON )

# Let the user change the plugin extension.
set ( USUL_PLUGIN_EXTENSION "plug" CACHE STRING "File extension for plugins" )

# Does the user want to ignore these warning?
if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
  option ( USUL_IGNORE_VCPP_WARNING_4251
    "Use a pragma to ignore Visual C++ warning 4251" ON )
  option ( USUL_IGNORE_VCPP_WARNING_4275
    "Use a pragma to ignore Visual C++ warning 4275" ON )
endif()

# Now that we have all the configuration options we can write the file.
configure_file (
  ${USUL_CONFIG_DIR_INPUT}/Config.h.in
  ${USUL_CONFIG_DIR_OUTPUT}/Usul/Config.h )

# Does the user want to be able to install usul
if ( "${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}" )
  set ( ${PROJECT_NAME}_INSTALL_DEFAULT ON )
else()
  set ( ${PROJECT_NAME}_INSTALL_DEFAULT OFF )
endif()
option ( ${PROJECT_NAME}_INSTALL "Able to install ${PROJECT_NAME}" ${${PROJECT_NAME}_INSTALL_DEFAULT} )

if ( ${PROJECT_NAME}_INSTALL )
  # Install generated files wherever the user specified to install things.
  install (
    DIRECTORY ${USUL_CONFIG_DIR_OUTPUT}/Usul
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
  )
endif()

# Does the user want strict warnings?
option ( USUL_ENABLE_STRICT_WARNINGS "Enable strict warnings" ON )
if ( USUL_ENABLE_STRICT_WARNINGS )
  message ( "<> Enabling strict warnings" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /W4 )
  else()
    add_compile_options ( -Wall -Wextra -pedantic -pedantic-errors -Wconversion -Wsign-conversion )
  endif()
endif()

# Does the user want to treat warnings the same as errors?
option ( USUL_TREAT_WARNINGS_LIKE_ERRORS "Treat warnings like errors" ON )
if ( USUL_TREAT_WARNINGS_LIKE_ERRORS )
  message ( "<> Treating warnings like errors" )
  if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
    add_compile_options ( /WX )
  else()
    add_compile_options ( -Werror )
  endif()
endif()

# Does the user want to build the tests?
option ( USUL_BUILD_TESTS "Build the tests" OFF )

# Need Catch2 to build the tests
if ( USUL_BUILD_TESTS )
  find_package ( Catch2 REQUIRED )
  # Fix for problem in Azure pipeline with new conan and CMakeDeps generator.
  if ( TARGET catch2::catch2 )
    add_library ( Catch2::Catch2 ALIAS catch2::catch2 )
    message ( "<> Created alias target Catch2::Catch2" )
  else()
    message ( "<> Using found target Catch2::Catch2" )
  endif()
  print_package ( Catch2 )
endif()

# Set default postfix if none was given on the command line.
if ( NOT DEFINED CMAKE_DEBUG_POSTFIX )
  set ( CMAKE_DEBUG_POSTFIX "_d" )
endif()

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# If this is a debug build, and this option was specified, compile in the
# code to keep track of reference-counted objects.
if ( USUL_REFERENCED_CLASS_DEBUG_KEEP_TRACK )
  add_compile_definitions ( USUL_REFERENCED_CLASS_DEBUG_KEEP_TRACK )
endif()

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( source ) # The library.
if ( USUL_BUILD_TESTS )
  enable_testing()
  add_subdirectory ( tests ) # The tests.
endif()

# Configure how this project gets imported into other cmake projects.
include ( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/export.cmake )

# Feedback.
message ( "<>\n<> End ${CMAKE_CURRENT_LIST_FILE}" )

################################################################################
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
#  http://cmake.3232098.n2.nabble.com/Directing-cmake-to-link-against-shared-object-with-debug-postfix-d-td7595338.html
#  https://stackoverflow.com/questions/16682606/how-to-resovle-gcov-init-undefined-reference-issue-when-link
#  https://cmake.org/cmake/help/v3.13/module/FindOpenSceneGraph.html?highlight=findopenscenegraph
#  https://gitlab.kitware.com/cmake/community/wikis/doc/tutorials/How-to-create-a-ProjectConfig.cmake-file
#
################################################################################
