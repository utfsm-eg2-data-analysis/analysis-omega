#!/bin/bash

function get_num()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

source ~/.bashrc
cd ${PRODIR}/sh

# Deuterium

tarName="D"
dirs=45

COUNTER=0
while [ ${COUNTER} -lt ${dirs} ]; do
    let COUNTER=COUNTER+1
    ndir=$(get_num "$((COUNTER-1))") # start at 00
    ./run_GST-jlab.sh ${tarName} ${ndir}
done

# Carbon

tarName="C"
dirs=8

COUNTER=1
while [ ${COUNTER} -lt ${dirs} ]; do
    let COUNTER=COUNTER+1
    ndir=$(get_num "$((COUNTER-1))") # start at 01
    ./run_GST-jlab.sh ${tarName} ${ndir}
done

# Iron

tarName="Fe"
dirs=11

COUNTER=0
while [ ${COUNTER} -lt ${dirs} ]; do
    let COUNTER=COUNTER+1
    ndir=$(get_num "$((COUNTER-1))") # start at 00
    ./run_GST-jlab.sh ${tarName} ${ndir}
done

# Lead

tarName="Pb"
dirs=4

COUNTER=0
while [ ${COUNTER} -lt ${dirs} ]; do
    let COUNTER=COUNTER+1
    ndir=$(get_num "$((COUNTER-1))") # start at 00
    ./run_GST-jlab.sh ${tarName} ${ndir}
done
