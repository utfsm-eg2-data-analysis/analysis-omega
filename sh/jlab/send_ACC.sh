#!/bin/bash

##############################################################
# ./send_ACC.sh <set> <target> <ndir>                        #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_ACC.sh old Fe                                   #
#     ./send_ACC.sh usm D                                    #
#     ./send_ACC.sh jlab Pb 00                               #
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
TMPDIR=${WORKDIR}/tmp
if [[ "$setOption" == "jlab" ]]; then
    XMLDIR=${TMPDIR}/xml/acc/${setOption}/${tarName}/${nDir}
    LOGDIR=${TMPDIR}/log/acc/${setOption}/${tarName}/${nDir}
    INDIR=${WORKDIR}/FilterNCombine/${setOption}/${tarName}/${nDir}
    ACCDIR=${WORKDIR}/Acceptance/${setOption}/${tarName}/${nDir}
else
    XMLDIR=${TMPDIR}/xml/acc/${setOption}/${tarName}
    LOGDIR=${TMPDIR}/log/acc/${setOption}/${tarName}
    INDIR=${WORKDIR}/FilterNCombine/${setOption}/${tarName}
    ACCDIR=${WORKDIR}/Acceptance/${setOption}/${tarName}
fi
mkdir -p ${TMPDIR}
mkdir -p ${XMLDIR} ${LOGDIR}
mkdir -p ${ACCDIR}

# obtain run numbers
nfiles=$(ls -1 ${INDIR} | wc -l)

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="30" # minutes
jobspace="500" # MB
jobmemory="500" # MB

for ((COUNTER=1; COUNTER <= $nfiles; COUNTER++)); do
    # update rn value
    if [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num_2dig $(($COUNTER-1)) ) # rn starts at 00
    else
	rn=$(get_num_2dig $COUNTER) # rn starts at 01
    fi

    # setting jobname
    if [[ "${setOption}" == "jlab" ]]; then
	jobname="ACC_${setOption}-${tarName}-${nDir}_${rn}"
    else
	jobname="ACC_${setOption}-${tarName}_${rn}"
    fi
    jobfile="${XMLDIR}/${jobname}.xml"

    echo ${jobname}

    echo "<Request>"                                                                   > ${jobfile}
    echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
    echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
    echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
    echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
    echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
    echo "  <TimeLimit time=\"${jobtime}\" unit=\"minutes\"/>"                        >> ${jobfile}
    echo "  <DiskSpace space=\"${jobspace}\" unit=\"MB\"/>"                           >> ${jobfile}
    echo "  <Memory space=\"${jobmemory}\" unit=\"MB\"/>"                             >> ${jobfile}
    echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
    # set inputs
    thebinary="${PRODIR}/bin/Acceptance_omega"
    execfile="${PRODIR}/sh/jlab/run_ACC.sh"
    echo "  <Input src=\"${thebinary}\"  dest=\"Acceptance_omega\"/>"                 >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_ACC.sh\"/>"                       >> ${jobfile}
    # input root files
    inrootfile="${INDIR}/comb${tarName}_${rn}.root"
    echo "  <Input src=\"${inrootfile}\" dest=\"comb${tarName}_${rn}.root\"/>"        >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_ACC.sh"                 >> ${jobfile}
    echo "    chmod 755 ./run_ACC.sh"                                                 >> ${jobfile}
    echo "    sh run_ACC.sh"                                                          >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${ACCDIR}/acceptance${tarName}_${rn}.root"
    echo "  <Output src=\"acceptance${tarName}.root\" dest=\"${outrootfile}\"/>"      >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done