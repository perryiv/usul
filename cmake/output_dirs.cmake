
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Set default output directories if none are given on command line.
#  Note: On Windows just setting CMAKE_ARCHIVE_OUTPUT_DIRECTORY results
#  %USUL_LIB_DIR%\Debug\<files> instead of %USUL_LIB_DIR%\<files>.
#  So, unfortunately, we have to explicitely set both configurations.
#
################################################################################

# Once for the general case, which works on Linux and Mac.
if ( NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY AND DEFINED ENV{USUL_LIB_DIR} )
  set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY $ENV{USUL_LIB_DIR} )
endif()
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY AND DEFINED ENV{USUL_LIB_DIR} )
  set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY $ENV{USUL_LIB_DIR} )
endif()
if ( NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY AND DEFINED ENV{USUL_BIN_DIR} )
  set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY $ENV{USUL_BIN_DIR} )
endif()

# Once for debug but only on Windows.
if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
  if ( NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG AND DEFINED ENV{USUL_LIB_DIR} )
    set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG $ENV{USUL_LIB_DIR} )
  endif()
  if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG AND DEFINED ENV{USUL_LIB_DIR} )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG $ENV{USUL_LIB_DIR} )
  endif()
  if ( NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG AND DEFINED ENV{USUL_BIN_DIR} )
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG $ENV{USUL_BIN_DIR} )
  endif()
endif()

# Once for release but only on Windows.
if ( MSVC ) # Also true for Intel compiler. Means "looks like Visual C++".
  if ( NOT DEFINED CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE AND DEFINED ENV{USUL_LIB_DIR} )
    set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE $ENV{USUL_LIB_DIR} )
  endif()
  if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE AND DEFINED ENV{USUL_LIB_DIR} )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE $ENV{USUL_LIB_DIR} )
  endif()
  if ( NOT DEFINED CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE AND DEFINED ENV{USUL_BIN_DIR} )
    set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE $ENV{USUL_BIN_DIR} )
  endif()
endif()
