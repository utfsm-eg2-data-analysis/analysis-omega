#!/bin/bash 

################################
# ./run_GST-data.sh <target>   #
#     <target> = (C, Fe, Pb)   #
#                              #
# EG: ./run_GST-data.sh Pb     #
################################

# only for utfsm cluster

tarName="$@"

if [[ ${tarName} = "C" ]]; then
  tarLongName="C-thickD2"
elif [[ ${tarName} = "Fe" ]]; then
  tarLongName="Fe-thickD2"
elif [[ ${tarName} = "Pb" ]]; then
  tarLongName="Pb-thinD2"
fi

DATADIR=/data/jlab/mss/clas/eg2a/production/Pass2/Clas
OUDIR=${PRODIR}/out/prunedData/${tarName}

runlist="include/${tarLongName}rn.txt"
lines=`wc -l < ${runlist}`

cd ${PRODIR}

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
  let COUNTER=COUNTER+1
  rn=`sed -n "$COUNTER{p;q}" $runlist`
  readlink -f ${DATADIR}/clas*${rn}*.root > tmp/RAW-data-${tarName}.tmp
  ./bin/GetSimpleTuple -t${tarName} -d
  mv -v ${OUDIR}/pruned_out.root ${OUDIR}/pruned_data_${rn}.root
done
