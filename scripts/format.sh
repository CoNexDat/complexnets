#!/bin/bash

set -e

source "${BASH_SOURCE%/*}/util.sh"

ensure_command clang-format

each_source_file clang-format -i
