#!/bin/bash

##############################################################
# ./send_FNC.sh <set> <target> <ndir> <stage>                #
#     <set>    = (data, old, usm, jlab)                      #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_FNC.sh data C                                   #
#     ./send_FNC.sh old Fe                                   #
#     ./send_FNC.sh usm D                                    #
#     ./send_FNC.sh jlab Pb 002 A                            #
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
stageOption="${inputArray[3]}"

#####
# Main
###

# set env
source ~/.bashrc
cd ${PRODIR}

# define important dirs
if [[ "$setOption" == "jlab" ]]; then
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}/${nDir}
    OUDIR=${PRODIR}/out/FilterNCombine/${setOption}/${tarName}/${nDir}    
else
    XMLDIR=${PRODIR}/xml/${setOption}/${tarName}
    OUDIR=${PRODIR}/out/FilterNCombine/${setOption}/${tarName}
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
    inputOption="_data"
    nfiles=$(wc -l < ${rnlist})
else
    if [[ "$setOption" == "jlab" ]]; then
	DATADIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}/${nDir}
    else
	DATADIR=${PRODIR}/out/GetSimpleTuple/${setOption}/${tarName}
    fi
    inputOption="_sim"
    nfiles=$(ls -1 ${DATADIR} | wc -l)
fi

# set limit files for jlab
if [[ "$setOption" == "jlab" ]]; then
    if [[ "$tarName" == "D" && "$nDir" == "046" ]]; then
	nfiles=89
    elif [[ "$tarName" == "C" && "$nDir" == "010" ]]; then
	nfiles=28
    elif [[ "$tarName" == "Fe" && "$nDir" == "013" ]]; then
	nfiles=31
    elif [[ "$tarName" == "Pb" && "$nDir" == "004" ]]; then
	nfiles=98
    else
	nfiles=100  
    fi
fi

# for jlab
if [[ "$stageOption" == "A" ]]; then
    init=1
    end=10
elif [[ "$stageOption" == "B" ]]; then
    init=11
    end=20
elif [[ "$stageOption" == "C" ]]; then
    init=21
    end=30
elif [[ "$stageOption" == "D" ]]; then
    init=31
    end=35
fi

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="72" # hours
jobspace="1" # GB
jobmemory="512" # MB
thebinary="${PRODIR}/bin/FilterNCombine${inputOption}"
execfile="${PRODIR}/sh/jlab/run_FNC.sh"

# counter stands for rn
for ((COUNTER=1; COUNTER <= ${nfiles}; COUNTER++)); do # "1" or "${nfiles}"
    # update rn value
    if [[ "${setOption}" == "data" ]]; then
	rn=$(sed -n "$COUNTER{p;q}" $rnlist) # data from rnlist
    elif [[ "${setOption}" == "usm" || "${setOption}" == "old" ]]; then
	rn=$(get_num_2dig $COUNTER) # old and usm start at 01
    elif [[ "${setOption}" == "jlab" ]]; then
	rn=$(get_num_2dig $(($COUNTER-1)) ) # rn start at 00
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
    echo "  <Memory space=\"${jobmemory}\" unit=\"MB\"/>"                             >> ${jobfile}
    echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
    # set inputs
    echo "  <Input src=\"${thebinary}\"  dest=\"FilterNCombine${inputOption}\"/>"     >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_FNC.sh\"/>"                       >> ${jobfile}
    if [[ "$setOption" == "jlab" ]]; then
	for ((sub=$init; sub <= $end; sub++)); do
	    # update sub number
	    ssub=$(get_num_2dig $sub)
	    sufix="${rn}_${ssub}"
	    inrootfile="${DATADIR}/pruned${tarName}_${sufix}.root"
	    echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${sufix}.root\"/>" >> ${jobfile}
	done
    else
	inrootfile="${DATADIR}/pruned${tarName}_${rn}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${rn}.root\"/>"  >> ${jobfile}
    fi
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^setOption=|setOption=${setOption}|g\" run_FNC.sh"           >> ${jobfile}
    echo "    sed -i \"s|^inputOption=|inputOption=${inputOption}|g\" run_FNC.sh"     >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_FNC.sh"                 >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\" run_FNC.sh"                                >> ${jobfile}
    echo "    sed -i \"s|^stageOption=|stageOption=${stageOption}|g\" run_FNC.sh"     >> ${jobfile}
    echo "    chmod 755 ./run_FNC.sh"                                                 >> ${jobfile}
    echo "    sh run_FNC.sh"                                                          >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    if [[ "$setOption" == "jlab" ]]; then    
	for ((sub2=$init; sub2 <= $end; sub2++)); do
	    # update sub2 number
	    ssub2=$(get_num_2dig $sub2)
	    sufix2="${rn}_${ssub2}"
            outrootfile="${OUDIR}/comb${tarName}_${sufix2}.root"
	    echo "  <Output src=\"comb${tarName}_${sufix2}.root\" dest=\"${outrootfile}\" />" >> ${jobfile}
	done
    else
	outrootfile="${OUDIR}/comb${tarName}_${rn}.root"
	echo "  <Output src=\"comb${tarName}_${rn}.root\" dest=\"${outrootfile}\" />" >> ${jobfile}
    fi
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
