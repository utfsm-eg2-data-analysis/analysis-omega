#!/bin/bash

#################################################
# ./send_GF_BkgSim.sh <version> <ndir>          #
#     <version> = (v1, v2)                      #
#     <ndir>    = (00, 01, 02, ...)             #
#                                               #
# EG: ./send_GF_BkgSim.sh v2 00                 #
#################################################

#####
# Functions
###

function get_num_2dig()
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
# Input
###

inputArray=("$@")

nVer="${inputArray[0]}"
nDir="${inputArray[1]}"

#####
# Main
###

# set env
source ~/.bashrc

# define important dirs
WORKDIR=/home/borquez/work
TMPDIR=${WORKDIR}/tmp
XMLDIR=${TMPDIR}/xml/bkg/${nVer}/D/${nDir}
LOGDIR=${TMPDIR}/log/bkg/${nVer}/D/${nDir}
GSTDIR=${WORKDIR}/GetSimpleTuple/bkg/${nVer}/D/${nDir}
FNCDIR=${WORKDIR}/FilterNCombine/bkg/${nVer}/D/${nDir}
INDIR=${WORKDIR}/simulations-bkg/${nVer}/D/${nDir}

mkdir -p ${TMPDIR}
mkdir -p ${XMLDIR} ${LOGDIR}
mkdir -p ${GSTDIR} ${FNCDIR}

# obtain run numbers
nfiles=$(ls -1 ${INDIR} | wc -l)

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="2" # hours
jobspace="2" # GB
jobmemory="2" # GB

for ((COUNTER=1; COUNTER <= $nfiles; COUNTER++)); do
    # update rn value
    rn=$(get_num_2dig $(($COUNTER-1)) ) # rn starts at 00

    # setting jobname
    jobname="GF_bkg-D-${nDir}_${rn}"
    jobfile="${XMLDIR}/${jobname}.xml"

    echo ${jobname}

    echo "<Request>"                                                                   > ${jobfile}
    echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
    echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
    echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
    echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
    echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
    echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
    echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
    echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
    echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
    # set inputs
    thebinary1="${PRODIR}/bin/GetSimpleTuple"
    thebinary2="${PRODIR}/bin/FilterNCombine_sim"
    execfile="${PRODIR}/sh/jlab/run_GF_Sim.sh" # same as GF_Sim
    echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple\"/>"                  >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
    echo "  <Input src=\"${execfile}\"    dest=\"run_GF_Sim.sh\"/>"                   >> ${jobfile}
    inrootfile="${INDIR}/recsisD_${rn}.root"
    echo "  <Input src=\"${inrootfile}\"  dest=\"recsisD_${rn}.root\"/>"              >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=D|g\" run_GF_Sim.sh"                       >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\"       run_GF_Sim.sh"                       >> ${jobfile}
    echo "    chmod 755 ./run_GF_Sim.sh"                                              >> ${jobfile}
    echo "    sh run_GF_Sim.sh"                                                       >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${GSTDIR}/prunedD_${rn}.root"
    outrootfile2="${FNCDIR}/combD_${rn}.root"
    echo "  <Output src=\"prunedD_${rn}.root\" dest=\"${outrootfile1}\"/>"            >> ${jobfile}
    echo "  <Output src=\"combD_${rn}.root\"   dest=\"${outrootfile2}\"/>"            >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
