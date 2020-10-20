#!/bin/bash

##############################################################
# ./send_GF_Sim.sh <set> <target> <ndir>                     #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_GF_Sim.sh old Fe                                #
#     ./send_GF_Sim.sh usm D                                 #
#     ./send_GF_Sim.sh jlab Pb 00                            #
##############################################################

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

setOption="${inputArray[0]}"
tarName="${inputArray[1]}"
nDir="${inputArray[2]}"

#####
# Main
###

# set env
source ~/.bashrc

# define important dirs
WORKDIR=/home/borquez/work
TMPDIR=${WORKDIR}/tmp
if [[ "$setOption" == "jlab" ]]; then
    XMLDIR=${TMPDIR}/xml/${setOption}/${tarName}/${nDir}
    LOGDIR=${TMPDIR}/log/${setOption}/${tarName}/${nDir}
    GSTDIR=${WORKDIR}/GetSimpleTuple/${setOption}/${tarName}/${nDir}
    FNCDIR=${WORKDIR}/FilterNCombine/${setOption}/${tarName}/${nDir}
    INDIR=${WORKDIR}/simulations-omega/jlab/${tarName}/${nDir}
else
    XMLDIR=${TMPDIR}/xml/${setOption}/${tarName}
    LOGDIR=${TMPDIR}/log/${setOption}/${tarName}
    GSTDIR=${WORKDIR}/GetSimpleTuple/${setOption}/${tarName}
    FNCDIR=${WORKDIR}/FilterNCombine/${setOption}/${tarName}    
    INDIR=${WORKDIR}/simulations-omega/${setOption}/${tarName}
fi
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
    if [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num_2dig $(($COUNTER-1)) ) # rn starts at 00
    else
	rn=$(get_num_2dig $COUNTER) # starts at 01
    fi

    # setting jobname
    if [[ "${setOption}" == "jlab" ]]; then
	jobname="GF_${setOption}-${tarName}-${nDir}_${rn}"
    else
	jobname="GF_${setOption}-${tarName}_${rn}"
    fi
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
    execfile="${PRODIR}/sh/jlab/run_GF_Sim.sh"
    echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple\"/>"                  >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
    echo "  <Input src=\"${execfile}\"    dest=\"run_GF_Sim.sh\"/>"                   >> ${jobfile}
    inrootfile="${INDIR}/recsis${tarName}_${rn}.root"
    echo "  <Input src=\"${inrootfile}\" dest=\"recsis${tarName}_${rn}.root\"/>"      >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_GF_Sim.sh"              >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\"                run_GF_Sim.sh"              >> ${jobfile}
    echo "    chmod 755 ./run_GF_Sim.sh"                                              >> ${jobfile}
    echo "    sh run_GF_Sim.sh"                                                       >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${GSTDIR}/pruned${tarName}_${rn}.root"
    outrootfile2="${FNCDIR}/comb${tarName}_${rn}.root"
    echo "  <Output src=\"pruned${tarName}_${rn}.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
    echo "  <Output src=\"comb${tarName}_${rn}.root\"   dest=\"${outrootfile2}\"/>"   >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
