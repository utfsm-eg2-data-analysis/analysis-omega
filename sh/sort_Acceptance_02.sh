#!/bin/bash

# ./sort_Acceptance_02.sh

# after getting every Acceptance_02 output file

OUDIR=$PRODIR/out/Acceptance/stage2/
mkdir -p $OUDIR # just in case

cd $OUDIR

firstBin=(3 1 1 1)
lastBin=(7 5 5 5)

for tarName in "D" "C" "Fe" "Pb"; do
    counter=0
    for kinvar in "z" "q" "n" "p"; do
	for ((bin=${firstBin[$counter]}; bin <= ${lastBin[$counter]}; bin++)); do
	    for simtype in "R" "G"; do
		hadd acc-2${simtype}-${tarName}-${kinvar}${bin}.root acc-2${simtype}-*-${tarName}-${kinvar}${bin}.root
	    done
	done
	((counter++))
    done
done
