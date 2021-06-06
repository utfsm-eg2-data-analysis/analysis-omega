#!/bin/bash

##############################################################
# ./send_TRE_data.sh <target>                                #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_TRE_data.sh C                                   #
#     ./send_TRE_data.sh Fe                                  #
#     ./send_TRE_data.sh Pb                                  #
##############################################################

# One script to rule them all.

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
GSTDIR=${VLTLDIR}/GetSimpleTuple # necessary because of RN lists
TGFDIR=${VLTLDIR}/analysis-omega/TwoGammaFinder
REDDIR=${VLTLDIR}/analysis-omega/Reductor
PRUDIR=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
OUDIR1=${WORKDIR}/out/TwoGammaFinder/data/${TARNAME}
OUDIR2=${WORKDIR}/out/Reductor/data/${TARNAME}
OUDIR3=${WORKDIR}/out/EventMixing/data/${TARNAME}

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
jobtime="4" # hours
jobspace="2" # GB
jobmemory="1" # GB

for ((COUNTER=1; COUNTER <= ${NFILES}; COUNTER++)); do # ${NFILES} or 1
    # update RN value
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # data from RNLIST

    # setting jobname
    jobname="TRE_${TARNAME}_${RN}"
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
    thebinary1="${TGFDIR}/bin/TwoGammaFinder_data"
    thebinary2="${REDDIR}/bin/Reductor_2G"
    execfile="${VLTLDIR}/analysis-omega/sh/run_TRE_data.sh"
    inrootfile="${PRUDIR}/pruned${TARNAME}_${RN}.root"
    echo "  <Input src=\"${thebinary1}\" dest=\"TwoGammaFinder_data\"/>"              >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\" dest=\"Reductor_2G\"/>"                      >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_TRE_data.sh\"/>"                  >> ${jobfile}
    echo "  <Input src=\"${inrootfile}\" dest=\"${file##*/}\" copyOption=\"link\"/>"  >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_TRE_data.sh"            >> ${jobfile}
    echo "    sed -i \"s|^RN=|RN=${RN}|g\"                run_TRE_data.sh"            >> ${jobfile}
    echo "    chmod 755 ./run_TRE_data.sh"                                            >> ${jobfile}
    echo "    sh run_TRE_data.sh"                                                     >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${OUDIR1}/comb${TARNAME}_${RN}.root"
    outrootfile2="${OUDIR2}/pruned${TARNAME}_${RN}_red.root"
    outrootfile3="${OUDIR3}/bkgmix${TARNAME}_${RN}_red_sGamma.root"
    echo "  <Output src=\"comb${TARNAME}_${RN}.root\"              dest=\"${outrootfile1}\"/>" >> ${jobfile}
    echo "  <Output src=\"pruned${TARNAME}_${RN}_red.root\"        dest=\"${outrootfile2}\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sGamma.root\" dest=\"${outrootfile3}\"/>" >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
