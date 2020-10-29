#!/bin/bash

##############################################################
# ./send_GF_Data.sh <target>                                 #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_GF_Data.sh C                                    #
#     ./send_GF_Data.sh Fe                                   #
#     ./send_GF_Data.sh Pb                                   #
##############################################################

#####
# Input
###

tarName="$@"

#####
# Main
###

# set env, should set PRODIR and WORKDIR
source ~/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp
XMLDIR=${TMPDIR}/xml/data/${tarName}
LOGDIR=${TMPDIR}/log/data/${tarName}
GSTDIR=${WORKDIR}/GetSimpleTuple/data/${tarName}
FNCDIR=${WORKDIR}/FilterNCombine/data/${tarName}
INDIR=/mss/clas/eg2a/production/Pass2/Clas # data stored on tape
INDIR2=${WORKDIR}/data-EG2 # new!

# make dirs, just in case
mkdir -p ${TMPDIR}
mkdir -p ${XMLDIR} ${LOGDIR}
mkdir -p ${GSTDIR} ${FNCDIR}

# obtain run numbers
if [[ "${tarName}" == "C" ]]; then
    rnlist=${PRODIR}/include/C-thickD2rn.txt
elif [[ "${tarName}" == "Fe" ]]; then
    rnlist=${PRODIR}/include/Fe-thickD2rn.txt
elif [[ "${tarName}" == "Pb" ]]; then
    rnlist=${PRODIR}/include/Pb-thinD2rn.txt
fi
nfiles=$(wc -l < ${rnlist})

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="2" # hours
jobspace="2" # GB
jobmemory="2" # GB

for ((COUNTER=1; COUNTER <= ${nfiles}; COUNTER++)); do # ${nfiles} or 1
    # update rn value
    rn=$(sed -n "$COUNTER{p;q}" ${rnlist}) # data from rnlist

    # setting jobname
    jobname="GF_data-${tarName}_${rn}"
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
    thebinary1="${PRODIR}/bin/GetSimpleTuple_data"
    thebinary2="${PRODIR}/bin/FilterNCombine_data"
    execfile="${PRODIR}/sh/jlab/run_GF_Data.sh"
    echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${execfile}\"    dest=\"run_GF_Data.sh\"/>"                  >> ${jobfile}
    for file in ${INDIR}/clas_${rn}*; do
	inrootfile=$(readlink -f ${file})
	echo "  <Input src=\"mss:${inrootfile}\" dest=\"${file##*/}\"/>"              >> ${jobfile}
    done
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_GF_Data.sh"             >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\"                run_GF_Data.sh"             >> ${jobfile}
    echo "    chmod 755 ./run_GF_Data.sh"                                             >> ${jobfile}
    echo "    sh run_GF_Data.sh"                                                      >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${GSTDIR}/pruned${tarName}_${rn}.root"
    outrootfile2="${FNCDIR}/comb${tarName}_${rn}.root"
    echo "  <Output src=\"pruned${tarName}_${rn}.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
    echo "  <Output src=\"comb${tarName}_${rn}.root\"   dest=\"${outrootfile2}\"/>"   >> ${jobfile}
    # extract from tape
    for file in ${INDIR}/clas_${rn}*; do
	echo "  <Output src=\"${file##*/}\" dest=\"${INDIR2}/${file##*/}\"/>"              >> ${jobfile}
    done
    # set logs
    echo "  <Stdout dest=\"${LOGDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${LOGDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
