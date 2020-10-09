#!/bin/bash

##############################################################
# ./send_AEN.sh <set> <target> <ndir>                        #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_AEN.sh old Fe                                   #
#     ./send_AEN.sh usm D                                    #
#     ./send_AEN.sh jlab Pb 00                               #
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
    XMLDIR=${TMPDIR}/xml/aen/${setOption}/${tarName}/${nDir}
    LOGDIR=${TMPDIR}/log/aen/${setOption}/${tarName}/${nDir}
    INDIR=${WORKDIR}/GetSimpleTuple/${setOption}/${tarName}/${nDir}
    AENDIR=${WORKDIR}/Acceptance_EN/${setOption}/${tarName}/${nDir}
else
    XMLDIR=${TMPDIR}/xml/aen/${setOption}/${tarName}
    LOGDIR=${TMPDIR}/log/aen/${setOption}/${tarName}
    INDIR=${WORKDIR}/GetSimpleTuple/${setOption}/${tarName}
    AENDIR=${WORKDIR}/Acceptance_EN/${setOption}/${tarName}/${nDir}
fi
mkdir -p ${TMPDIR}
mkdir -p ${XMLDIR} ${LOGDIR}
mkdir -p ${AENDIR}

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
	jobname="AEN_${setOption}-${tarName}-${nDir}_${rn}"
    else
	jobname="AEN_${setOption}-${tarName}_${rn}"
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
    thebinary="${PRODIR}/bin/Acceptance_EN"
    execfile="${PRODIR}/sh/jlab/run_AEN.sh"
    echo "  <Input src=\"${thebinary}\" dest=\"Acceptance_EN\"/>"                     >> ${jobfile}
    echo "  <Input src=\"${execfile}\"  dest=\"run_AEN.sh\"/>"                        >> ${jobfile}
    # input root files
    inrootfile="${INDIR}/pruned${tarName}_${rn}.root"
    echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${rn}.root\"/>" >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_AEN.sh"                 >> ${jobfile}
    echo "    chmod 755 ./run_AEN.sh"                                                 >> ${jobfile}
    echo "    sh run_AEN.sh"                                                          >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${AENDIR}/acc-en${tarName}_${rn}.root"
    echo "  <Output src=\"electron-numbers${tarName}.root\" dest=\"${outrootfile}\"/>" >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
