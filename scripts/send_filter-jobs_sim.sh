#!/bin/bash

#################################################
#                                               #
#  Script made to send batch jobs               #
#    to filter the eta and omega simulations    #
#      that were generated with LEPTO, for the  #
#        analysis of the CLAS6 EG2 data         #
#                                               #
#################################################

############################
# Declaration of functions #
############################

function print_help() {
    echo "SCRIPT: send_filter-jobs_sim.sh"
    echo "==============================="
    echo "./send_filter-jobs_sim.sh --part <part> --targ <targ> --dir <dir>"
    echo "Where:"
    echo "  <part> = selects particle (eta, omega)"
    echo "  <targ> = selects target (D, C, Fe, Pb)"
    echo "  <dir>  = selects dir (00, 01, ...)"
    echo "Example:"
    echo "  ./send_filter-jobs_sim.sh --part omega --targ D --dir 00"
    exit 0
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--targ" ]]; then
            TARNAME=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--part" ]]; then
            PARTICLE=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--dir" ]]; then
            NDIR=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}."
            print_help
            exit 1
        fi
        ((ic+=2))
    done
}

function get_num_2dig() {
    sr=$1
    srn=""
    if [[ ${sr} -lt 10 ]]; then
        srn="0${sr}"
    else
        srn="${sr}"
    fi
    echo ${srn}
}

#############################
# Check for possible errors #
#############################

NARGS=6 # number of command-line arguments
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

GST_OUTDIR=${WORKDIR}/out/GetSimpleTuple/${PARTICLE}-sim/${TARNAME}/${NDIR}
TPF_OUTDIR=${WORKDIR}/out/ThreePionFinder/${PARTICLE}-sim/${TARNAME}/${NDIR}
TGF_OUTDIR=${WORKDIR}/out/TwoGammaFinder/${PARTICLE}-sim/${TARNAME}/${NDIR}
RED_OUTDIR=${WORKDIR}/out/Reductor/${PARTICLE}-sim/${TARNAME}/${NDIR}
EVM_OUTDIR=${WORKDIR}/out/EventMixing/${PARTICLE}-sim/${TARNAME}/${NDIR}

SIMDIR=/cache/mss/clas/eg2a/production/Simulation/${PARTICLE}_lepto/new/${TARNAME}/${NDIR}
TMPDIR=${WORKDIR}/tmp/${PARTICLE}-sim/${TARNAME}/${NDIR}

# make output dirs, just in case
mkdir -p ${TMPDIR} ${GST_OUTDIR} ${TPF_OUTDIR} ${TGF_OUTDIR} ${RED_OUTDIR} ${EVM_OUTDIR}

# copy binaries to output dirs
cp -v ${GST_BINDIR}/GetSimpleTuple_sim   ${GST_OUTDIR}
cp -v ${TPF_BINDIR}/ThreePionFinder_sim  ${TPF_OUTDIR}
cp -v ${TGF_BINDIR}/TwoGammaFinder_sim   ${TGF_OUTDIR}
cp -v ${RED_BINDIR}/Reductor             ${RED_OUTDIR}
cp -v ${TPF_BINDIR}/ThreePionFinder_sim  ${EVM_OUTDIR}

# obtain run numbers
TOTALRN=$(ls -1 ${SIMDIR} | wc -l)

# start
for ((COUNTER=1; COUNTER <= ${TOTALRN}; COUNTER++)); do
    # update RN value
    RN=$(get_num_2dig $((${COUNTER} - 1))) # starts at 00

    # setting jobname
    jobname="${PARTICLE}_${TARNAME}_${NDIR}_${RN}"
    jobfile="${TMPDIR}/job_${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=2:00:00"                                     >> ${jobfile}
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    echo "source ${HOME}/software/env_scripts/set_all.sh"             >> ${jobfile}

    # GetSimpleTuple
    echo "cd ${GST_OUTDIR}"                                           >> ${jobfile} # enter GST output dir
    inputfile=$(readlink -f ${SIMDIR}/recsis${TARNAME}_${RN}.root)                  # retrieve full path of input file
    echo "ln -s ${inputfile} ${inputfile##*/}"                        >> ${jobfile} # symbolic link the respective input file
    echo "./GetSimpleTuple_sim -t${TARNAME} -r${RN}"                  >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}.root ${TPF_OUTDIR}"            >> ${jobfile} # copy output files to 3PF output dir
    echo "cp -v pruned${TARNAME}_${RN}.root ${TGF_OUTDIR}"            >> ${jobfile} # copy output files to 2GF output dir
    echo "cp -v pruned${TARNAME}_${RN}.root ${RED_OUTDIR}"            >> ${jobfile} # copy output files to RED output dir
    echo "rm -v recsis${TARNAME}_${RN}.root"                          >> ${jobfile} # remove symbolic link of input file

    if [[ "${PARTICLE}" == "eta" ]]; then
        # TwoGammaFinder
        echo "cd ${TGF_OUTDIR}"                                       >> ${jobfile} # enter 2GF output dir
        echo "./TwoGammaFinder_sim -t${TARNAME} -r${RN}"              >> ${jobfile} # execute program
        echo "rm -v pruned${TARNAME}_${RN}.root"                      >> ${jobfile} # remove copied input files
    elif [[ "${PARTICLE}" == "omega" ]]; then
        # ThreePionFinder
        echo "cd ${TPF_OUTDIR}"                                       >> ${jobfile} # enter 3PF output dir
        echo "./ThreePionFinder_sim -t${TARNAME} -r${RN}"             >> ${jobfile} # execute program
        echo "rm -v pruned${TARNAME}_${RN}.root"                      >> ${jobfile} # remove copied input files

        # Reductor
        echo "cd ${RED_OUTDIR}"                                       >> ${jobfile} # enter RED output dir
        echo "./Reductor -t${TARNAME} -r${RN} -s"                     >> ${jobfile} # execute program
        echo "cp -v redu${TARNAME}_${RN}.root ${EVM_OUTDIR}"          >> ${jobfile} # copy RED output files to EVM output dir
        echo "rm -v pruned${TARNAME}_${RN}.root"                      >> ${jobfile} # remove copied input files

        # EventMixing
        echo "cd ${EVM_OUTDIR}"                                       >> ${jobfile} # enter EVM output dir
        echo "./ThreePionFinder_sim -t${TARNAME} -r${RN} -m211"       >> ${jobfile} # execute program, swap pi+
        echo "./ThreePionFinder_sim -t${TARNAME} -r${RN} -m-211"      >> ${jobfile} # execute program, swap pi-
        echo "./ThreePionFinder_sim -t${TARNAME} -r${RN} -m111"       >> ${jobfile} # execute program, swap pi0
        echo "./ThreePionFinder_sim -t${TARNAME} -r${RN} -m999"       >> ${jobfile} # execute program, swap all
        echo "rm -v redu${TARNAME}_${RN}.root"                        >> ${jobfile} # remove copied input files
    else
        echo "ERROR: <part> argument must be omega or eta."
        exit 1
    fi

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
