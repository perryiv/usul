
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
# Hey CMake, here is a library and all the stuff you need to know about it.
add_library ( ${PROJECT_NAME} SHARED ${SOURCE_FILES} )

# Tell cmake that other projects that use this one will need
# the header files from USUL_INC_DIR.
target_include_directories ( ${PROJECT_NAME} PUBLIC ${USUL_INC_DIR} )

# Bake the version into the file name and create symlinks if appropriate.
set_target_properties ( ${PROJECT_NAME} PROPERTIES
  VERSION ${USUL_VERSION_STRING}
  SOVERSION ${USUL_VERSION_MAJOR}
)

# Tell cmake how to install the headers and binaries if the user types
# "make install" or compiles the Visual C++ INSTALL project. The default
# directory prefix is /usr/local or "C:/Program Files", and can be changed
# on the command line with -DCMAKE_INSTALL_PREFIX=/some/path.
install ( TARGETS ${PROJECT_NAME} DESTINATION lib )
install ( DIRECTORY ${USUL_INC_DIR}/Usul DESTINATION include FILES_MATCHING PATTERN "*.h" )
