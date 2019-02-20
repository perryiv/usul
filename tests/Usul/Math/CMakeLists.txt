
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul math test program.
#
################################################################################

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  ./Base.cpp
  ./CloseFloat.cpp
  ./Functions.cpp
  ./Vector2.cpp
  ./Vector3.cpp
  ./Vector4.cpp
  ./Main.cpp
)

# Make an executable.
add_executable ( ${PROJECT_NAME}_math_test ${SOURCE_FILES} )

# We're going to use this library.
# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( ${PROJECT_NAME}_math_test PRIVATE usul_math )
