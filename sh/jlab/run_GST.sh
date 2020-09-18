#!/bin/bash

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

#####
# Main
###

# set env
source /home/borquez/.bashrc

setOption=
inputOption=
tarName=
rn=

if [[ "$setOption" == "jlab" ]]; then
    for ((sub=1; sub <= 35; sub++)); do
	ssub=$(get_num_2dig $sub)
	./GetSimpleTuple ${inputOption}${tarName} -r"${rn}_${ssub}"
    done
else
    ./GetSimpleTuple ${inputOption}${tarName} -r"${rn}"
fi
