#!/bin/bash

############################################################################################
# ./run_FilterNCombine.sh --targ <target> --set <set> --n <ndir> --run1 <rn> --run2 <rn>   #
#     <target> = (D, C, Fe, Pb)                                                            #
#     <set>    = (data, old, usm, jlab)                                                    #
#     <ndir>   = (00, 01, 02, ...)                                                         #
#     <rn>     = (1, ..., 9999) (sim)                                                      #
#                (42011, ...)   (data)                                                     #
#                                                                                          #
# EG: ./run_FilterNCombine.sh --targ C --set data --rn 42011                               #
#     ./run_FilterNCombine.sh --targ D --set jlab --n 06 -rn 6666                          #
#     ./run_FilterNCombine.sh --targ Fe --set old -rn 132                                  #
############################################################################################

####
# Functions
##

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

####
# Main
##

inputArray=("$@")

ic=0
while [ $ic -le $((${#inputArray[@]}-1)) ]; do
  if [ "${inputArray[$ic]}" == "--targ" ]; then
    tarName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--set" ]; then
    setName=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--n" ]; then
    nDir=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--run1" ]; then
    runNumber1=${inputArray[$((ic+1))]}
  elif [ "${inputArray[$ic]}" == "--run2" ]; then
    runNumber2=${inputArray[$((ic+1))]}
  else
    printf "*** Aborting: Unrecognized argument: ${inputArray[$((ic))]}. ***\n\n";
  fi
  ((ic+=2))
done

cd ${PRODIR}

if [[ ${setName} = "data" ]]; then
  OUDIR=${PRODIR}/out/filterData/${tarName}
  opt="-t${tarName} -d"
elif [[ ${setName} = "jlab" ]]; then
  OUDIR=${PRODIR}/out/filterSim/${setName}/${tarName}/${nDir}
  opt="-t${tarName} -S${setName} -n${nDir}"
else
  OUDIR=${PRODIR}/out/filterSim/${setName}/${tarName}
  opt="-t${tarName} -S${setName}"
fi

# Set environment variables
source ~/.bashrc

for (( ir=$runNumber1; ir<=$runNumber2; ir++ )); do
  srun=$(get_run "$ir")

  TMPDIR="${PRODIR}/tmp/FNC"
  mkdir -p ${TMPDIR}
  jobfile="${TMPDIR}/job_${setName}${tarName}_${srun}.sh"
  jobname="FNC_${setName}-${tarName}_${srun}"
  
  echo "#!/bin/bash"                                > $jobfile
  echo "#PBS -N ${jobname}"                        >> $jobfile
  echo "#PBS -V"                                   >> $jobfile
  echo "#PBS -q utfsm"                             >> $jobfile
  echo "#PBS -l walltime=06:00:00"                 >> $jobfile
  echo "#PBS -l cput=06:00:00"                     >> $jobfile
  echo "#PBS -m ae"                                >> $jobfile
  echo "#PBS -M andres.borquez.14@sansano.usm.cl"  >> $jobfile
  echo ""                                          >> $jobfile
  echo "cd ${PRODIR}"                              >> $jobfile
  echo "./bin/FilterNCombine ${opt} -r${srun}"     >> $jobfile
  
  echo "Submitting job $jobfile..."
  qsub $jobfile
done
