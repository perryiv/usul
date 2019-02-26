
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul base library.
#
################################################################################

# The name of this library is usul_base and it's a header-file-only library.
add_library ( usul_base SHARED
  ./Referenced.cpp
  ./Typed.cpp
)

# Tell cmake that to use this library you need to include the directory
# defined in USUL_INC_DIR, which was set in our top-level CMakeLists.txt file.
target_include_directories ( usul_base INTERFACE ${USUL_INC_DIR} )

# We're going to use these libraries.
# CMake will automatically add -I, -L, and -D (etc) appropriately.
target_link_libraries ( usul_base PRIVATE usul_errors )
