
################################################################################
#
#  Copyright (c) 2019, Perry L Miller IV
#  All rights reserved.
#  MIT License: https://opensource.org/licenses/mit-license.html
#
################################################################################

################################################################################
#
#  Test script.
#
################################################################################

# Exit immediately if one of the following commands does not return zero.
set -e

# Echo all the commands.
set -x

rm -rf build
mkdir build
cd build

cmake .. \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE="Release" \
  -DUSUL_BUILD_TESTS=ON \
  -DUSUL_ENABLE_CODE_COVERAGE=OFF
cmake --build .

tests/usul_test --abort --use-colour=yes --durations=no

cd ..

rm -rf build
mkdir build
cd build

cmake .. \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE="Debug" \
  -DUSUL_BUILD_TESTS=ON \
  -DUSUL_ENABLE_CODE_COVERAGE=ON
cmake --build .

tests/usul_test_d --abort --use-colour=yes --durations=no

cd ..
gcovr
