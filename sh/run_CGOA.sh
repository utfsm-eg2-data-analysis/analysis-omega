#!/bin/bash

#################################################################
# ./run_CGOA.sh <set> <target> <simrec/gsim>                    #
#                                                               #
# EG: ./run_CGOA.sh old C simrec                                #
#     ./run_CGOA.sh usm D gsim                                  #
#################################################################

# exclusive for old/usm simulations located in the JLAB cluster

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
OUDIR=$PRODIR/out/CheckGammasOpAngle
mkdir -p $OUDIR

if [[ "$simulType" == "gsim" ]]; then
    inputOption="-g${tarName}"
elif [[ "$simulType" == "simrec" ]]; then
    inputOption="-s${tarName}"
fi

# copy binary to sim dir
cp -v $PRODIR/bin/CheckGammasOpAngle $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    if [[ "${sector}" != "" ]]; then
	./CheckGammasOpAngle ${inputOption} -r${rn}
    else
	./CheckGammasOpAngle ${inputOption} -r${rn}
    fi
done

hadd gammas-op-angle.root gammas-op-angle-${tarName}_*.root
rm -v gammas-op-angle-${tarName}_*.root # to clean a little
mv -v gammas-op-angle-${tarName}.png $OUDIR/gammas-op-angle-${setOption}-${tarName}_${simulType}.png
mv -v gammas-op-angle.root $OUDIR/gammas-op-angle-${setOption}-${tarName}_${simulType}.root

rm -v CheckGammasOpAngle
