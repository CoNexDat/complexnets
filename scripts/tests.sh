#!/bin/sh

set -e

if [ -e test/build ]; then
  rm -rf test/build
fi

mkdir -p test/build
cd test/build

CC=gcc-6 CXX=g++-6 cmake ..
make

exec ./runUnitTests
