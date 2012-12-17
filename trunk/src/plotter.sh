#!/bin/bash

# I get the filename without both full path and extension.
filename=$(basename "$1")
extension="${filename##*.}"
directory="${filename%.*}"

log_bin=false
if [ $# -eq 2 ] ; then
	log_bin=true
	number_of_bins=$2
fi

# If a directory with the filename exists, we delete and create it
# again.
rm -r $directory
mkdir $directory

./complexnets -i $1 --betweenness-output -o "$directory/${directory}_betweenness"

./complexnets -i $1 --ddist-output -o "$directory/${directory}_ddist"

if $log_bin ; then
	./complexnets -i $1 --ddist-output --log-bin=$number_of_bins -o "$directory/${directory}_ddist_logbin${number_of_bins}"
fi

./complexnets -i $1 --clustering-output -o "$directory/${directory}_clustering"

./complexnets -i $1 --knn-output -o "$directory/${directory}_knn"

./complexnets -i $1 --shell-output -o "$directory/${directory}_shell"