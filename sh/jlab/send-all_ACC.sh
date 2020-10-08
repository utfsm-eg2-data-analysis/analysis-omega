#!/bin/bash

##############################################################
# ./send-all_ACC.sh                                          #
#                                                            #
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

#####
# Main
##

source ~/.bashrc
cd ${PRODIR}/sh/jlab

# Simulations/old
# ./send_ACC.sh old C
# ./send_ACC.sh old Fe

# Simulations/usm
# ./send_ACC.sh usm D
# ./send_ACC.sh usm C
# ./send_ACC.sh usm Fe
# ./send_ACC.sh usm Pb

# Simulations/jlab
tarArray=("D" "C" "Fe" "Pb")
for tarName in "${tarArray[@]}"; do
    totalDirs=$(ls -1 ${WORKDIR}/FilterNCombine/jlab/${tarName} | wc -l)
    for ((j=0; j < ${totalDirs}; j++)); do
	ndir=$(get_num_2dig $j)
	./send_ACC.sh jlab ${tarName} ${ndir}
    done
done
