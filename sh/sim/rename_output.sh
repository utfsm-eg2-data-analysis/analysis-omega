#!/bin/bash

#####################################################
# ./rename_output.sh --targ <target> --ndir <ndir>  #
#     <target> = (D, C, Fe, Pb)                     #
#     <ndir>   = (00, 01, .., 99)                   #
#                                                   #
# EG: ./rename_output.sh --targ D --ndir 27         #
#####################################################

#####
# Functions
###

function get_num()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="000$sr"
  elif [[ $sr -lt 100 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 1000 ]]; then
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
  elif [ "${inputArray[$ic]}" == "--ndir" ]; then
    auxDir=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

OUDIR=/home/borquez/volatile/omegaSim/output/${tarName}/${auxDir}
cd ${OUDIR}
echo "Executing rename_output.sh..."

count=0
for file in *.root; do
  ((count++))
  scount=$(get_num "${count}")
  srun=${file##*_}
  srun=${srun/.root/}
  #echo ${srun}
  #echo ${scount}
  #echo
  if [ ${scount} != ${srun} ]; then
    mv -v ${file} recsis${tarName}_${scount}.root
  fi
done

echo "Everything ready, sir!"
