#!/bin/bash

###############################################################################
# ./run_FilterNCombine.sh --targ <target> --set <set> --n <ndir>              #
#     <target> = (D, C, Fe, Pb)                                               #
#     <set>    = (data, old, usm, jlab)                                       #
#     <ndir>   = (00, 01, 02, ...)                                            #
#                                                                             #
# EG: ./run_FilterNCombine.sh --targ C --set data                             #
#     ./run_FilterNCombine.sh --targ D --set jlab --nn 06                     #
###############################################################################

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--set" ]; then
    setName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--n" ]; then
    nDir=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

cd ${PRODIR}

if [[ ${setName} = "data" ]]; then
  OUDIR=${PRODIR}/out/filterData/${tarName}
  filelist=${PRODIR}/include/prunedDataFiles-${tarName}.txt
  tmpfile=${PRODIR}/tmp/PRU-${setName}-${tarName}.tmp
  opt="-t${tarName} -d"
elif [[ ${setName} = "jlab" ]]; then
  OUDIR=${PRODIR}/out/filterSim/${setName}/${tarName}/${nDir}
  filelist=${PRODIR}/include/prunedSimulFiles-${setName}-${tarName}-${nDir}.txt
  tmpfile=${PRODIR}/tmp/PRU-${setName}-${tarName}-${nDir}.tmp
  opt="-t${tarName} -S${setName} -n${nDir}"
else
  OUDIR=${PRODIR}/out/filterSim/${setName}/${tarName}
  filelist=${PRODIR}/include/prunedSimulFiles-${setName}-${tarName}.txt
  tmpfile=${PRODIR}/tmp/PRU-${setName}-${tarName}.tmp
  opt="-t${tarName} -S${setName}"
fi

source ~/.bashrc

lines=`wc -l < ${filelist}`

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${filelist} > ${tmpfile}
    ./bin/FilterNCombine ${opt}
    inputfile=`head -1 ${tmpfile}`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    mv -v ${OUDIR}/comb_out.root ${OUDIR}/comb_${setName}${tarName}_${sufix}.root
    rm -v ${tmpfile}
done
