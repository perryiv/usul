
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul tools library.
#
################################################################################

# The name of this library is usul_tools and it's a header-file-only library.
add_library ( usul_tools INTERFACE )

# Tell cmake that to use this library you need to include the directory
# defined in USUL_INC_DIR, which was set in our top-level CMakeLists.txt file.
target_include_directories ( usul_tools INTERFACE ${USUL_INC_DIR} )
