#!/bin/bash

##############################################################
# ./send-10_split.sh                                         #
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

source ~/.bashrc
cd ${PRODIR}/sh/jlab

./send_split.sh D 001 01
./send_split.sh D 001 02
./send_split.sh D 001 03
./send_split.sh D 001 04

./send_split.sh C 001 01
./send_split.sh C 001 02

./send_split.sh Fe 001 01
./send_split.sh Fe 001 02

./send_split.sh Pb 001 01
./send_split.sh Pb 001 02
