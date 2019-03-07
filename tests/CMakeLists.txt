
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
#  Sources:
#  https://stackoverflow.com/questions/16682606/how-to-resovle-gcov-init-undefined-reference-issue-when-link
#
################################################################################

# Let the user set the include path for Catch2.
set ( CATCH2_INC_DIR $ENV{CATCH2_INC_DIR} CACHE STRING "Include path for Catch2 header file" )

# Does the user want to generate code coverage?
option ( USUL_ENABLE_CODE_COVERAGE
  "Generate test code coverage in supported configurations" OFF )
if ( USUL_ENABLE_CODE_COVERAGE )
  if ( USING_GCC OR USING_CLANG )
    message ( "   -- Generating test code coverage data" )
    add_compile_options ( -fprofile-arcs -ftest-coverage )
    if ( USING_GCC )
      link_libraries ( gcov )
    elseif ( USING_CLANG )
      add_link_options ( --coverage )
    endif()
  else()
    message ( "!! Test code coverage data not supported with current compiler" )
  endif()
endif()

# Add the include directory for catch.
include_directories ( ${CATCH2_INC_DIR} )

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
  ./Usul/Tools/ScopedCall.cpp
  ./Usul/Main.cpp
  ./Usul/Version.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME}_test ${SOURCE_FILES} )

# Append a "d" to the file name if this is a debug build.
# Unlike with the library files, this does not happen automatically.
set_target_properties ( ${PROJECT_NAME}_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} )

# Tell cmake we are going to use these libraries.
# It will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME} ${CMAKE_DL_LIBS} )
