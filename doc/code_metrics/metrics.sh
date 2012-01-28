#!/bin/bash

rm -rf metrics
cd ../../complexnets
exclude="tree-gen|Console|ParserBak|PhyloGUI"

cccc `(find | egrep -v $exclude) | egrep "*(\.cpp|\.h)$"` --outdir=./code_metrics/metrics


