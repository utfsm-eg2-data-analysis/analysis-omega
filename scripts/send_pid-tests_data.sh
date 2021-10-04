#!/bin/bash

##############################################
#                                            #
#  Script made to send batch jobs            #
#    to test some PID schemes on C data      #
#                                            #
##############################################

#############################
# Check for possible errors #
#############################

if [[ ! -e ${HOME}/software/env_scripts/set_all.sh ]]; then
    echo "ERROR: script to set environment variables <set_all.sh> doesn't exist."
    echo ""
    exit 1
fi

if [[ -z "${VLTLDIR}" ]]; then
    echo "ERROR: environment variable VLTLDIR is unset."
    echo ""
    exit 1
fi

if [[ ! -e ${VLTLDIR}/GetSimpleTuple/bin/GetSimpleTuple_no-ec ]]; then
    echo "ERROR: binary file <GetSimpleTuple_no-ec> doesn't exist."
    echo ""
    exit 1
fi

if [[ ! -e ${VLTLDIR}/GetSimpleTuple/bin/GetSimpleTuple_no-vertex ]]; then
    echo "ERROR: binary file <GetSimpleTuple_no-vertex> doesn't exist."
    echo ""
    exit 1
fi

if [[ ! -e ${VLTLDIR}/GetSimpleTuple/bin/GetSimpleTuple_no-dc-fid ]]; then
    echo "ERROR: binary file <GetSimpleTuple_no-dc-fid> doesn't exist."
    echo ""
    exit 1
fi

if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: environment variable WORKDIR is unset."
    echo ""
    exit 1
fi

########
# Main #
########

TARNAME="C"

# define directories
GST_BINDIR=${VLTLDIR}/GetSimpleTuple/bin

TEST_OUTDIR=${WORKDIR}/out/TestPID/data/${TARNAME}

DATADIR=/cache/mss/clas/eg2a/production/Pass2/Clas
TMPDIR=${WORKDIR}/tmp/data/${TARNAME}

# make output dirs, just in case
mkdir -p ${TMPDIR} ${TEST_OUTDIR}

# copy binaries to output dirs
cp -v ${GST_BINDIR}/GetSimpleTuple_no-ec ${TEST_OUTDIR}
cp -v ${GST_BINDIR}/GetSimpleTuple_no-vertex ${TEST_OUTDIR}
cp -v ${GST_BINDIR}/GetSimpleTuple_no-dc-fid ${TEST_OUTDIR}

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${GST_BINDIR}/../include/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${GST_BINDIR}/../include/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${GST_BINDIR}/../include/Pb-thinD2rn.txt
fi
TOTALRN=$(wc -l < ${RNLIST})

# start
for ((COUNTER=1; COUNTER <= ${TOTALRN}; COUNTER++)); do
    # update RN value
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # data from RNLIST

    # setting jobname, pidt = pid test
    jobname="pidt_${TARNAME}_${RN}"
    jobfile="${TMPDIR}/job_${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                              > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                                   >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                                     >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                                     >> ${jobfile}
    echo "#SBATCH --time=4:00:00"                                                  >> ${jobfile}
    echo "#SBATCH --mem=2GB"                                                       >> ${jobfile}
    echo ""                                                                        >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                                  >> ${jobfile}
    echo "source ${HOME}/software/env_scripts/set_all.sh"                          >> ${jobfile}

    # GetSimpleTuple
    echo "cd ${TEST_OUTDIR}"                                                       >> ${jobfile} # enter GST output dir
    for file in ${DATADIR}/clas_${RN}*; do                                                       # list all the files of a run
	    inputfile=$(readlink -f ${file})                                                         # retrieve full path of each input file
	    echo "ln -s ${inputfile} ${inputfile##*/}"                                 >> ${jobfile} # symbolic link each input file
    done
    echo "./GetSimpleTuple_no-ec -t${TARNAME} -r${RN}"                             >> ${jobfile} # execute program
    echo "mv -v pruned${TARNAME}_${RN}.root pruned${TARNAME}_${RN}_no-ec.root"     >> ${jobfile} # rename output files accordingly
    echo "./GetSimpleTuple_no-vertex -t${TARNAME} -r${RN}"                         >> ${jobfile} # execute program
    echo "mv -v pruned${TARNAME}_${RN}.root pruned${TARNAME}_${RN}_no-vertex.root" >> ${jobfile} # rename output files accordingly
    echo "./GetSimpleTuple_no-dc-fid -t${TARNAME} -r${RN}"                         >> ${jobfile} # execute program
    echo "mv -v pruned${TARNAME}_${RN}.root pruned${TARNAME}_${RN}_no-dc-fid.root" >> ${jobfile} # rename output files accordingly
    echo "rm -v clas_${RN}*.root"                                                  >> ${jobfile} # remove symbolic link of input files

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
