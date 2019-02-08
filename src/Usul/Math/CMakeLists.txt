
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#
################################################################################

################################################################################
#
#  CMake file for the Usul library.
#
################################################################################

# The name of this library is usul_math and it's a header-file-only library.
# INTERFACE has to be all caps, as does SHARED and STATIC.
# Default is a hybrid that is configurable to be either SHARED or STATIC,
# and that is specified on the command line as a cmake argument.
add_library ( usul_math INTERFACE )

# Tell cmake that to use this library you need to include the directory
# defined in USUL_INC_DIR, which was set in our top-level CMakeLists.txt file.
target_include_directories ( usul_math INTERFACE ${USUL_INC_DIR} )

# Add pre-processor definitions here, and use INTERFACE, PRIVATE, or PUBLIC
# like above. We don't need any so this is just here as an example.
# target_compile_definitions ( usul_math )

# Definitions ...

# INTERFACE:
# File and definitions not used to build the library but used by others when
# using the library.

# PRIVATE:
# File and definitions used to build the library but the user of the library
# doesn't need these.

# PUBLIC:
# This is for files and definitions that are both INTERFACE and PRIVATE.
