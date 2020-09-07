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

inputOption=
tarName=
rn=

for ((counter=1; counter <= 35; counter++)); do
    scounter=$(get_num_dig2 $counter)
    ./FilterNCombine${inputOption} -t${tarName} -r${rn}_${scounter}
done
