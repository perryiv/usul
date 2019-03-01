
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
################################################################################

# We are compling usul.
add_compile_definitions ( COMPILING_USUL )

# Define a variable that holds all the source files.
set ( SOURCE_FILES
  ./Usul/Base/Referenced.cpp
)

# Make the add_library using the source files.
add_library ( ${PROJECT_NAME} SHARED ${SOURCE_FILES} )

# Tell cmake that other projects that use this one will need
# the header files from USUL_INC_DIR.
target_include_directories ( ${PROJECT_NAME} INTERFACE ${USUL_INC_DIR} )
