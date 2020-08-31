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
#     ./send_GST.sh jlab Pb 002                              #
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

function get_num_3dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 100 ]]; then
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
    nfiles=$(wc -l < ${rnlist})
else
    if [[ "${setOption}" == "old" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/old/${tarName}"
    elif [[ "${setOption}" == "usm" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/usm/${tarName}"
    elif [[ "${setOption}" == "jlab" ]]; then
	DATADIR="/home/borquez/volatile/omegaSim/output/${tarName}2/${nDir}"
    fi
    inputOption="-s"
    nfiles=$(ls -1 ${DATADIR} | wc -l)
fi

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="debug" # "debug" or "analysis"
jobos="general"
jobtime="4" # hours
jobspace="1" # GB
jobmemory="3" # GB
thebinary="${PRODIR}/bin/GetSimpleTuple"
execfile="${PRODIR}/sh/jlab/run_GST.sh"

for ((COUNTER=1; COUNTER <= 10; COUNTER++)); do # "COUNTER <= 10" or "COUNTER <= ${nfiles}" or "COUNTER <= 100"
    # update rn value
    if [[ "${setOption}" == "data" ]]; then
	rn=$(sed -n "$COUNTER{p;q}" $rnlist) # data from rnlist
    elif [[ "${setOption}" == "old"  || "${setOption}" == "usm" ]]; then
	rn=$(get_num_2dig "$COUNTER") # starts at 01
    elif [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num_2dig $(($COUNTER-1)) ) # rn starts at 00
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
	    echo "  <Input src=\"mss:${inrootfile##/w}\" dest=\"${file##*/}\"/>"      >> ${jobfile}
	done
    elif [[ "$setOption" == "jlab" ]]; then
	for ((su=1; su <= 35; su++)); do
	    ssu=$(get_num_2dig $su)
	    inrootfile="${DATADIR}/recsis${tarName}_${rn}_${ssu}.root"
	    echo "  <Input src=\"${inrootfile}\" dest=\"recsis${tarName}_${rn}_${ssu}.root\"/>"  >> ${jobfile}
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
    # set outputs, updated to 35 files per each rn
    for ((sub=1; sub <= 35; sub++)); do
	ssub=$(get_num_2dig $sub)
	outrootfile="${OUDIR}/pruned${tarName}_${rn}_${ssub}.root"
	echo "  <Output src=\"pruned${tarName}_${rn}_${ssub}.root\" dest=\"${outrootfile}\"/>"    >> ${jobfile}
    done
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
