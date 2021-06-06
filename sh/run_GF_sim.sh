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

SETOPTION=
TARNAME=
RN=
NFILES_BEGIN=
NFILES_END=

if [[ "${SETOPTION}" == "old" || "${SETOPTION}" == "usm" ]]; then
    ./GetSimpleTuple_sim -t${TARNAME} -r${RN}
    ./FilterNCombine_sim -t${TARNAME} -r${RN}
elif [[ "${SETOPTION}" == "jlab" ]]; then
    for ((RN=${NFILES_BEGIN}; RN<=${NFILES_END}; RN++)); do
	srn=$(get_num_2dig $RN)
	./GetSimpleTuple_sim -t${TARNAME} -r${srn}
	./FilterNCombine_sim -t${TARNAME} -r${srn}
    done
fi
