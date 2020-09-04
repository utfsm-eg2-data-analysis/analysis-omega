#!/bin/bash

#################################################################
# ./run_PlotSim_Vertex.sh <set> <target> <gsim/simrec> <sector> #
#                                                               #
# EG: ./run_PlotSim_Vertex.sh old C simrec                      #
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

if [[ "$simulType" == "gsim" ]]; then
    inputOption="-g${tarName}"
elif [[ "$simulType" == "simrec" ]]; then
    inputOption="-s${tarName}"
fi

# copy binary to sim dir
cp -v $PRODIR/bin/PlotSim_Vertex $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    if [[ "${sector}" != ""]]; then
	./PlotSim_Vertex ${inputOption} -r${rn} -S${sector}
    else
	./PlotSim_Vertex ${inputOption} -r${rn}	
    fi
done

# sector
sufixSector="_${sector}"

rm vertex-${tarName}_${simulType}.root # just in case
hadd vertex.root vertex-${tarName}_${simulType}_${sufixSector}_*.root
rm vertex-${tarName}_${simulType}_*.root # to clean a little
mv -v vertex.root vertex-${tarName}_${simulType}_${sufixSector}.root

rm PlotSim_Vertex
