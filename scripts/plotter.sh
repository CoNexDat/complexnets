#!/bin/bash

# Usage:
# 	sh plotter.sh <input_file>
#	sh plotter.sh <input_file> <number_of_bins>
#
# <input_file>: the file that stores a graph (it must have an extension).
# <number_of_bins>: if sent, each function is plotted with log-bin with this amount of bins.

# -----------------------------------------------------------------------------

# This script is licensed under the Academic Free License 3.0.
# Instituto Tecnológico de Buenos Aires (ITBA).
# Last modification: December 19th, 2012.


# $1: input filename.
# $2: complexnets output argument.
# $3: output filename.
# $4: title.
# $5: x label.
# $6: y label.
# $7: use x logscale.
# $8: use y logscale.
savePlot ()
{
	../build/complexnets -i $1 $2 -o $3

	# Uncomment to generate a PS file.
	# gnuplotCommand="set style data linespoint; set term postscript color; set title '$4'; set xlabel '$5'; set ylabel '$6'; set output '$3.ps'; plot '$3'"

	gnuplotCommand="set style data linespoint; set term pdfcairo; set title '$4'; set xlabel '$5'; set ylabel '$6'; set output '$3.pdf'; plot '$3'"

	if $8 ; then
		gnuplotCommand="set logscale y; $gnuplotCommand"
	fi

	if $7 ; then
		gnuplotCommand="set logscale x; $gnuplotCommand"
	fi

	gnuplot -e "$gnuplotCommand"
}

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
if [ -d $directory ]; then
    rm -r $directory
fi
mkdir $directory

# savePlot $1 "--betweenness-output" "$directory/${directory}_betweenness" "Betweeness" "Degree" "Betweeness" true false
savePlot $1 "--ddist-output" "$directory/${directory}_ddist" "Degree distribution" "Degree" "Frequency" true true
savePlot $1 "--clustering-output" "$directory/${directory}_clustering" "Clustering coefficient" "Degree" "Clustering coefficient" true true
savePlot $1 "--knn-output" "$directory/${directory}_knn" "Nearest neighbors degree" "Degree" "Nearest neighbors degree" true true
savePlot $1 "--shell-output" "$directory/${directory}_shell" "Shell index" "Degree" "Shell index" true true

if $log_bin ; then
	savePlot $1	"--ddist-output --log-bin=$number_of_bins" \
				"$directory/${directory}_ddist_logbin${number_of_bins}" \
				"Degree distribution (log bin - $number_of_bins bins)" \
				"Degree" \
				"Frequency" \
				true true
fi