#!/bin/bash

##############################################################
# ./send_FNC.sh <target> <ndir>                              #
#     <target> = (D, C, Fe)                                  #
#     <ndir>   = (001, 002, ...)                             #
#                                                            #
# EG: ./send_FNC.sh C 001                                    #
##############################################################

#####
# Input
###

inputArray=("$@")

tarName="${inputArray[0]}"
nDir="${inputArray[1]}"

#####
# Main
###

# set env
source ~/.bashrc
cd ${PRODIR}

# define and make important dirs
LOGDIR=${PRODIR}/log/${tarName}/${nDir}
XMLDIR=${PRODIR}/xml/jlab/${tarName}/${nDir}
OUDIR=${PRODIR}/out/FilterNCombine/jlab/${tarName}/${nDir}
mkdir -p ${LOGDIR}
mkdir -p ${XMLDIR}
mkdir -p ${OUDIR}

# set input dirs and obtain run numbers
DATADIR=${PRODIR}/out/GetSimpleTuple/jlab/${tarName}/${nDir}

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="24" # hours
jobspace="1" # GB
jobmemory="500" # MB

thebinary="${PRODIR}/bin/FilterNCombine_sim"
execfile="${PRODIR}/sh/jlab-test/run_FNC.sh" # test

# counter stands for rn
COUNTER=0
for file in $DATADIR/*.root; do
    # test
    if [[ $COUNTER -eq 100 ]]; then
	break
    fi

    # update id
    file1=${file#*_}
    id=${file1%.root}
        
    # set input and output
    inrootfile="${DATADIR}/pruned${tarName}_${id}.root"
    outrootfile="${OUDIR}/comb${tarName}_${id}.root"
    
    if [[ -f ${outrootfile} ]]; then
	continue
    else
	((COUNTER++)) # test
    fi
    
    # setting jobname
    jobname="FNC-test_${tarName}-${nDir}_${id}"
    jobfile="${XMLDIR}/${jobname}.xml"

    echo ${jobname}

    # echo "<Request>"                                                                   > ${jobfile}
    # echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
    # echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
    # echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
    # echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
    # echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
    # echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
    # echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
    # echo "  <Memory space=\"${jobmemory}\" unit=\"MB\"/>"                             >> ${jobfile}
    # echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
    # echo "  <Input src=\"${thebinary}\"  dest=\"FilterNCombine_sim\"/>"               >> ${jobfile}
    # echo "  <Input src=\"${execfile}\"   dest=\"run_FNC.sh\"/>"                       >> ${jobfile}
    # echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${id}.root\"/>"      >> ${jobfile}
    # echo "  <Command><![CDATA["                                                       >> ${jobfile}
    # echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_FNC.sh"                 >> ${jobfile}
    # echo "    sed -i \"s|^id=|id=${id}|g\" run_FNC.sh"                                >> ${jobfile}
    # echo "    chmod 755 ./run_FNC.sh"                                                 >> ${jobfile}
    # echo "    sh run_FNC.sh"                                                          >> ${jobfile}
    # echo "  ]]></Command>"                                                            >> ${jobfile}
    # echo "  <Output src=\"comb${tarName}_${id}.root\" dest=\"${outrootfile}\" />"     >> ${jobfile}
    # echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    # echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    # echo "  <Job>"                                                                    >> ${jobfile}
    # echo "  </Job>"                                                                   >> ${jobfile}
    # echo "</Request>"                                                                 >> ${jobfile}
    # 
    # echo "Submitting job: ${jobfile}"
    # jsub --xml ${jobfile}
done
