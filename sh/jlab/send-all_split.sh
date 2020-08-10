#!/bin/bash

##############################################################
# ./send-all_split.sh <target>                               #
#     <target> = (D, C, Fe, Pb)                              #
#                                                            #
# EG: ./send-all_split.sh C                                  #
##############################################################

#####
# Functions
###

function get_num_2dig()
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

function get_num_3dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 100 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

#####
# Input
##

tarName="$@"

#####
# Main
##

source ~/.bashrc
cd ${PRODIR}/sh/jlab

if [[ "$tarName" == "D" ]]; then
    totalDirs=46
elif [[ "$tarName" == "C" ]]; then
    totalDirs=10
elif [[ "$tarName" == "Fe" ]]; then
    totalDirs=13
elif [[ "$tarName" == "Pb" ]]; then
    totalDirs=4
fi

for ((i=1; i <= $totalDirs; i++)); do
    for ((j=0; j <= 99; j++)); do
        ./send_split.sh "$tarName" "$(get_num_3dig $i)" "$(get_num_2dig $j)"
    done
done
