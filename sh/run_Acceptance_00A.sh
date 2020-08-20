#!/bin/bash

#################################################
# ./run_Acceptance_00A.sh <set> <target>        #
#                                               #
# EG: ./run_Acceptance_00A.sh old C             #
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
cp -v $PRODIR/bin/Acceptance_00A $SIMDIR

cd $SIMDIR
for file in $SIMDIR/*; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./Acceptance_00A -s${tarName} -r${rn}
done

hadd acc-0AR-${setOption}-${tarName}.root acc-0AR-*.root
