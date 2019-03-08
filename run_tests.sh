
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
  -DUSUL_ENABLE_CODE_COVERAGE=OFF
cmake --build .

${USUL_BIN_DIR}/usul_test --abort --use-colour=yes --durations=no

cd ..

rm -rf build
mkdir build
cd build

cmake .. \
  -DCMAKE_VERBOSE_MAKEFILE=ON \
  -DCMAKE_BUILD_TYPE="Debug" \
  -DUSUL_ENABLE_CODE_COVERAGE=ON
cmake --build .

${USUL_BIN_DIR}/usul_testd --abort --use-colour=yes --durations=no

cd ..
gcovr
