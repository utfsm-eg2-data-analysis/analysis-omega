#!/bin/bash

################################
# ./run_CEC.sh <target>        #
#     <target> = (C, Fe, Pb)   #
#                              #
# EG: ./run_CEC.sh Pb          #
################################

# only for utfsm cluster

tarName="$@"

if [[ ${tarName} = "C" ]]; then
  rnlist=${PRODIR}/include/C-thickD2rn.txt
elif [[ ${tarName} = "Fe" ]]; then
  rnlist=${PRODIR}/include/Fe-thickD2rn.txt
elif [[ ${tarName} = "Pb" ]]; then
  rnlist=${PRODIR}/include/Pb-thinD2rn.txt
fi

OUDIR=${PRODIR}/out/CheckElectronCut
mkdir -p ${OUDIR}
mkdir -p ${OUDIR}/tmp

# set environment variables
source ~/.bashrc

cd ${PRODIR}

lines=`wc -l < ${rnlist}`

COUNTER=0
while [ ${COUNTER} -lt ${lines} ]; do
  let COUNTER=COUNTER+1
  rn=`sed -n "$COUNTER{p;q}" ${rnlist}`

  jobfile="${OUDIR}/tmp/cec_${tarName}_${rn}.sh"
  jobname="CEC_${tarName}_${rn}"

  echo ${jobname}

  echo "#!/bin/bash"                                    > ${jobfile}
  echo "#PBS -N ${jobname}"                            >> ${jobfile}
  echo "#PBS -V"                                       >> ${jobfile}
  echo "#PBS -q utfsm"                                 >> ${jobfile}
  echo "#PBS -l walltime=01:00:00"                     >> ${jobfile}
  echo "#PBS -l cput=01:00:00"                         >> ${jobfile}
  echo "#PBS -m ae"                                    >> ${jobfile}
  echo "#PBS -M andres.borquez.14@sansano.usm.cl"      >> ${jobfile}
  echo ""                                              >> ${jobfile}
  echo "cd ${PRODIR}"                                  >> ${jobfile}
  echo "./bin/CheckElectronCuts -t${tarName} -r${rn}"  >> ${jobfile}

  echo "Submitting job ${jobfile}..."
  qsub $jobfile
done
