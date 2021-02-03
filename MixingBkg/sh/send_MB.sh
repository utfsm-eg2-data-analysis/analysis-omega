#!/bin/bash

##############################################################
# ./send_MB.sh <target>                                      #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_MB.sh C                                         #
#     ./send_MB.sh Fe                                        #
#     ./send_MB.sh Pb                                        #
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
MBDIR=${VLTLDIR}/analysis-omega/MixingBkg
DATADIR=${WORKDIR}/out/GST_Reduced/data/${TARNAME}
OUDIR=${WORKDIR}/out/MixingBkg/data/${TARNAME}

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR}

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="30" # minutes
jobspace="500" # MB
jobmemory="500" # MB

for file in ${DATADIR}/*; do
    RN=${file##*_}
    RN=${RN%.root}
    RN="${RN}_red"
    
    # setting jobname
    jobname="MB_${TARNAME}_${RN%_red}"
    jobfile="${TMPDIR}/${jobname}.xml"

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
    thebinary="${MBDIR}/bin/MixingBkg"
    execfile="${VLTLDIR}/analysis-omega/sh/run_MB.sh"
    echo "  <Input src=\"${thebinary}\" dest=\"MixingBkg\"/>"                         >> ${jobfile}
    echo "  <Input src=\"${execfile}\" dest=\"run_MB.sh\"/>"                          >> ${jobfile}
    echo "  <Input src=\"${file}\" dest=\"${file##*/}\" />"                           >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_MB.sh"                  >> ${jobfile}
    echo "    sed -i \"s|^RN=|RN=${RN}|g\"                run_MB.sh"                  >> ${jobfile}
    echo "    chmod 755 ./run_MB.sh"                                                  >> ${jobfile}
    echo "    sh run_MB.sh"                                                           >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${OUDIR}/bkgmix${TARNAME}_${RN%_red}.root"
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}.root\" dest=\"${outrootfile}\"/>"   >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
