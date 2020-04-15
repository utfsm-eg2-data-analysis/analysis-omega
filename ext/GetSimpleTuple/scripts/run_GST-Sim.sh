#!/bin/bash

###########################################
# ./run_GST-Sim.sh <category-target>      #
#     <target>   = (D, C, Fe, Pb)         #
#     <category> = (old, bad, usm, jlab)  #
#                                         #
# EG: ./run_GST-Sim.sh bad-Pb             #
###########################################

input="$@"
catName=`echo ${input/-*/}`
tarName=`echo ${input/*-/}`

INDIR=/user/b/borquez/omega/GetSimpleTuple
TOPDIR=/eos/user/b/borquez/prunedSim
OUDIR=${TOPDIR}/${catName}/${tarName}

fileslist=${INDIR}/input/simulFiles-${input}.txt
lines=`wc -l < ${fileslist}`

cd ${INDIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${fileslist} > simulFiles-${input}.tmp
    ./GetSimpleTuple -s${tarName} -f${catName}
    inputfile=`head -1 simulFiles-${input}.tmp`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    #echo ${inputfile}
    #echo ${sufix}
    mv -v ${OUDIR}/pruned${tarName}.root ${OUDIR}/pruned${tarName}_${sufix}.root
    rm -v simulFiles-${input}.tmp
done
