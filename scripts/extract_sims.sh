#!/bin/bash

############################################
#                                          #
#  Script made to extract simulations,     #
#      from volatile/ to work/             #
#                                          #
############################################

function print_help() {
    echo "SCRIPT: extract_sims.sh"
    echo "======================="
    echo "./extract_sims.sh --part <part> --targ <targ> --run1 <run1> --run2 <run2>"
    echo "Where:"
    echo "  <part> = selects particle (eta, omega)"
    echo "  <targ> = selects target (D, C, Fe, Pb)"
    echo "  <run1> = first run number to loop over"
    echo "  <run2> = last run number to loop over"
    echo "Example:"
    echo "  ./extract_sims.sh --part omega --targ D --run1 1 --run2 2500"
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
        elif [[ "${arr[$ic]}" == "--run1" ]]; then
            run1=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--run2" ]]; then
            run2=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}.";
            print_help;
        fi
        ((ic+=2))
    done
}

function print_args() {
    echo "SCRIPT: extract_sims.sh"
    echo "======================="
    echo "part  = ${part}"
    echo "targ  = ${targ}"
    echo "run1  = ${run1}"
    echo "run2  = ${run2}"
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

if [[ -z "${VLTLDIR}" ]]; then
    echo "ERROR: variable VLTLDIR is unset."
    exit
fi

if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: variable WORKDIR is unset."
    exit
fi

NARGS=8
if [[ ${#} -ne ${NARGS} ]]; then
    echo "ERROR: ${#} arguments were provided, they should be ${NARGS}."
    print_help
fi

argArray=("$@")
process_args "${argArray[@]}"
print_args

in_path=${VLTLDIR}/${part}Sim/farm/${targ}
out_path=${WORKDIR}/${part}Sim/${targ}

for ((i=${run1}; i<=${run2}; i++)); do
    string_i="$(get_number_4dig ${i})"
    mkdir -vp ${out_path}/${string_i:0:2}/
    mv -v ${in_path}/run${string_i}/clastool/recsis${targ}.root ${out_path}/${string_i:0:2}/recsisD_${string_i:2:2}.root
done

# clean after extracting
for ((i=${run1}; i<=${run2}; i++)); do
    string_i="$(get_number_4dig ${i})"
    rm -rvf ${in_path}/run${string_i}
done

# clean corrupted files
find ${out_path}/ -name *.root -size -50k -delete
