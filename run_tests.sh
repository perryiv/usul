
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

mkdir release
cd release

cmake ../.. \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE="Release" \
  -DUSUL_ENABLE_CODE_COVERAGE=OFF
cmake --build .

./bin/usul_test --abort --use-colour=yes --durations=no

cd ..
mkdir debug
cd debug

cmake ../.. \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE="Debug" \
  -DUSUL_ENABLE_CODE_COVERAGE=ON
cmake --build .

./bin/usul_testd --abort --use-colour=yes --durations=no

cd ../..
gcovr
