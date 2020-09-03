#!/bin/bash

##############################################################
# ./send-all_FNC.sh <target>                                 #
#     <target> = (D, C, Fe, Pb)                              #
#                                                            #
# EG: ./send-all_FNC.sh C                                    #
##############################################################

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
##

tarName="$@"

source ~/.bashrc
cd ${PRODIR}/sh/jlab

# Data
# ./send_FNC.sh data C
# ./send_FNC.sh data Fe
# ./send_FNC.sh data Pb

# Simulations/old
# ./send_FNC.sh old C
# ./send_FNC.sh old Fe
 
# Simulations/usm
# ./send_FNC.sh usm D
# ./send_FNC.sh usm C
# ./send_FNC.sh usm Fe
# ./send_FNC.sh usm Pb

# Simulations/jlab
if [[ "$tarName" == "D" ]]; then
    totalDirs=46
elif [[ "$tarName" == "C" ]]; then
    totalDirs=10
elif [[ "$tarName" == "Fe" ]]; then
    totalDirs=13
elif [[ "$tarName" == "Pb" ]]; then
    totalDirs=4
fi

for ((j=1; j <= ${totalDirs}; j++)); do
    ndir=$(get_num_3dig $j)
    ./send_FNC.sh jlab ${tarName} ${ndir}
done
