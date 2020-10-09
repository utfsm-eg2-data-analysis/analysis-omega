#!/bin/bash

##############################################################
# ./send-all_AEN.sh                                          #
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
./send_AEN.sh old C
./send_AEN.sh old Fe

# Simulations/usm
./send_AEN.sh usm D
./send_AEN.sh usm C
./send_AEN.sh usm Fe
./send_AEN.sh usm Pb

# Simulations/jlab
tarArray=("D" "C" "Fe" "Pb")
for tarName in "${tarArray[@]}"; do
    totalDirs=$(ls -1 ${WORKDIR}/GetSimpleTuple/jlab/${tarName} | wc -l)
    for ((j=0; j < ${totalDirs}; j++)); do
	ndir=$(get_num_2dig $j)
	./send_AEN.sh jlab ${tarName} ${ndir}
    done
done
