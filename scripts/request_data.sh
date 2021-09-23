#!/bin/bash

##################################################
# ./request_data.sh <target>                     #
#     <target> = (C, Fe, Pb)                     #
#                                                #
# EG: ./request_data.sh Fe                       #
##################################################

TARNAME="$@"

DATADIR=/mss/clas/eg2a/production/Pass2/Clas

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${HOME}/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${HOME}/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${HOME}/Pb-thinD2rn.txt
fi
TOTALRN=$(wc -l < ${RNLIST}) # total number of run numbers

for ((COUNTER=1; COUNTER <= ${TOTALRN}; COUNTER++)); do
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # update run number
    jcache get ${DATADIR}/clas_${RN}*
done
