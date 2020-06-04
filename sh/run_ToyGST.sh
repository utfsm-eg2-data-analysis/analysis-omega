#!/bin/bash

################################
# ./run_ToyGST.sh <target>     #
#     <target> = (C, Fe, Pb)   #
#                              #
# EG: ./run_GST-data.sh Pb     #
################################

# only for utfsm cluster
# for data (by now)

tarName="$@"

if [[ ${tarName} = "C" ]]; then
  rnlist=${PRODIR}/include/C-thickD2rn.txt
elif [[ ${tarName} = "Fe" ]]; then
  rnlist=${PRODIR}/include/Fe-thickD2rn.txt
elif [[ ${tarName} = "Pb" ]]; then
  rnlist=${PRODIR}/include/Pb-thinD2rn.txt
fi

OUDIR=${PRODIR}/out/ToyGST/data/${tarName}
mkdir -p ${OUDIR}
mkdir -p ${OUDIR}/tmp

# set environment variables
source ~/.bashrc

cd ${PRODIR}

lines=`wc -l < ${rnlist}`

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
  let COUNTER=COUNTER+1
  rn=`sed -n "$COUNTER{p;q}" ${rnlist}`

  jobfile="${OUDIR}/tmp/ToyGST_data${tarName}_${rn}.sh"
  jobname="ToyGST_data${tarName}_${rn}"

  echo ${jobname}

  echo "#!/bin/bash"                                    > ${jobfile}
  echo "#PBS -N ${jobname}"                            >> ${jobfile}
  echo "#PBS -V"                                       >> ${jobfile}
  echo "#PBS -q utfsm"                                 >> ${jobfile}
  echo "#PBS -l walltime=24:00:00"                     >> ${jobfile}
  echo "#PBS -l cput=24:00:00"                         >> ${jobfile}
  echo "#PBS -m ae"                                    >> ${jobfile}
  echo "#PBS -M andres.borquez.14@sansano.usm.cl"      >> ${jobfile}
  echo ""                                              >> ${jobfile}
  echo "cd ${PRODIR}"                                  >> ${jobfile}
  echo "./bin/ToyGST -d -t${tarName} -r${rn}"          >> ${jobfile}

  echo "Submitting job ${jobfile}..."
  qsub $jobfile
done
