#!/bin/sh

set -e

if [ -e test/build ]; then
  rm -rf test/build
fi

mkdir -p test/build
cd test/build

CC=gcc-7 CXX=g++-7 cmake ..
make

exec ./runUnitTests
