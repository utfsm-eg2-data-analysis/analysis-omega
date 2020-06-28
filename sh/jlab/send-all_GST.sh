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
./send_GST.sh data C
./send_GST.sh data Fe
./send_GST.sh data Pb

# Simulations/old
./send_GST.sh old C
./send_GST.sh old Fe

# Simulations/usm
./send_GST.sh usm D
./send_GST.sh usm C
./send_GST.sh usm Fe
./send_GST.sh usm Pb

# Simulations/jlab
targets=("D" "C" "Fe" "Pb")
ndirs=(46 10 13 4)
for ((i=0; i < ${#targets[@]}; i++)); do
    for ((j=1; j <= ${ndirs[i]}; j++)); do
	ndir=$(get_num "$j")
        ./send_GST.sh jlab ${targets[i]} ${ndir}
    done
done
