#!/bin/bash

##################################################
# ./request_sim.sh <set> <target>                #
#     <set> = (old, usm, jlab)                   #
#     <target> = (D, C, Fe, Pb)                  #
#                                                #
# EG: ./request_sim.sh old Fe                    #
##################################################

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

INPUTARRAY=("$@")

SETOPTION="${INPUTARRAY[0]}"
TARGET="${INPUTARRAY[1]}"

if [[ "${SETOPTION}" == "jlab" ]]; then

    TAPEDIR=/mss/clas/eg2a/production/Simulation/omega_lepto/${TARGET}

    NDIRS=$(ls -1 ${TAPEDIR} | wc -l)

    for ((n = 0; n < ${NDIRS}; n++)); do
	sn=$(get_num_2dig $n)
	cd $TAPEDIR/$sn
	for file in *.root; do
	    sfile=$(readlink -f $file)
	    sfile=${sfile##/w} # just in case
            jcache get $sfile
	done
    done

else

    TAPEDIR=/mss/clas/eg2a/production/Simulation/omega_lepto/${SETOPTION}/${TARGET}

    cd $TAPEDIR
    for file in *.root; do
	sfile=$(readlink -f $file)
	sfile=${sfile##/w} # just in case
        jcache get $sfile
    done

fi
