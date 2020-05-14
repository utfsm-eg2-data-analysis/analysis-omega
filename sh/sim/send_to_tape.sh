#!/bin/bash

#####################################################
# ./send_to_tape.sh --targ <target> --n <number>    #
#     <target> = (D, C, Fe, Pb)                     #
#     <number> = (00, 01, 02, ...)                  #
#                                                   #
# EG: ./send_to_tape.sh --targ D --n 00             #
#####################################################

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

SIMDIR=/home/borquez/volatile/omegaSim
OUDIR=${SIMDIR}/output/${tarName}/${nn}

TAPEDIR=/mss/clas/eg2a/production/Simulation/omega_lepto/${tarName}/${nn}

cd ${OUDIR}
pwd

jput *.root ${TAPEDIR}/

ls -lrth ${TAPEDIR}
echo "Process ${tarName}-${nn} ready!"
