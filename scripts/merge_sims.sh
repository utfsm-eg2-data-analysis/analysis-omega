#!/bin/bash

############################################
#                                          #
#  Script made to merge extracted          #
#       simulations in work/               #
#                                          #
############################################

function print_help() {
    echo "SCRIPT: merge_sims.sh"
    echo "======================="
    echo "./merge_sims.sh --part <part> --targ <targ>"
    echo "Where:"
    echo "  <part> = selects particle (eta, omega)"
    echo "  <targ> = selects target (D, C, Fe, Pb)"
    echo "Example:"
    echo "  ./merge_sims.sh --part omega --targ D"
    exit
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--part" ]]; then
            part=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--targ" ]]; then
            targ=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}.";
            print_help;
        fi
        ((ic+=2))
    done
}

function print_args() {
    echo "SCRIPT: merge_sims.sh"
    echo "====================="
    echo "part  = ${part}"
    echo "targ  = ${targ}"
}


function get_number_4dig() {
    sr=$1
    srn=""
    if [[ ${sr} -lt 10 ]]; then
        srn="000${sr}"
    elif [[ ${sr} -lt 100 ]]; then
        srn="00${sr}"
    elif [[ ${sr} -lt 1000 ]]; then
        srn="0${sr}"
    else
        srn="${sr}"
    fi
    echo ${srn}
}

################
###   Main   ###
################

if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: variable WORKDIR is unset."
    exit
fi

NARGS=4
if [[ ${#} -ne ${NARGS} ]]; then
    echo "ERROR: ${#} arguments were provided, they should be ${NARGS}."
    print_help
fi

argArray=("$@")
process_args "${argArray[@]}"
print_args

in_path=${WORKDIR}/${part}Sim/${targ}

for dir in ${in_path}/*/; do
    dir_number=${dir:(-3):2} # slice path from right to left
    hadd ${in_path}/recsisD_${dir_number}.root ${dir}/recsis${targ}_*.root
done

# clean after merging
for dir2 in ${in_path}/*/; do
    rm -rvf ${dir2}
done
