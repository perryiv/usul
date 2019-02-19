
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul test programs.
#
################################################################################

# Make sure this environment variable is set.
if ( NOT DEFINED ENV{CATCH2_INC_DIR} )
  message ( FATAL_ERROR
    "\nEnvironment variable CATCH2_INC_DIR is not set. "
    "\nIt should point to a directory that contains these files:\n"
    "https://github.com/catchorg/Catch2/tree/master/single_include/catch2"
  )
endif()

# For debug builds we want the _DEBUG preprocessor symbol to be defined.
add_compile_definitions ( $<$<CONFIG:Debug>:_DEBUG> )

# Add the include directory for catch.
include_directories ( $ENV{CATCH2_INC_DIR} )

# Also process the CMakeLists.txt files found in these directories.
add_subdirectory ( Math )
