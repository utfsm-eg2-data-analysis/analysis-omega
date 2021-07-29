#!/bin/bash

##############################################################
# ./jlab_GTRE_data.sh <target>                               #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./jlab_GTRE_data.sh C                                  #
#     ./jlab_GTRE_data.sh Fe                                 #
#     ./jlab_GTRE_data.sh Pb                                 #
##############################################################

# Script made to filter data from the EG2 experiment.
# Please, make sure the environment variables HOME, PRODIR, VLTLDIR and WORKDIR are properly defined.

#####
# Input
###

TARNAME="$@"

#####
# Main
###

source ${HOME}/.bashrc

# input dirs
GSTDIR=${VLTLDIR}/GetSimpleTuple
TPFDIR=${PRODIR}/ThreePionFinder
REDDIR=${PRODIR}/Reductor
DATADIR=/cache/mss/clas/eg2a/production/Pass2/Clas # data stored in cache

# output dirs
OUDIR1=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
OUDIR2=${WORKDIR}/out/ThreePionFinder/data/${TARNAME}
OUDIR3=${WORKDIR}/out/Reductor_3P/data/${TARNAME}
OUDIR4=${WORKDIR}/out/EventMixing_3P/data/${TARNAME}
TMPDIR=${WORKDIR}/tmp/data/${TARNAME}

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2} ${OUDIR3} ${OUDIR4}

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${GSTDIR}/include/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${GSTDIR}/include/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${GSTDIR}/include/Pb-thinD2rn.txt
fi

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="4" # hours
jobspace="2" # GB
jobmemory="2" # GB

NFILES=$(wc -l < ${RNLIST})
for ((COUNTER=1; COUNTER <= ${NFILES}; COUNTER++)); do # ${NFILES} or 1
    # update RN value
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # data from RNLIST

    # setting jobname
    jobname="GTRE_${TARNAME}_${RN}"
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
    thebinary2="${TPFDIR}/bin/ThreePionFinder_data"
    thebinary3="${REDDIR}/bin/Reductor"
    execfile="${PRODIR}/scripts/run_GTRE_data.sh"
    echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${thebinary2}\"  dest=\"ThreePionFinder_data\"/>"             >> ${jobfile}
    echo "  <Input src=\"${thebinary3}\"  dest=\"Reductor\"/>"                        >> ${jobfile}
    echo "  <Input src=\"${execfile}\"    dest=\"run_GTRE_data.sh\"/>"                >> ${jobfile}
    for file in ${DATADIR}/clas_${RN}*; do
	inrootfile=$(readlink -f ${file})
	echo "  <Input src=\"${inrootfile}\" dest=\"${file##*/}\" copyOption=\"link\"/>" >> ${jobfile}
    done
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_GTRE_data.sh"           >> ${jobfile}
    echo "    sed -i \"s|^RN=|RN=${RN}|g\"                run_GTRE_data.sh"           >> ${jobfile}
    echo "    chmod 755 ./run_GTRE_data.sh"                                           >> ${jobfile}
    echo "    sh run_GTRE_data.sh"                                                    >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile1="${OUDIR1}/pruned${TARNAME}_${RN}.root"
    outrootfile2="${OUDIR2}/comb${TARNAME}_${RN}.root"
    outrootfile3="${OUDIR3}/pruned${TARNAME}_${RN}_red.root"
    outrootfile4="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPip.root"
    outrootfile5="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPim.root"
    outrootfile6="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPi0.root"
    outrootfile7="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sAll.root"
    echo "  <Output src=\"pruned${TARNAME}_${RN}.root\"          dest=\"${outrootfile1}\"/>" >> ${jobfile}
    echo "  <Output src=\"comb${TARNAME}_${RN}.root\"            dest=\"${outrootfile2}\"/>" >> ${jobfile}
    echo "  <Output src=\"pruned${TARNAME}_${RN}_red.root\"      dest=\"${outrootfile3}\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPip.root\" dest=\"${outrootfile4}\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPim.root\" dest=\"${outrootfile5}\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPi0.root\" dest=\"${outrootfile6}\"/>" >> ${jobfile}
    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sAll.root\" dest=\"${outrootfile7}\"/>" >> ${jobfile}
    # set logs
    echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
