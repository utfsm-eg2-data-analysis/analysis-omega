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
    lastFileInLastDir=88
elif [[ "$tarName" == "C" ]]; then
    totalDirs=10
    lastFileInLastDir=27
elif [[ "$tarName" == "Fe" ]]; then
    totalDirs=13
    lastFileInLastDir=30
elif [[ "$tarName" == "Pb" ]]; then
    totalDirs=4
    lastFileInLastDir=97
fi
lastFile=99

for ((i=1; i <= $totalDirs; i++)); do
    # condition
    if [[ $i -eq $totalDirs ]]; then
	lastFile=$lastFileInLastDir
    fi
    # loop
    for ((j=0; j <= $lastFile; j++)); do
        ./send_split.sh "$tarName" "$(get_num_3dig $i)" "$(get_num_2dig $j)"
    done
done
