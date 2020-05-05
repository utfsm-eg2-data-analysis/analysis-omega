#!/bin/bash

############################################################################################
# ./run_FilterNCombine.sh --targ <target> --set <set> --run1 <rn> --run2 <rn>              #
#     <target> = (D, C, Fe, Pb)                                                            #
#     <set>    = (data, old, usm)                                                          #
#     <rn>     = (1, ..., 9999) (sim)                                                      #
#                (42011, ...)   (data)                                                     #
#                                                                                          #
# EG: ./run_FilterNCombine.sh --targ C --set data --rn 42011                               #
#     ./run_FilterNCombine.sh --targ Fe --set old -rn 132                                  #
#                                                                                          #
############################################################################################
#                                                                                          #
# New version: "I can NOT send more than 600 jobs..."                                      #
# --- It doesn't work in jlab cluster, only for utfsm cluster                              #
# --- It's set to run the remaining jobs for all the usm set (run1=0, run2~150)            #
# --- Only works for sim: old and usm                                                      #
#                                                                                          #
############################################################################################

#####
# Functions
###

function get_run()
{
  sr=$1
  srn=""
  if [ $sr -lt 10 ]; then
    srn="000$sr"
  elif [ $sr -lt 100 ]; then
    srn="00$sr"
  elif [ $sr -lt 1000 ]; then
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
  if [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--set" ]; then
    setName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--run1" ]; then
    runNumber1=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--run2" ]; then
    runNumber2=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

TMPDIR="${PRODIR}/tmp/FNC"
mkdir -p ${TMPDIR}
cd ${TMPDIR}

if [[ ${setName} = "data" ]]; then
  OUDIR=${PRODIR}/out/filterData/${tarName}
  opt="-t${tarName} -d"
elif [[ ${setName} = "usm" ]]; then
  OUDIR=${PRODIR}/out/filterSim/${setName}/${tarName}
  opt="-t${tarName} -S${setName}"
  if [[ ${tarName} = "D" ]]; then
    runStart=377
    runStep=8
  elif [[ ${tarName} = "C" ]]; then
    runStart=195      
    runStep=8
  elif [[ ${tarName} = "Fe" ]]; then
    runStart=58
    runStep=8
  elif [[ ${tarName} = "Pb" ]]; then
    runStart=117
    runStep=12
  fi
fi

# Set environment variables
source ~/.bashrc

for (( ir=$runNumber1; ir<=$runNumber2; ir++ )); do
  srun=$(get_run "$ir")

  jobfile="${TMPDIR}/job_${setName}${tarName}_${srun}.sh"
  jobname="FNC_${setName}-${tarName}_${srun}"

  echo ${jobname}

  echo "#!/bin/bash"                                > $jobfile
  echo "#PBS -N ${jobname}"                        >> $jobfile
  echo "#PBS -V"                                   >> $jobfile
  echo "#PBS -q utfsm"                             >> $jobfile
  echo "#PBS -l walltime=24:00:00"                 >> $jobfile
  echo "#PBS -l cput=24:00:00"                     >> $jobfile
  echo "#PBS -m ae"                                >> $jobfile
  echo "#PBS -M andres.borquez.14@sansano.usm.cl"  >> $jobfile
  echo ""                                          >> $jobfile
  echo "cd ${PRODIR}"                              >> $jobfile
  
  runStart2=$((runStart+1+ir*runStep))
  for (( ik=$runStart2; ik<$((runStart2+runStep)); ik++ )); do
    sik=$(get_run "$ik")
    echo "./bin/FilterNCombine ${opt} -r${sik}"     >> $jobfile
  done

  echo "Submitting job $jobfile..."
  #qsub $jobfile
done
