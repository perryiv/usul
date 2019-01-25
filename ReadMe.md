### Usul

This is a modernization of the low-level utility code found
[here](https://github.com/perryiv/cadkit/tree/master/Usul),
which is itself just an unaltered copy of
[this code](https://sourceforge.net/p/cadkit/code/HEAD/tree/trunk/Usul/).

It also takes into consideration the first attempt at a re-write found
[here](https://github.com/perryiv/haf/tree/master/Source/Usul).

### Do This first

If you don't already have [Conan](https://conan.io/) get it here:

    https://conan.io/

Then do this one time:

    conan remote add catchorg https://api.bintray.com/conan/catchorg/Catch2

### Building

Do this once, or whenever the conan configuration file changes.

    cd usul
    rm -rf build
    mkdir build
    cd build
    conan install ..

Also do this once, or whenever the CMakeLists.txt file changes.

    cd usul/build
    cmake ..

Assuming you have done the above, to compile just do this:

    make

As of now the only thing that gets compiled is the test program.

### Testing

Assuming you have already done the above build steps you should be able to run the tests like this:

    cd usul/build/bin
    ./usul_test

### Developing

If you ...
1. Have the [watch](https://www.npmjs.com/package/watch) command or similar, and
2. Are editing the source code, and
3. You want to automatically rebuild and test, then

do this:

    cd usul/build
    watch 'clear && make && ./bin/usul_test' ../Usul/ ../tests/

Alternatively, if you have a recent version of
[Node.js](https://nodejs.org/) and `npm` ...

do this:

    cd usul
    npm run rebuild
    npm run watch
