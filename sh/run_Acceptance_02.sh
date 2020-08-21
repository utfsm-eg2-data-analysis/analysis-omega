#!/bin/bash

###############################################################
# ./run_Acceptance_02.sh <set> <target>                       #
#                                                             #
# EG: ./run_Acceptance_02.sh usm D                            #
###############################################################

#####
# Input
###

inputArray=("$@")

setOption="${inputArray[0]}"
tarName="${inputArray[1]}"

#####
# Main
###

#set env
source ~/.bashrc

# set dir
SIMDIR=$PRODIR/out/FilterNCombine/${setOption}/${tarName}/

# copy binary to sim dir
cp -v $PRODIR/bin/Acceptance_02 $SIMDIR

firstBin=(3 1 1 1)
lastBin=(7 5 5 5)

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    counter=0
    for kinvar in "z" "q" "n" "p"; do
	for ((bin=${firstBin[$counter]}; bin <= ${lastBin[$counter]}; bin++)); do
	    rn="${file#*_}"
	    rn="${rn/.root/}"
	    # reconstructed
	    ./Acceptance_02 -s${tarName} -r${rn} -${kinvar}${bin}
	    # generated
	    ./Acceptance_02 -g${tarName} -r${rn} -${kinvar}${bin}
	done
	((counter++))
    done
done

# cleaning
temp="acc.root"
for simtype in "R" "G"; do
    counter=0
    for kinvar in "z" "q" "n" "p"; do
	for ((bin=${firstBin[$counter]}; bin <= ${lastBin[$counter]}; bin++)); do
	    rm acc-2${simtype}-${setOption}-${tarName}-${kinvar}${bin}.root # just in case
	    hadd $temp acc-2${simtype}-${tarName}_*-${kinvar}${bin}.root
	    mv $temp acc-2${simtype}-${setOption}-${tarName}-${kinvar}${bin}.root
	    rm acc-2${simtype}-${tarName}_*-${kinvar}${bin}.root
	done
	((counter++))
    done
done
rm Acceptance_02
