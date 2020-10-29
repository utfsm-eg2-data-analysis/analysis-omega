#!/bin/bash

##############################################################
# ./send-missing_AEN.sh                                      #
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

# set env
source ~/.bashrc
cd ${PRODIR}/sh/jlab

# Simulations/jlab
tarArray=("D" "C" "Fe" "Pb")
for tarName in "${tarArray[@]}"; do
    totalDirs=$(ls -1 ${WORKDIR}/GetSimpleTuple/jlab/${tarName} | wc -l)
    for ((j=0; j < ${totalDirs}; j++)); do
	ndir=$(get_num_2dig $j)
	# missing file
	if [ ! -f ${WORKDIR}/Acceptance_EN/jlab/${tarName}/${ndir}/acc-en_jlab-${tarName}-${ndir}.root ]; then
	    ./send_AEN.sh jlab ${tarName} ${ndir}
	fi
    done
done