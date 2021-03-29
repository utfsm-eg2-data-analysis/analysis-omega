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
    # 0) GST + FNC
    ./GetSimpleTuple_sim -t${TARNAME} -r${RN}
    ./FilterNCombine_sim -t${TARNAME} -r${RN}
    # 1) Reductor
    ./Reductor -t${TARNAME} -r${RN} -s0 # MC
    ./Reductor -t${TARNAME} -r${RN} -s1 # SimRec
    # 2) Event-Mixing, SimRec
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red" -m"211"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red" -m"-211"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red" -m"111"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red" -m"999"
    # 3) Event-Mixing, MC
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"211"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"-211"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"111"
    ./FilterNCombine_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"999"
elif [[ "${SETOPTION}" == "jlab" ]]; then
    for ((RN=${NFILES_BEGIN}; RN<=${NFILES_END}; RN++)); do
	srn=$(get_num_2dig $RN)
	# 0) GST + FNC
	./GetSimpleTuple_sim -t${TARNAME} -r${srn}
	./FilterNCombine_sim -t${TARNAME} -r${srn}
	# 1) Reductor
	./Reductor -t${TARNAME} -r${srn} -s0 # MC
	./Reductor -t${TARNAME} -r${srn} -s1 # SimRec
	# 2) Event-Mixing, SimRec
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red" -m"211"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red" -m"-211"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red" -m"111"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red" -m"999"
	# 3) Event-Mixing, MC
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red_MC" -g"211"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red_MC" -g"-211"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red_MC" -g"111"
	./FilterNCombine_sim -t"${TARNAME}" -r"${srn}_red_MC" -g"999"
    done
fi
