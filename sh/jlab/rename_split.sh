#!/bin/bash

##############################################################
# ./rename_split.sh <target>                                 #
#     <target> = (D, C, Fe, Pb)                              #
#                                                            #
# EG: ./rename_split.sh C                                    #
##############################################################

# It renames the simulation files inside the D2, C2, Fe2 and Pb2 dirs, from 001 to 300

#####
# Functions
###

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
# Main
###

# set env
source ~/.bashrc

tarName="$@"

INDIR="/home/borquez/volatile/omegaSim/output/${tarName}2"
cd ${INDIR}

for dir in */; do
    count=0
    for file in $dir/*.root; do
	((count++))
	scount=$(get_num_3dig ${count})
	mv -v ${file} $dir/recsis${tarName}_${scount}.root
    done
done
