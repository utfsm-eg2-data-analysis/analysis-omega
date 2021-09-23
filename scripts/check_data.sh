#!/bin/bash

##################################################
# ./check_data.sh <target>                       #
#     <target> = (C, Fe, Pb)                     #
#                                                #
# EG: ./check_data.sh Fe                         #
##################################################

TARNAME="$@"

TAPEDIR=/mss/clas/eg2a/production/Pass2/Clas
CACHEDIR=/cache/${TAPEDIR}

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${HOME}/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${HOME}/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${HOME}/Pb-thinD2rn.txt
fi
TOTALRN=$(wc -l < ${RNLIST}) # total number of run numbers

echo "----- : CACHE : TAPE"
for ((COUNTER=1; COUNTER <= ${TOTALRN}; COUNTER++)); do
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # update run number
    CACHEN=$(ls -1 ${CACHEDIR}/clas_${RN}* | wc -l)
    TAPEN=$(ls -1 ${TAPEDIR}/clas_${RN}* | wc -l)
    echo "${RN} : ${CACHEN}    : ${TAPEN}"
done
