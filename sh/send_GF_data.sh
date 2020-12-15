#!/bin/bash

##############################################################
# ./send_GF_data.sh <target>                                 #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_GF_data.sh C                                    #
#     ./send_GF_data.sh Fe                                   #
#     ./send_GF_data.sh Pb                                   #
##############################################################

#####
# Input
###

TARNAME="$@"

#####
# Main
###

# set env, WORKDIR and VLTLDIR should be set
source ~/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp/data/${TARNAME}
GSTDIR=${VLTLDIR}/GetSimpleTuple
FNCDIR=${VLTLDIR}/analysis-omega/FilterNCombine
DATADIR=/cache/mss/clas/eg2a/production/Pass2/Clas # data stored in cache
OUDIR1=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
OUDIR2=${WORKDIR}/out/FilterNCombine/data/${TARNAME}

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2}

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${GSTDIR}/include/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${GSTDIR}/include/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${GSTDIR}/include/Pb-thinD2rn.txt
fi
NFILES=$(wc -l < ${RNLIST})

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="2" # hours
jobspace="1" # GB
jobmemory="2" # GB

for ((COUNTER=1; COUNTER <= ${NFILES}; COUNTER++)); do # ${NFILES} or 1
    # update RN value
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # data from RNLIST

    # setting jobname
    jobname="GF_${TARNAME}_${RN}"
    jobfile="${TMPDIR}/${jobname}.xml"

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
    thebinary1="${GSTDIR}/bin/GetSimpleTuple_data"
    thebinary2="${FNCDIR}/bin/FilterNCombine_data"
    execfile="${VLTLDIR}/analysis-omega/sh/run_GF_data.sh"
    echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${execfile}\"    dest=\"run_GF_data.sh\"/>"                  >> ${jobfile}
    for file in ${DATADIR}/clas_${RN}*; do
	inrootfile=$(readlink -f ${file})
	echo "  <Input src=\"${inrootfile}\" dest=\"${file##*/}\" copyOption=\"link\"/>" >> ${jobfile}
    done
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_GF_data.sh"             >> ${jobfile}
    echo "    sed -i \"s|^RN=|RN=${RN}|g\"                run_GF_data.sh"             >> ${jobfile}
    echo "    chmod 755 ./run_GF_data.sh"                                             >> ${jobfile}
    echo "    sh run_GF_data.sh"                                                      >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${OUDIR1}/pruned${TARNAME}_${RN}.root"
    outrootfile2="${OUDIR2}/comb${TARNAME}_${RN}.root"
    echo "  <Output src=\"pruned${TARNAME}_${RN}.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
    echo "  <Output src=\"comb${TARNAME}_${RN}.root\"   dest=\"${outrootfile2}\"/>"   >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
