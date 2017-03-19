#!/bin/bash

ensure_command () {
  command -v "$1" >/dev/null 2>&1 || {
    echo >&2 "$1 is not installed.  Aborting."; exit 1; }
}

each_source_file () {
  find src -iname "*.h" -o -iname "*.cpp" |
    grep -v "src/ComplexNets/mili/" |
    grep -v "src/ComplexNetsGui/inc/ui_.*.h" |
    grep -v "src/ComplexNetsCmd/cmdline.h" |
    grep -v "src/moc_.*" |
    xargs "$@"
}

