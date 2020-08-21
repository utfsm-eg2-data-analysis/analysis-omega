#!/bin/bash

###############################################################
# ./run_Acceptance_00A.sh <set> <gsim/simrec> <target>        #
#                                                             #
# EG: ./run_Acceptance_00A.sh old simrec C                    #
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
cp -v $PRODIR/bin/Acceptance_00A $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./Acceptance_00A ${inputOption} -r${rn}
done

rm acc-0A${letter}-${setOption}-${tarName}.root # just in case
hadd acc.root acc-0A${letter}-*.root
rm acc-0A${letter}-*.root # to clean a little
mv acc.root acc-0A${letter}-${setOption}-${tarName}.root

rm Acceptance_00A
