#!/bin/bash

#################################################################
# ./run_CSF.sh <set> <target>                                   #
#                                                               #
# EG: ./run_CSF.sh old C                                        #
#     ./run_CSF.sh usm D                                        #
#################################################################

# exclusive for old/usm simulations located in the JLAB cluster

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
OUDIR=$PRODIR/out/CheckSampFrac
mkdir -p $OUDIR

# copy binary to sim dir
cp -v $PRODIR/bin/CheckSampFrac $SIMDIR

cd $SIMDIR
for file in $SIMDIR/comb*.root; do
    rn="${file#*_}"
    rn="${rn/.root/}"
    if [[ "${sector}" != "" ]]; then
	./CheckSampFrac -s${tarName} -r${rn}
    else
	./CheckSampFrac -s${tarName} -r${rn}
    fi
done

hadd samp-frac.root samp-frac-${tarName}_*.root
rm -v samp-frac-${tarName}_*.root # to clean a little
mv -v samp-frac-${tarName}.png $OUDIR/samp-frac-${setOption}-${tarName}.png
mv -v samp-frac.root $OUDIR/samp-frac-${setOption}-${tarName}.root

rm -v CheckSampFrac
