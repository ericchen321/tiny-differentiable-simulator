#!/bin/bash

ROOT=$(pwd)

rm -rf build/
mkdir build
cd build
cmake .. \
    -DCeres_DIR=$ROOT/third_party/ceres-solver/build_cmake/local_install/lib/cmake/Ceres/ \
    -DBullet_DIR=$ROOT/third_party/bullet3/build_cmake 2>&1 | tee cmake.log
make -j 2>&1 | tee build.log