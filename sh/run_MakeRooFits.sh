#!/bin/bash

##################################################################################
# ./run_MakeRooFits.sh  --kinvar <kinvarOpt> --signal <signalOpt> --bkg <bkgOpt> #
#     <kinvarOpt> = (Z, Pt2, Q2, Nu)                                             #
#     <signalOpt> = (g, bw)                                                      #
#     <bkgOpt>    = (1, 2)                                                       #
#                                                                                #
# EG: ./run_MakeRooFits.sh --kinvar Pt2 --signal g --bkg 1                       #
##################################################################################

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--bkg" ]; then
    bkgOpt=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--signal" ]; then
    signalOpt=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--kinvar" ]; then
    kinvarOpt=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

COUNTER=1
END=5

if [[ ${kinvarOpt} = "Z" ]]; then
  kinvarOpt="z"
  COUNTER=3
  END=7
elif [[ ${kinvarOpt} = "Pt2" ]]; then
  kinvarOpt="p"
elif [[ ${kinvarOpt} = "Q2" ]]; then
  kinvarOpt="q"
elif [[ ${kinvarOpt} = "Nu" ]]; then
  kinvarOpt="n"
fi

cd ${PRODIR}
./bin/MakeRooFits -h

while [ ${COUNTER} -le ${END} ]; do
  # Deut
  ./bin/MakeRooFits -tD -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt} -S
  ./bin/MakeRooFits -tD -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt}

  # Carbon
  ./bin/MakeRooFits -tC -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt} -S
  ./bin/MakeRooFits -tC -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt}

  # Iron
  ./bin/MakeRooFits -tFe -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt} -S
  ./bin/MakeRooFits -tFe -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt}

  # Lead
  ./bin/MakeRooFits -tPb -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt} -S
  ./bin/MakeRooFits -tPb -${kinvarOpt}${COUNTER} -F${signalOpt} -b${bkgOpt}

  let COUNTER=COUNTER+1
done


