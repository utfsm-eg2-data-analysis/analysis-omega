#!/bin/bash

####################################
# ./bulk-split.sh <target>        #
#                                #
# target: D, C, Fe, Pb          #
#                              #
###############################

# Splits simulation files, moves them into new directories and renames them
# (exlusive for JLAB cluster)

#####
# Functions
###

function get_num()
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
# Input
###

tarName="$@"

#####
# Main
###

# set env
source ~/.bashrc

topdir=/home/borquez/volatile/omegaSim/output/$tarName
newtopdir=/home/borquez/volatile/omegaSim/output/$(echo "${tarName}2")

cd $topdir
mkdir -p $newtopdir

# simulations@jlab
counter1=1
counter2=2
counter3=3
for dir in */; do
    cd $dir
    dir1=$newtopdir/$(get_num $counter1)
    mkdir -p $dir1
    dir2=$newtopdir/$(get_num $counter2)
    mkdir -p $dir2
    dir3=$newtopdir/$(get_num $counter3)
    mkdir -p $dir3
    for file in *.root; do
	sh /home/borquez/volatile/hsplit/hsplit.sh --B 115500 $file
        basename=${file//.*/}
	# first file
	file1=$(echo "${basename}_01.root")
        mv $file1 $dir1
	# second file
	file2=$(echo "${basename}_02.root")
        mv $file2 $dir2
	# third file	
	file3=$(echo "${basename}_03.root")
        mv $file3 $dir3
    done
    ((counter1+=3))
    ((counter2+=3))
    ((counter3+=3))
done
