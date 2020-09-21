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
stageOption=

if [[ "$stageOption" == "A" ]]; then
    init=1
    end=10
elif [[ "$stageOption" == "B" ]]; then
    init=11
    end=20
elif [[ "$stageOption" == "C" ]]; then
    init=21
    end=30
elif [[ "$stageOption" == "D" ]]; then
    init=31
    end=35
fi

if [[ "$setOption" == "jlab" ]]; then
    for ((sub=$init; sub <= $end; sub++)); do
	ssub=$(get_num_2dig $sub)
	./FilterNCombine${inputOption} -t${tarName} -r"${rn}_${ssub}"
    done
else
    ./FilterNCombine${inputOption} -t${tarName} -r"${rn}"
fi
