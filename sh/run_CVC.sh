#!/bin/bash

#################################################################
# ./run_CVC.sh <set> <target> <gsim/simrec> <sector>            #
#                                                               #
# EG: ./run_CVC.sh old C simrec                                 #
#     ./run_CVC.sh old C gsim 5                                 #
#################################################################

#####
# Input
###

inputArray=("$@")

setOption="${inputArray[0]}"
tarName="${inputArray[1]}"
simulType="${inputArray[2]}"
sector="${inputArray[3]}"

#####
# Main
###

#set env
source ~/.bashrc

# set dir
SIMDIR=$PRODIR/out/FilterNCombine/${setOption}/${tarName}/
OUDIR=$PRODIR/out/CheckVertexCuts
mkdir -p $OUDIR

if [[ "$simulType" == "gsim" ]]; then
    inputOption="-g${tarName}"
elif [[ "$simulType" == "simrec" ]]; then
    inputOption="-s${tarName}"
fi

# copy binary to sim dir
cp -v $PRODIR/bin/CheckVertexCuts $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    if [[ "${sector}" != "" ]]; then
	./CheckVertexCuts ${inputOption} -r${rn} -S${sector}
    else
	./CheckVertexCuts ${inputOption} -r${rn}
    fi
done

# sector
if [[ "$sector" != "" ]]; then
    sufixSector="_sector${sector}"
fi

# just in case
rm -v vertex-${tarName}_${simulType}${sufixSector}.root
rm -v vertex-${tarName}_${simulType}${sufixSector}.png

hadd vertex.root vertex-${tarName}_${simulType}${sufixSector}_*.root
rm vertex-${tarName}_${simulType}${sufixSector}_*.root # to clean a little
mv -v vertex.root $OUDIR/vertex-${setOption}-${tarName}_${simulType}${sufixSector}.root

rm -v CheckVertexCuts
