
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  CMake file for the library.
#
#  Sources:
#  https://stackoverflow.com/questions/5311515/gcc-fpic-option
#
################################################################################

# We are compling usul.
add_compile_definitions ( COMPILING_USUL )

# We want position independent code.
set ( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  ./Usul/Base/Referenced.cpp
  ./Usul/Plugins/Library.cpp
  ./Usul/Plugins/Manager.cpp
  ./Usul/System/LastError.cpp
)

# Make the library using the source files.
add_library ( ${PROJECT_NAME} SHARED ${SOURCE_FILES} )

# Tell cmake that other projects that use this one will need
# the header files from USUL_INC_DIR.
target_include_directories ( ${PROJECT_NAME} INTERFACE ${USUL_INC_DIR} )

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${PROJECT_NAME} PROPERTIES
  VERSION ${USUL_VERSION_STRING}
  SOVERSION ${USUL_VERSION_MAJOR}
)
