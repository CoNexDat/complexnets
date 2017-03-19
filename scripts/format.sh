#!/bin/sh

command -v clang-format >/dev/null 2>&1 || {
  echo >&2 "clang-format is not installed.  Aborting."; exit 1; }

exec find src -iname "*.h" -o -iname "*.cpp" |
  grep -v "src/ComplexNets/mili/" |
  grep -v "src/ComplexNetsGui/inc/ui_.*.h" |
  xargs clang-format -i
