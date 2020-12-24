
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

# Does the user want to generate code coverage?
option ( USUL_ENABLE_CODE_COVERAGE
  "Generate test code coverage in supported configurations" OFF )
if ( USUL_ENABLE_CODE_COVERAGE )
  if ( UNIX ) # True for Linux, Mac, and Cygwin.
    message ( "   -- Generating test code coverage data" )
    add_compile_options ( -fprofile-arcs -ftest-coverage )
    if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" )
      add_link_options ( --coverage )
    else() # GCC
      link_libraries ( gcov )
    endif()
  else()
    message ( WARNING "Test code coverage data not supported with current compiler" )
  endif()
endif()

# Need to include files from this directory.
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  ./Helpers/Classes.cpp
  ./Helpers/Instances.cpp
  ./Usul/Algorithms/Revolution.cpp
  ./Usul/Base/Referenced.cpp
  ./Usul/Bits/Bits.cpp
  ./Usul/Errors/Check.cpp
  ./Usul/File/Buffer.cpp
  ./Usul/Jobs/Manager.cpp
  ./Usul/Math/Base.cpp
  ./Usul/Math/Box.cpp
  ./Usul/Math/CloseFloat.cpp
  ./Usul/Math/Functions.cpp
  ./Usul/Math/Line2.cpp
  ./Usul/Math/Line3.cpp
  ./Usul/Math/Matrix44.cpp
  ./Usul/Math/Random.cpp
  ./Usul/Math/Sequence.cpp
  ./Usul/Math/Three.cpp
  ./Usul/Math/Vector2.cpp
  ./Usul/Math/Vector3.cpp
  ./Usul/Math/Vector4.cpp
  ./Usul/Strings/Format.cpp
  ./Usul/Pointers/Functions.cpp
  ./Usul/Pointers/Intrusive.cpp
  ./Usul/Pointers/QueryPointer.cpp
  ./Usul/Pointers/SmartPointer.cpp
  ./Usul/Properties/Map.cpp
  ./Usul/Tools/Cast.cpp
  ./Usul/Tools/NoThrow.cpp
  ./Usul/Tools/ScopedCall.cpp
  ./Usul/Main.cpp
  ./Usul/Version.cpp
)

# Add these files if the standard is new enough.
if ( ${CMAKE_CXX_STANDARD} VERSION_GREATER_EQUAL "17" )
  set (SOURCE_FILES ${SOURCE_FILES} ./Usul/Tools/Any.cpp )
endif()

# Make an executable.
add_executable ( ${PROJECT_NAME}_test ${SOURCE_FILES} )
add_test (
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}_test --abort --use-colour=yes --durations=no
)

if ( WIN32 AND BUILD_SHARED_LIBS )
  add_custom_command ( TARGET ${PROJECT_NAME}_test
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}_test>
  )
endif()

# Append a "d" to the file name if this is a debug build.
# Unlike with the library files, this does not happen automatically.
if ( ( DEFINED CMAKE_DEBUG_POSTFIX ) AND ( NOT ${CMAKE_DEBUG_POSTFIX} STREQUAL "" ) )
  set_target_properties ( ${PROJECT_NAME}_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX} )
endif()

# Tell cmake we are going to use these libraries.
# It will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_test PRIVATE
  ${PROJECT_NAME}
  ${CMAKE_DL_LIBS}
  Catch2::Catch2
)
