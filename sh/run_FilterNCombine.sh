#!/bin/bash

###############################################
# ./run_FilterNCombine.sh <category-target>   #
#     <target>   = (D, C, Fe, Pb)             #
#     <category> = (old, usm, jlab)           #
#                                             #
# EG: ./run_FilterNCombine.sh bad-Pb          #
###############################################

# preliminary
# only works for (gsim) in the 12m
# i'm interested in jlab-D, jlab-C, jlab-Fe, usm-Pb

input="$@"
catName=`echo ${input/-*/}`
tarName=`echo ${input/*-/}`

source ~/.bashrc

OUDIR=${PRODIR}/out/filterSim/gsim/${catName}/${tarName}
TMPDIR=${PRODIR}/tmp

fileslist=${PRODIR}/include/prunedSimulFiles-${tarName}.txt # this!
lines=`wc -l < ${fileslist}`

cd ${PRODIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${fileslist} > ${TMPDIR}/PRU-${input}.tmp
    ./bin/FilterNCombine -t${tarName} -G${catName}
    inputfile=`head -1 ${TMPDIR}/PRU-${input}.tmp`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    #echo ${inputfile}
    #echo ${sufix}
    mv -v ${OUDIR}/comb_out.root ${OUDIR}/comb_gsim${tarName}_${sufix}.root
    rm -v ${TMPDIR}/PRU-${input}.tmp
done
