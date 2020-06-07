#!/bin/bash

#################################################################
# ./run_ToyGST-Sim.sh <set> <target>                            #
#     <target> = (D, C, Fe, Pb)                                 #
#     <set> = (old, usm, jlab)                                  #
#                                                               #
# EG: ./run_ToyGST-Sim.sh data C                                #
#     ./run_ToyGST-Sim.sh old Fe                                #
#     ./run_ToyGST-Sim.sh usm D                                 #
#################################################################

#####
# Functions
###

function get_num()
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

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "data" ]; then
    setName=${inputArray[$((ic))]}
    tarName=${inputArray[$((ic+1))]}
    inputOption="d"
  elif [ "${inputArray[$ic]}" == "old" ]; then
    setName=${inputArray[$((ic))]}
    tarName=${inputArray[$((ic+1))]}
    inputOption="S${setName}"
  elif [ "${inputArray[$ic]}" == "usm" ]; then
    setName=${inputArray[$((ic))]}
    tarName=${inputArray[$((ic+1))]}
    inputOption="S${setName}"
  else
    printf "\n*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. Please, check usage box inside code. ***\n\n";
  fi
  ((ic+=2))
done

# set env
source ~/.bashrc

cd ${PRODIR}

OUDIR=${PRODIR}/out/ToyGST/${setName}/${tarName}
mkdir -p ${OUDIR}
mkdir -p ${OUDIR}/tmp

# how to obtain the run numbers
SIMDIR=/eos/user/b/borquez/omegaSim
if [ "${setName}" == "data" ]; then
    if [[ ${tarName} = "C" ]]; then
	rnlist=${PRODIR}/include/C-thickD2rn.txt
    elif [[ ${tarName} = "Fe" ]]; then
	rnlist=${PRODIR}/include/Fe-thickD2rn.txt
    elif [[ ${tarName} = "Pb" ]]; then
	rnlist=${PRODIR}/include/Pb-thinD2rn.txt
    fi
    lines=`wc -l < ${rnlist}`
elif [ "${setName}" == "old" ]; then
    if [[ ${tarName} = "C" ]]; then
	lines=2
    elif [[ ${tarName} = "Fe" ]]; then
	lines=1
    fi
elif [ "${setName}" == "usm" ]; then
    if [[ ${tarName} = "D" ]]; then
	lines=16
    elif [[ ${tarName} = "C" ]]; then
	lines=14
    elif [[ ${tarName} = "Fe" ]]; then
	lines=13
    elif [[ ${tarName} = "Pb" ]]; then
	lines=19
    fi
fi

COUNTER=0
while [ ${COUNTER} -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    if [ "${setName}" == "data" ]; then
	rn=`sed -n "$COUNTER{p;q}" ${rnlist}` # data starts from 1 (due to line number)
    else
	rn=$(get_num "$((COUNTER-1))") # sim starts from 00 (due to filenames)
    fi

    jobfile="${OUDIR}/tmp/ToyGST_${setName}${tarName}_${rn}.sh"
    jobname="GST_${setName}${tarName}_${rn}"
    
    echo ${jobname}
    
    echo "#!/bin/bash"                                        > ${jobfile}
    echo "#PBS -N ${jobname}"                                >> ${jobfile}
    echo "#PBS -V"                                           >> ${jobfile}
    echo "#PBS -q utfsm"                                     >> ${jobfile}
    echo "#PBS -l walltime=24:00:00"                         >> ${jobfile}
    echo "#PBS -l cput=24:00:00"                             >> ${jobfile}
    echo "#PBS -m ae"                                        >> ${jobfile}
    echo "#PBS -M andres.borquez.14@sansano.usm.cl"          >> ${jobfile}
    echo ""                                                  >> ${jobfile}
    echo "cd ${PRODIR}"                                      >> ${jobfile}
    echo "./bin/ToyGST -${inputOption} -t${tarName} -r${rn}" >> ${jobfile}
    
    echo "Submitting job ${jobfile}"
    # qsub $jobfile
done

