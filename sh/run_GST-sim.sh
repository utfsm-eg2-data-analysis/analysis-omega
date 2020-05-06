#!/bin/bash

#################################################################
# ./run_GST-sim.sh --targ <target> --set <set> --n <ndir>       #
#     <target> = (D, C, Fe, Pb)                                 #
#     <set> = (old, usm, jlab)                                  #
#     <ndir> = (00, 01, 02, ...)                                # 
#                                                               #
# EG: ./run_GST-sim.sh --targ D --set jlab --n 00               #
#     ./run_GST-sim.sh --targ C --set old                       #
#     ./run_GST-sim.sh --targ Fe --set usm                      #
#################################################################
#                                                               #
# This version:                                                 #
# --- should work in utfsm and jlab cluster                     #
# --- requires the simulFiles-set-target(-ndir).txt in include/ #
#                                                               #
#################################################################

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--set" ]; then
    setName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--n" ]; then
    nDir=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. Please, execute: head -15 run_GST-sim.sh to print usage. ***\n\n";
  fi
  ((ic+=2))
done

cd ${PRODIR}

if [[ ${setName} = "jlab" ]]; then
  OUDIR=${PRODIR}/out/prunedSim/${setName}/${tarName}/${nDir}
  filelist=${PRODIR}/include/simulFiles-${setName}-${tarName}-${nDir}.txt
  tmpfile=${PRODIR}/tmp/RAW-${setName}-${tarName}-${nDir}.tmp
  opt="-t${tarName} -S${setName} -n${nDir}"
else
  OUDIR=${PRODIR}/out/prunedSim/${setName}/${tarName}
  filelist=${PRODIR}/include/simulFiles-${setName}-${tarName}.txt
  tmpfile=${PRODIR}/tmp/RAW-${setName}-${tarName}.tmp
  opt="-t${tarName} -S${setName}"
fi

lines=`wc -l < ${filelist}`

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
  let COUNTER=COUNTER+1
  rn=`sed -n "$COUNTER{p;q}" ${filelist}`
  echo ${rn} > ${tmpfile}
  rn=`echo ${rn/*_/}`
  rn=`echo ${rn/.*/}`
  ./bin/GetSimpleTuple ${opt}
  mv -v ${OUDIR}/pruned_out.root ${OUDIR}/pruned_sim${tarName}_${rn}.root
done
