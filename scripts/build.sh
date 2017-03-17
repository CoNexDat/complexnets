#!/bin/sh

set -e

cd src
qmake -qt=5
exec make all
