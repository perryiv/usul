### Usul

This is a modernization of the low-level utility code found
[here](https://github.com/perryiv/cadkit/tree/master/Usul),
which is itself just an unaltered copy of
[this code](https://sourceforge.net/p/cadkit/code/HEAD/tree/trunk/Usul/).
It also takes into consideration the first attempt at a re-write found
[here](https://github.com/perryiv/haf/tree/master/Source/Usul).

### Dependencies

Many header files can be used without ever compiling the library.
However, if you're going to build the library you will need
[CMake](https://cmake.org/).
Building the test program requires
[Catch2](https://github.com/catchorg/Catch2).

### Testing

To configure, compile, and test, do this:

    cd usul
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ./bin/usul_test

### Errors

When this library encounters an error inside a destructor it writes information
to stderr. When it encounters an error (just about) anywhere else it throws a
standard exception.

This seems to be a good balance between flexibility when handling errors,
and keeping the various source files decoupled, especially the header-only
source files.
