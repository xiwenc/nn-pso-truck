#!/bin/sh

MAIN=./main
OUTPUT=output

if [ ! -x $MAIN ]; then
    echo "Executable not found! Did you run 'make'?"
    exit 1;
fi

if [ ! -d $OUTPUT ]; then
    mkdir $OUTPUT
fi

$MAIN -a 1 -d 1000 -i 1000 -p 20 -s 20 -m 2 > $OUTPUT/ga-1000.data
$MAIN -a 1 -d 1000 -i 1000 -p 20 -s 20 -m 1 > $OUTPUT/pso-1000.data
$MAIN -a 1 -d 1000 -i 1000 -p 20 -s 2 -m 0 > $OUTPUT/bs-1000.data


if [ `which gnuplot` ]; then
    gnuplot ackley-1000.gnu > $OUTPUT/graph-1000.png
fi

