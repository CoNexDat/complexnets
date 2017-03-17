#!/bin/sh

set -e

cd src

QT_SELECT=qt5 qmake
exec make all
