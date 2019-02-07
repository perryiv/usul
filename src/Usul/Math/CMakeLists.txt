
# INTERFACE: File and definitions not used to build the library but used by others when using the library.
# PRIVATE: File and definitions used to build the library but the user of the library doesn't need these.
# PUBLIC: This is for files and definitions that are both INTERFACE and PRIVATE.

# Name of library is usul_math.
# It's a header-file-only library.
# The word INTERFACE has to be all caps.
# Alternatively, could make SHARED, STATIC.
# Default is hybrid that is configurabe to be eithr SHARED or STATIC, specified on the command line as a cmake argument.
add_library ( usul_math INTERFACE )

# Tell cmake that to use this library you need to include the directory defined in USUL_INC_DIR.
target_include_directories ( usul_math INTERFACE ${USUL_INC_DIR} )

# Add pre-processor definitions here, and use INTERFACE, PRIVATE, or PUBLIC like above.
# target_compile_definitions ( usul_math )
