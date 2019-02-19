### Usul

This is a modernization of the low-level utility code found
[here](https://github.com/perryiv/cadkit/tree/master/Usul),
which is itself just an unaltered copy of
[this code](https://sourceforge.net/p/cadkit/code/HEAD/tree/trunk/Usul/).
It also takes into consideration the first attempt at a re-write found
[here](https://github.com/perryiv/haf/tree/master/Source/Usul).

### Dependencies

As of now Usul is a library of header files with zero dependencies.
If you're just going to use Usul in your project then there is nothing to do.

However, if you're going to build the test programs then you will need:

- [CMake](https://cmake.org/) to generate the build files, and
- [Catch2](https://github.com/catchorg/Catch2) to compile against.

Download the Catch2 repository and set one environment variable. In a `tcsh`
it will look like this:

    setenv CATCH2_INC_DIR Catch2/single_include/catch2

Adjust accordingly for other platforms and shells.

### Testing

To configure, compile, and test, do this:

    cd usul
    mkdir build
    cd build
    cmake ..
    cmake --build .
    cd bin
    ./usul_math_test

### Optional

If you have a recent version of [Node.js](https://nodejs.org/) and `npm`
you can do this:

    cd usul
    npm install
    npm run config
    npm run build
    npm run test

If you want to automatically recompile when the source code changes, so this:

    npm run watch
