
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul strings library.
#
################################################################################

# The name of this library is usul_strings and it's a header-file-only library.
add_library ( usul_strings INTERFACE )

# Tell cmake that to use this library you need to include the directory
# defined in USUL_INC_DIR, which was set in our top-level CMakeLists.txt file.
target_include_directories ( usul_strings INTERFACE ${USUL_INC_DIR} )
