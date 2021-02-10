#!/bin/bash

##############################################################
# ./send_FNC_mix.sh <target>                                 #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_FNC_mix.sh C                                    #
#     ./send_FNC_mix.sh Fe                                   #
#     ./send_FNC_mix.sh Pb                                   #
##############################################################

#####
# Input
###

TARNAME="$@"

#####
# Main
###

# set env, WORKDIR and VLTLDIR should be already set
source ~/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp/data/${TARNAME}
FNCDIR=${VLTLDIR}/analysis-omega/FilterNCombine_mix
DATADIR=${WORKDIR}/out/GST_Reduced/data/${TARNAME}
OUDIR=${WORKDIR}/out/FilterNCombine_mix/data/${TARNAME}

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
    file2=${file//_red}
    file3=${file2##*_}
    RN=${file3%.root}
    
    # setting jobname
    jobname="FNCm_${TARNAME}_${RN}"
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
    thebinary="${FNCDIR}/bin/FilterNCombine_mix"
    execfile="${FNCDIR}/sh/run_FNC_mix.sh"
    echo "  <Input src=\"${thebinary}\" dest=\"FilterNCombine_mix\"/>"                >> ${jobfile}
    echo "  <Input src=\"${execfile}\" dest=\"run_FNC_mix.sh\"/>"                     >> ${jobfile}
    echo "  <Input src=\"${file}\" dest=\"${file##*/}\" />"                           >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_FNC_mix.sh"             >> ${jobfile}
    echo "    sed -i \"s|^RN=|RN=${RN}_red|g\"            run_FNC_mix.sh"             >> ${jobfile}
    echo "    chmod 755 ./run_FNC_mix.sh"                                             >> ${jobfile}
    echo "    sh run_FNC_mix.sh"                                                      >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPip.root\"   dest=\"${OUDIR}/bkgmix${TARNAME}_${RN}_sPip.root\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPim.root\"   dest=\"${OUDIR}/bkgmix${TARNAME}_${RN}_sPim.root\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sGamma.root\" dest=\"${OUDIR}/bkgmix${TARNAME}_${RN}_sGamma.root\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sAll.root\"   dest=\"${OUDIR}/bkgmix${TARNAME}_${RN}_sAll.root\"/>" >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
