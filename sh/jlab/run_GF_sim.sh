#!/bin/bash

# set env
source /home/borquez/.bashrc

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

setOption=
tarName=
rn=
nfiles_begin=
nfiles_end=

if [[ "${setOption}" == "old" || "${setOption}" == "usm" ]]; then
    ./GetSimpleTuple_sim -t${tarName} -r${rn}
    ./FilterNCombine_sim -t${tarName} -r${rn}
elif [[ "${setOption}" == "jlab" ]]; then
    for ((rn=$nfiles_begin; rn <= $nfiles_end; rn++)); do
	srn=$(get_num_2dig $rn)
	./GetSimpleTuple_sim -t${tarName} -r${srn}
	./FilterNCombine_sim -t${tarName} -r${srn}
    done
fi
