#!/bin/bash

# This script sends everything!

#####
# Functions
###

function get_num()
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

# Data
./send_FNC.sh data C
./send_FNC.sh data Fe
./send_FNC.sh data Pb

# Simulations/old
./send_FNC.sh old C
./send_FNC.sh old Fe
 
# Simulations/usm
./send_FNC.sh usm D
./send_FNC.sh usm C
./send_FNC.sh usm Fe
./send_FNC.sh usm Pb

# Simulations/jlab
targets=("D" "C" "Fe" "Pb")
ndirs=(46 10 13 4)
for ((i=0; i < ${#targets[@]}; i++)); do
    for ((j=1; j <= ${ndirs[i]}; j++)); do
	ndir=$(get_num "$j")
        ./send_FNC.sh jlab ${targets[i]} ${ndir}
    done
done
