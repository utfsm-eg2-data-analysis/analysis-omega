#!/bin/bash

###############################################################
# ./run_Acceptance_00B.sh <set> <gsim/simrec> <target>        #
#                                                             #
# EG: ./run_Acceptance_00B.sh old simrec C                    #
###############################################################

#####
# Input
###

inputArray=("$@")

setOption="${inputArray[0]}"
simulType="${inputArray[1]}"
tarName="${inputArray[2]}"

#####
# Main
###

#set env
source ~/.bashrc

# set dir
SIMDIR=$PRODIR/out/FilterNCombine/${setOption}/${tarName}/

if [[ "$simulType" == "gsim" ]]; then
    inputOption="-g${tarName}"
    letter="G"
elif [[ "$simulType" == "simrec" ]]; then
    inputOption="-s${tarName}"
    letter="R"
fi

# copy binary to sim dir
cp -v $PRODIR/bin/Acceptance_00B $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./Acceptance_00B ${inputOption} -r${rn}
done

hadd acc-0B${letter}-${setOption}-${tarName}.root acc-0B${letter}-*.root
