#!/bin/bash

###########################################
# ./run_GST_12m.sh <category-target>      #
#     <target>   = (D, C, Fe, Pb)         #
#     <category> = (old, usm, jlab)       #
#                                         #
# EG: ./run_GST_12m.sh bad-Pb             #
###########################################

# preliminary, only works for 12m

input="$@"
catName=`echo ${input/-*/}`
tarName=`echo ${input/*-/}`

source ~/.bashrc

OUDIR=${PRODIR}/out/prunedSim/${catName}/${tarName}
TMPDIR=${PRODIR}/tmp

fileslist=${PRODIR}/include/simulFiles-${input}_12m--usm.txt # this!
lines=`wc -l < ${fileslist}`

cd ${PRODIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${fileslist} > ${TMPDIR}/RAW-${input}.tmp
    ./bin/GetSimpleTuple -t${tarName} -S${catName}
    inputfile=`head -1 simulFiles-${input}.tmp`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    #echo ${inputfile}
    #echo ${sufix}
    mv -v ${OUDIR}/pruned_out.root ${OUDIR}/pruned${tarName}_${sufix}.root
    rm -v ${TMPDIR}/RAW-${input}.tmp
done
