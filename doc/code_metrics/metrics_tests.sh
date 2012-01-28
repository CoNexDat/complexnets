#!/bin/bash

rm -rf metrics_tests
cd ../../test

cccc `find | egrep "*Test(\.cpp|\.h)$"` --outdir=./code_metrics/metrics_tests


