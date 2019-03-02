
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the Usul test program.
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

# Add the include directory for catch.
include_directories ( $ENV{CATCH2_INC_DIR} )

# Need to include files from this directory.
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  ./Helpers/Classes.cpp
  ./Helpers/Instances.cpp
  ./Usul/Base/Referenced.cpp
  ./Usul/Errors/Check.cpp
  ./Usul/Math/Base.cpp
  ./Usul/Math/CloseFloat.cpp
  ./Usul/Math/Functions.cpp
  ./Usul/Math/Vector2.cpp
  ./Usul/Math/Vector3.cpp
  ./Usul/Math/Vector4.cpp
  ./Usul/Strings/Format.cpp
  ./Usul/Pointers/Functions.cpp
  ./Usul/Pointers/Intrusive.cpp
  ./Usul/Pointers/QueryPointer.cpp
  ./Usul/Pointers/SmartPointer.cpp
  ./Usul/Tools/Cast.cpp
  ./Usul/Tools/NoThrow.cpp
  ./Usul/Main.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME}_test ${SOURCE_FILES} )

# Tell cmake we are going to use this library.
# It will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_test PRIVATE usul )
