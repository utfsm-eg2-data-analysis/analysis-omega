#!/bin/bash

###############################################################################################
# ./run_MakeRooFits_SS.sh --bkg <bkgOpt> --kinvar <kinvarOpt> --mean <mean> --width <width>   #
#     (SS stands for Sigma Studies!)                                                          #
#     <kinvarOpt> = (Z, Pt2, Q2, Nu)                                                          #
#     <bkgOpt> = (1, 2)                                                                       #
#     <mean> = (float value) (it will get multiplied by 10^-3)                                #
#     <width> = (float value) (it will get multiplied by 10^-3)                               #
#                                                                                             #
# EG: ./run_MakeRooFits_SS.sh --bkg 1 --kinvar Z --mean 24 --width 2                          #
###############################################################################################

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--bkg" ]; then
    bkgOpt=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--kinvar" ]; then
    kinvarOpt=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--mean" ]; then
    mean=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--width" ]; then
    width=${inputArray[$((ic+1))]}
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
  ./bin/MakeRooFits -tD -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width} -S
  ./bin/MakeRooFits -tD -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width}

  # Carbon
  ./bin/MakeRooFits -tC -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width} -S
  ./bin/MakeRooFits -tC -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width}

  # Iron
  ./bin/MakeRooFits -tFe -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width} -S
  ./bin/MakeRooFits -tFe -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width}

  # Lead
  ./bin/MakeRooFits -tPb -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width} -S
  ./bin/MakeRooFits -tPb -${kinvarOpt}${COUNTER} -b${bkgOpt} -C${mean} -c${width}

  let COUNTER=COUNTER+1
done


