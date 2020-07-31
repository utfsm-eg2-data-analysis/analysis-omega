#!/bin/bash

##############################################################
# ./send_FNC.sh <set> <target> <ndir>                        #
#     <set>    = (data, old, usm, jlab)                      #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_FNC.sh data C                                   #
#     ./send_FNC.sh old Fe                                   #
#     ./send_FNC.sh usm D                                    #
#     ./send_FNC.sh jlab Pb 02                               #
##############################################################

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
cd ${PRODIR}

# define important dirs
if [[ "$setOption" == "jlab" ]]; then
    DATADIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}/${nDir}
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}/${nDir}
    OUDIR=${PRODIR}/out/FilterNCombine/${setOption}/${tarName}/${nDir}    
else
    DATADIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}
    OUDIR=${PRODIR}/out/FilterNCombine/${setOption}/${tarName}
fi
mkdir -p ${XMLDIR}
mkdir -p ${OUDIR}

# set input option
if [[ "${setOption}" == "data" ]]; then
    if [[ ${tarName} = "C" ]]; then
	rnlist=${PRODIR}/include/C-thickD2rn.txt
    elif [[ ${tarName} = "Fe" ]]; then
	rnlist=${PRODIR}/include/Fe-thickD2rn.txt
    elif [[ ${tarName} = "Pb" ]]; then
	rnlist=${PRODIR}/include/Pb-thinD2rn.txt
    fi
    inputOption="_data"
    nfiles=$(wc -l < ${rnlist})
else
    inputOption="_sim"
    nfiles=$(ls -1 ${DATADIR} | wc -l)
fi

# declaration of variables
#jobfile=
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug"
jobos="general"
#jobname=
jobtime="72" # hours
jobspace="1" # GB
jobmemory="1" # GB
thebinary="${PRODIR}/bin/FilterNCombine${inputOption}"
#inrootfile=
#outrootfile=
execfile="${PRODIR}/sh/jlab/run_FNC.sh"

for ((COUNTER=1; COUNTER <= ${nfiles}; COUNTER++)); do
    # update rn value
    if [[ "${setOption}" == "data" ]]; then
	rn=$(sed -n "$COUNTER{p;q}" $rnlist) # data from rnlist
    elif [[ "${setOption}" == "usm" || "${setOption}" == "old" ]]; then
	rn=$(get_num "$COUNTER") # old and usm start at 1
    elif [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num "$(($COUNTER - 1))") # jlab files start at 0
    fi

    # setting jobname
    if [[ "${setOption}" == "jlab" ]]; then
	jobname="FNC_${setOption}-${tarName}-${nDir}_${rn}"
    else
	jobname="FNC_${setOption}-${tarName}_${rn}"
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
    echo "  <Input src=\"${thebinary}\"  dest=\"FilterNCombine${inputOption}\"/>"     >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_FNC.sh\"/>"                       >> ${jobfile}
    inrootfile="${DATADIR}/pruned${tarName}_${rn}.root"
    echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${rn}.root\"/>"      >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^inputOption=|inputOption=${inputOption}|g\" run_FNC.sh"     >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_FNC.sh"                 >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\" run_FNC.sh"                                >> ${jobfile}
    echo "    chmod 755 ./run_FNC.sh"                                                 >> ${jobfile}
    echo "    sh run_FNC.sh"                                                          >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${OUDIR}/comb${tarName}_${rn}.root"
    echo "  <Output src=\"comb${tarName}_${rn}.root\" dest=\"${outrootfile}\"/>"      >> ${jobfile}
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
