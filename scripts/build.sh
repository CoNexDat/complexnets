#!/bin/sh

set -e

if [ -e build ]; then
  rm -rf build
fi

mkdir build
cd build

CC=gcc-6 CXX=g++-6 cmake ..
make
