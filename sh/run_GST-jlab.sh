#!/bin/bash

####################################################################
# ./run_GST-jlab.sh --targ <target> --dir1 <ndir> --dir2 <ndir>    #
#     <target> = (D, C, Fe, Pb)                                    #
#     <ndir>   = (0, ..., XX)                                      # 
#                                                                  #
# EG: ./run_GST-jlab.sh --targ D --dir1 0 --dir2 3                 #
#                                                                  #
####################################################################
#                                                                  #
# Version:                                                         #
# --- Use it on jlab cluster, in a tmux screen!                    #
# --- Only for jlab simulations!                                   #
#                                                                  #
####################################################################

#####
# Functions
###

function get_run()
{
  sr=$1
  srn=""
  if [ $sr -lt 10 ]; then
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
  elif [ "${inputArray[$ic]}" == "--dir1" ]; then
    nDir1=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--dir2" ]; then
    nDir2=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

cd ${PRODIR}

for (( id=$nDir1; id<=$nDir2; id++ )); do

  sdir=$(get_run "$id")
  opt="-t${tarName} -Sjlab -n${sdir}"
  
  for (( rn=0; rn<100; rn++ )); do
    srn=$(get_run "$rn")
    ./bin/GetSimpleTuple ${opt} -r${srn}
  done
 
done
