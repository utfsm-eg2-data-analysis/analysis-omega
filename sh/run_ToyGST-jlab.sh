#!/bin/bash

#################################################################
# ./run_ToyGST-jlab.sh <target> <ndir>                          #
#     <target> = (D, C, Fe, Pb)                                 #
#     <ndir>   = integer(00, 01, 02, ...)                       #
#                                                               #
# EG: ./run_ToyGST-Sim.sh C 09                                  #
#     ./run_ToyGST-Sim.sh Fe 04                                 #
#     ./run_ToyGST-Sim.sh D 35                                  #
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

tarName=${inputArray[$((0))]}
nDir=${inputArray[$((1))]}

# set env
source ~/.bashrc

cd ${PRODIR}

# define important dirs
XMLDIR=${PRODIR}/xml/${tarName}/${nDir}
mkdir -p ${XMLDIR}
SIMDIR=/home/borquez/volatile/omegaSim
OUDIR=${PRODIR}/out/ToyGST/jlab/${tarName}/${nDir}
mkdir -p ${OUDIR}
INDIR=${SIMDIR}/output/${tarName}/${nDir}

# obtain the last run number
lines=`ls -1 ${INDIR} | wc -l`

# testing...
#jobfile=
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis"
jobos="general"
#jobname=
jobtime="30"
jobspace="1"
jobmemory="1"
thebinary="${PRODIR}/bin/ToyGST"
#inrootfile=
#outrootfile=
execfile="${PRODIR}/sh/ToyGST-jlab.sh"

# handling exceptions
if [[ "${tarName}" == "D" && "${nDir}" == "00" ]]; then
    COUNTER=6
elif [[ "${tarName}" == "C" && "${nDir}" == "00" ]]; then
    COUNTER=6
elif [[ "${tarName}" == "Fe" && "${nDir}" == "00" ]]; then
    COUNTER=6
else
    COUNTER=0
fi
	
while [ ${COUNTER} -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    rn=$(get_num "$((COUNTER-1))") # start at (06, 06, 06, 00) respectively
    # rn=$(get_num "99") # test

    jobname="GST_${tarName}-${nDir}_${rn}"
    jobfile="${XMLDIR}/${jobname}.xml"
    inrootfile="${INDIR}/recsis${tarName}_${rn}.root"
    outrootfile="${OUDIR}/pruned${tarName}_${rn}.root"

    echo ${jobname}

    echo "<Request>"                                                                   > ${jobfile}
    echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
    echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
    echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
    echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
    echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
    echo "  <TimeLimit time=\"${jobtime}\" unit=\"minutes\"/>"                        >> ${jobfile}
    echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
    echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
    echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
    echo "  <Input src=\"${thebinary}\"  dest=\"ToyGST\"/>"                           >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"ToyGST-jlab.sh\"/>"                   >> ${jobfile}
    echo "  <Input src=\"${inrootfile}\" dest=\"recsis${tarName}_${rn}.root\"/>"      >> ${jobfile}
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\"  ToyGST-jlab.sh"            >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\"                 ToyGST-jlab.sh"            >> ${jobfile}
    echo "    chmod 755 ./ToyGST-jlab.sh"                                             >> ${jobfile}
    echo "    sh ToyGST-jlab.sh"                                                      >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    echo "  <Output src=\"pruned${tarName}_${rn}.root\" dest=\"${outrootfile}\"/>"    >> ${jobfile}
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job ${jobfile}"
    jsub --xml ${jobfile}
done
