#!/bin/bash

##############################################################
# ./send_GST.sh <set> <target> <ndir>                        #
#     <set>    = (data, old, usm, jlab)                      #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_GST.sh data C                                   #
#     ./send_GST.sh old Fe                                   #
#     ./send_GST.sh usm D                                    #
#     ./send_GST.sh jlab Pb 02                               #
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
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}/${nDir}
    OUDIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}/${nDir}
else
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}
    OUDIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}
fi
mkdir -p ${XMLDIR}
mkdir -p ${OUDIR}

# set input dirs and obtain run numbers
if [[ "${setOption}" == "data" ]]; then
    if [[ ${tarName} = "C" ]]; then
	rnlist=${PRODIR}/include/C-thickD2rn.txt
    elif [[ ${tarName} = "Fe" ]]; then
	rnlist=${PRODIR}/include/Fe-thickD2rn.txt
    elif [[ ${tarName} = "Pb" ]]; then
	rnlist=${PRODIR}/include/Pb-thinD2rn.txt
    fi
    DATADIR="/mss/clas/eg2a/production/Pass2/Clas"
    inputOption="-d"
    lines=`wc -l < ${rnlist}`
else
    if [[ "${setOption}" == "old" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/old/${tarName}"
    elif [[ "${setOption}" == "usm" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/usm/${tarName}"
    elif [[ "${setOption}" == "jlab" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/output/${tarName}/${nDir}"
    fi
    inputOption="-S${setOption}"
    lines=`ls -1 ${DATADIR} | wc -l`
fi

# declaration of variables
#jobfile=
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="debug" # testing... "analysis"
jobos="general"
#jobname=
jobtime="2" # hours
jobspace="10" # GB
jobmemory="1" # GB
thebinary="${PRODIR}/bin/GetSimpleTuple"
#inrootfile=
#outrootfile=
execfile="${PRODIR}/sh/jlab/run_GST.sh"

COUNTER=0
while [[ ${COUNTER} -lt 1 ]]; do # testing... ${lines}
    # update counter
    let COUNTER=COUNTER+1
    if [[ "${setOption}" == "data" ]]; then
	rn=$(sed -n "$COUNTER{p;q}" $rnlist)
    elif [[ "${setOption}" == "usm" || "${setOption}" == "old" ]]; then
	rn=$(get_num "$COUNTER") # old and usm start at 1
    elif [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num "$(($COUNTER - 1))") # jlab files start at 0
    fi

    # setting jobname
    if [[ "${setOption}" == "jlab" ]]; then
	jobname="GST_${setOption}-${tarName}-${nDir}_${rn}"
    else
	jobname="GST_${setOption}-${tarName}_${rn}"
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
    echo "  <Input src=\"${thebinary}\"  dest=\"GetSimpleTuple\"/>"                   >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_GST.sh\"/>"                       >> ${jobfile}
    if [[ "$setOption" == "data" ]]; then
	for file in ${DATADIR}/clas_${rn}*; do
	    inrootfile=$(readlink -f $file)
	    echo "  <Input src=\"mss:${inrootfile##/w}\" dest=\"${file##*/}\"/>"          >> ${jobfile}
	done
    else
	inrootfile="${DATADIR}/recsis${tarName}_${rn}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"recsis${tarName}_${rn}.root\"/>"  >> ${jobfile}
    fi
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^inputOption=|inputOption=${inputOption}|g\" run_GST.sh"     >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_GST.sh"                 >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\" run_GST.sh"                                >> ${jobfile}
    echo "    chmod 755 ./run_GST.sh"                                                 >> ${jobfile}
    echo "    sh run_GST.sh"                                                          >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${OUDIR}/pruned${tarName}_${rn}.root"
    echo "  <Output src=\"pruned${tarName}_${rn}.root\" dest=\"${outrootfile}\"/>"    >> ${jobfile}
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
