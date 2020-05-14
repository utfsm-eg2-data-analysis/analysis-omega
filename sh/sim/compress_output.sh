#!/bin/bash

#####################################################
# ./compress_output.sh --targ <target> --n <number> #
#     <target> = (D, C, Fe, Pb)                     #
#     <number> = (00, 01, 02, ...)                  #
#                                                   #
# EG: ./compress_output.sh --targ D --n 00          #
#####################################################

#####
# Functions
###

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

#####
# Main
###

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--n" ]; then
    nn=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]} ***\n\n";
  fi
  ((ic+=2))
done

SIMDIR=/home/borquez/volatile/omegaSim/
OUDIR=${SIMDIR}/output/${tarName}/${nn}

cd ${OUDIR}
mkdir -p hadding
pwd

counter=0
while [ ${counter} -le 99 ]; do
  scount=$(get_num "${counter}")
  mv recsis${tarName}_${scount}* hadding/
  hadd recsis${tarName}_${scount}.root hadding/recsis${tarName}_${scount}*
  rm hadding/*
  ((counter++))
done

ls -lrth
echo "Process ${tarName}-${nn} ready!"

