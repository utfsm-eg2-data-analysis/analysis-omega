#!/bin/bash

#################################################
# ./run_Acceptance_00B.sh <set> <target>        #
#                                               #
# EG: ./run_Acceptance_00B.sh old C             #
#################################################

# testing for reconstructed only

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

SIMDIR=$PRODIR/out/FilterNCombine/${setOption}/${tarName}/

# copy binary to sim dir
cp -v $PRODIR/bin/Acceptance_00B $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./Acceptance_00B -s${tarName} -r${rn}
done

hadd acc-0BR-${setOption}-${tarName}.root acc-0BR-*.root
