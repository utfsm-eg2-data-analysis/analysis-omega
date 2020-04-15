#!/bin/bash

###########################################
# ./run_OID-gsim.sh <category-target>     #
#     <target>   = (D, C, Fe, Pb)         #
#     <category> = (old, bad, usm, jlab)  #
#                                         #
# EG: ./run_OID-gsim.sh bad-Pb            #
###########################################

input="$@"
catName=`echo ${input/-*/}`
tarName=`echo ${input/*-/}`

INDIR=/user/b/borquez/omega/OmegaID
TOPDIR=/eos/user/b/borquez/filterSim/gsim # important!
OUDIR=${TOPDIR}/${catName}/${tarName}

fileslist=${INDIR}/input/prunedFiles-${input}.txt
lines=`wc -l < ${fileslist}`

cd ${INDIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${fileslist} > prunedFiles-${input}.tmp
    ./OmegaID -ts -T${tarName} -f${catName}
    inputfile=`head -1 prunedFiles-${input}.tmp`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    #echo ${inputfile}
    #echo ${sufix}
    mv -v ${OUDIR}/wout_${tarName}.root ${OUDIR}/wout_gsim${tarName}_${sufix}.root
    rm -v prunedFiles-${input}.tmp
done
