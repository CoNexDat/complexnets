#!/bin/sh

set -e

if [ ! -e build ]; then
    mkdir -p build
fi

cd build
CC=gcc-7 CXX=g++-7 cmake ..
make runUnitTests

exec ./runUnitTests
