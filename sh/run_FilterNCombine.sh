#!/bin/bash

######################################################################
# ./run_FilterNCombine.sh --targ <target> --set <set> --dttp <dttp>  #
#     <target> = (D, C, Fe, Pb)                                      #
#     <dttp>   = (gsim, simrec)                                      #
#     <set>    = (old, usm, jlab)                                    #
#                                                                    #
# EG: ./run_FilterNCombine.sh --targ Pb --set usm --dttp simrec      #
######################################################################

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--set" ]; then
    setName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--dttp" ]; then
    dataType=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

if [[ ${dataType} = "gsim" ]]; then
  opt="G"
elif [[ ${dataType} = "simrec" ]]; then
  opt="R"
fi

# prev
# catName=`echo ${input/-*/}`
# tarName=`echo ${input/*-/}`

source ~/.bashrc

OUDIR=${PRODIR}/out/filterSim/${dataType}/${setName}/${tarName}
TMPDIR=${PRODIR}/tmp

fileslist=${PRODIR}/include/prunedSimulFiles-${setName}-${tarName}.txt # this!
lines=`wc -l < ${fileslist}`

cd ${PRODIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    sed -e "${COUNTER}q;d" ${fileslist} > ${TMPDIR}/PRU-${setName}-${tarName}.tmp
    ./bin/FilterNCombine -t${tarName} -${opt}${setName}
    inputfile=`head -1 ${TMPDIR}/PRU-${setName}-${tarName}.tmp`
    sufix="${inputfile##*_}"
    sufix="${sufix/.root/}"
    #echo ${inputfile}
    #echo ${sufix}
    mv -v ${OUDIR}/comb_out.root ${OUDIR}/comb_${dataType}${tarName}_${sufix}.root
    rm -v ${TMPDIR}/PRU-${setName}-${tarName}.tmp
done
