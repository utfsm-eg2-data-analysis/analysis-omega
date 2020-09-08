#!/bin/bash

#################################################################
# ./run_CGOA.sh <set> <target> <simrec/gsim> <stage>            #
#                                                               #
# EG: ./run_CGOA.sh old C simrec                                #
#     ./run_CGOA.sh usm D gsim plot                             #
#################################################################

# exclusive for old/usm simulations located in the JLAB cluster

#####
# Input
###

inputArray=("$@")

setOption="${inputArray[0]}"
tarName="${inputArray[1]}"
simulType="${inputArray[2]}"
stageOption="${inputArray[3]}"

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

if [[ "$simulType" == "gsim" && "$stageOption" == "plot" ]]; then
    binOption="_plot"
    prefix="plot-"
else
    binOption=""
    prefix=""
fi

# copy binary to sim dir
cp -v $PRODIR/bin/CheckGammasOpAngle${binOption} $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    ./CheckGammasOpAngle${binOption} ${inputOption} -r${rn}
done

hadd ${prefix}gammas-op-angle.root ${prefix}gammas-op-angle-${tarName}_*.root
rm -v ${prefix}gammas-op-angle-${tarName}_*.root # to clean a little
mv -v ${prefix}gammas-op-angle-${tarName}.png $OUDIR/${prefix}gammas-op-angle-${setOption}-${tarName}_${simulType}.png
mv -v ${prefix}gammas-op-angle.root $OUDIR/${prefix}gammas-op-angle-${setOption}-${tarName}_${simulType}.root

rm -v CheckGammasOpAngle${binOption}
