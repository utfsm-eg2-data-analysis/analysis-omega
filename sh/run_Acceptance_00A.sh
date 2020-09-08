#!/bin/bash

###############################################################
# ./run_Acceptance_00A.sh <set> <target> <gsim/simrec>        #
#                                                             #
# EG: ./run_Acceptance_00A.sh old C simrec                    #
###############################################################

#####
# Input
###

inputArray=("$@")

setOption="${inputArray[0]}"
tarName="${inputArray[1]}"
simulType="${inputArray[2]}"

#####
# Main
###

#set env
source ~/.bashrc

# set dir
SIMDIR=$PRODIR/out/FilterNCombine/${setOption}/${tarName}/
OUDIR=$PRODIR/out/Acceptance/
mkdir -p $OUDIR # just in case

if [[ "$simulType" == "gsim" ]]; then
    inputOption="-g${tarName}"
elif [[ "$simulType" == "simrec" ]]; then
    inputOption="-s${tarName}"
fi

# copy binary to sim dir
cp -v $PRODIR/bin/Acceptance_00A $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./Acceptance_00A ${inputOption} -r${rn}
done

hadd acc.root acc-0A-${tarName}_${simulType}_*.root
rm -v acc-0A-${tarName}_${simulType}_*.root # to clean a little
mv -v acc.root $OUDIR/acc-0A-${tarName}_${simulType}.root

rm -v Acceptance_00A
