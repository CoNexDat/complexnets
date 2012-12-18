#!/bin/bash

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
	./complexnets -i $1 $2 -o $3
	gnuplotCommand="set style data linespoint; set term png; set title '$4'; set xlabel '$5'; set ylabel '$6'; set output '$3.png'; plot '$3'"

	if $8 ; then
		gnuplotCommand="set logscale y; $gnuplotCommand"
	fi

	if $7 ; then
		gnuplotCommand="set logscale x; $gnuplotCommand"
	fi

	gnuplot -e "$gnuplotCommand"
	rm $3
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

savePlot $1 "--betweenness-output" "$directory/${directory}_betweenness" "Betweeness" "Degree" "Betweeness" true false
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