#!/bin/bash

##############################################
#                                            #
#  Script made to send batch jobs            #
#    to filter the entire CLAS6 EG2 dataset  #
#      and reconstruct eta and omega mesons  #
#                                            #
##############################################

############################
# Declaration of functions #
############################

function print_help() {
    echo "SCRIPT: send_filter-jobs_data.sh"
    echo "================================"
    echo "./send_filter-jobs_data.sh --targ <targ>"
    echo "Where:"
    echo "  <targ> = selects target (C, Fe, Pb)"
    echo "Example:"
    echo "  ./send_filter-jobs_data.sh --targ C"
    exit 0
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--targ" ]]; then
            TARNAME=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}."
            print_help
        fi
        ((ic+=2))
    done
}

#############################
# Check for possible errors #
#############################

NARGS=2 # number of command-line arguments
if [[ ${#} -ne ${NARGS} ]]; then
    echo "ERROR: ${#} arguments were provided, they should be ${NARGS}."
    echo ""
    print_help
    exit 1
fi

if [[ ! -e ${HOME}/software/env_scripts/set_all.sh ]]; then
    echo "ERROR: script to set environment variables <set_all.sh> doesn't exist."
    echo ""
    print_help
    exit 1
fi

if [[ -z "${VLTLDIR}" ]]; then
    echo "ERROR: environment variable VLTLDIR is unset."
    echo ""
    print_help
    exit 1
fi

if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: environment variable WORKDIR is unset."
    echo ""
    print_help
    exit 1
fi

########
# Main #
########

argArray=("$@")
process_args "${argArray[@]}"

# define directories
GST_BINDIR=${VLTLDIR}/GetSimpleTuple/bin
TPF_BINDIR=${VLTLDIR}/analysis-omega/ThreePionFinder/bin
TGF_BINDIR=${VLTLDIR}/analysis-omega/TwoGammaFinder/bin
RED_BINDIR=${VLTLDIR}/analysis-omega/Reductor/bin

GST_OUTDIR=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
TPF_OUTDIR=${WORKDIR}/out/ThreePionFinder/data/${TARNAME}
TGF_OUTDIR=${WORKDIR}/out/TwoGammaFinder/data/${TARNAME}
RED_OUTDIR=${WORKDIR}/out/Reductor/data/${TARNAME}
EVM_OUTDIR=${WORKDIR}/out/EventMixing/data/${TARNAME}

DATADIR=/cache/mss/clas/eg2a/production/Pass2/Clas
TMPDIR=${WORKDIR}/tmp/data/${TARNAME}

# make output dirs, just in case
mkdir -p ${TMPDIR} ${GST_OUTDIR} ${TPF_OUTDIR} ${TGF_OUTDIR} ${RED_OUTDIR} ${EVM_OUTDIR}

# copy binaries to output dirs
cp -v ${GST_BINDIR}/GetSimpleTuple_data  ${GST_OUTDIR}
cp -v ${TPF_BINDIR}/ThreePionFinder_data ${TPF_OUTDIR}
cp -v ${TGF_BINDIR}/TwoGammaFinder_data  ${TGF_OUTDIR}
cp -v ${RED_BINDIR}/Reductor             ${RED_OUTDIR}
cp -v ${TPF_BINDIR}/ThreePionFinder_data ${EVM_OUTDIR}

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

    # setting jobname
    jobname="data_${TARNAME}_${RN}"
    jobfile="${TMPDIR}/job_${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=4:00:00"                                     >> ${jobfile}
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    echo "source ${HOME}/software/env_scripts/set_all.sh"             >> ${jobfile}

    # GetSimpleTuple
    echo "cd ${GST_OUTDIR}"                                           >> ${jobfile} # enter GST output dir
    for file in ${DATADIR}/clas_${RN}*; do                                          # list all the files of a run
	    inputfile=$(readlink -f ${file})                                            # retrieve full path of each input file
	    echo "ln -s ${inputfile} ${inputfile##*/}"                    >> ${jobfile} # symbolic link each input file
    done
    echo "./GetSimpleTuple_data -t${TARNAME} -r${RN}"                 >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}.root ${TPF_OUTDIR}"            >> ${jobfile} # copy output files to 3PF output dir
    echo "cp -v pruned${TARNAME}_${RN}.root ${TGF_OUTDIR}"            >> ${jobfile} # copy output files to 2GF output dir
    echo "cp -v pruned${TARNAME}_${RN}.root ${RED_OUTDIR}"            >> ${jobfile} # copy output files to RED output dir
    echo "rm -v clas_${RN}*.root"                                     >> ${jobfile} # remove symbolic link of input files

    # TwoGammaFinder
    echo "cd ${TGF_OUTDIR}"                                           >> ${jobfile} # enter 2GF output dir
    echo "./TwoGammaFinder_data -t${TARNAME} -r${RN}"                 >> ${jobfile} # execute program
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied input files

    # ThreePionFinder
    echo "cd ${TPF_OUTDIR}"                                           >> ${jobfile} # enter 3PF output dir
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}"                >> ${jobfile} # execute program
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied input files

    # Reductor
    echo "cd ${RED_OUTDIR}"                                           >> ${jobfile} # enter RED output dir
    echo "./Reductor -t${TARNAME} -r${RN}"                            >> ${jobfile} # execute program
    echo "cp -v redu${TARNAME}_${RN}.root ${EVM_OUTDIR}"              >> ${jobfile} # copy RED output files to EVM output dir
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied input files

    # EventMixing
    echo "cd ${EVM_OUTDIR}"                                           >> ${jobfile} # enter EVM output dir
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN} -m211"          >> ${jobfile} # execute program, swap pi+
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN} -m-211"         >> ${jobfile} # execute program, swap pi-
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN} -m111"          >> ${jobfile} # execute program, swap pi0
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN} -m999"          >> ${jobfile} # execute program, swap all
    echo "rm -v redu${TARNAME}_${RN}.root"                            >> ${jobfile} # remove copied input files

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
