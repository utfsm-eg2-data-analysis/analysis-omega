#!/bin/bash

##############################################
#                                            #
#  Script made to send batch jobs            #
#    to filter the entire CLAS6 EG2 data     #
#      and reconstruct eta and omega mesons  #
#        (with syst. electron cuts)          #
#                                            #
##############################################

############################
# Declaration of functions #
############################

function print_help() {
    echo "SCRIPT: send_filter-jobs_syst.sh"
    echo "================================"
    echo "./send_filter-jobs_syst.sh --targ <targ> --syst <syst> --sigma <sigma>"
    echo "Where:"
    echo "  <targ>  = selects target (C, Fe, Pb)"
    echo "  <syst>  = selects systematic source (SF: Sampling Fraction, VC: Vertex Cuts)"
    echo "  <sigma> = choose Number of sigma (For VC: -1, +1) (For SF: 2.0, 3.0)"
    echo "Example:"
    echo "  ./send_filter-jobs_syst.sh --targ C --syst SF --sigma 2.0"
    exit 0
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--targ" ]]; then
            TARNAME=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--syst" ]]; then
            SYSTOPT=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--sigma" ]]; then
            SYSTVAL=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}."
            print_help
            exit 1
        fi
        ((ic+=2))
    done
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

# define suffix
if [[ "${SYSTVAL}" == "+1" ]]; then
    SYSTVAL="plus-1"
elif [[ "${SYSTVAL}" == "-1" ]]; then
    SYSTVAL="minus-1"
fi
SYSTSUFFIX=${SYSTOPT}_${SYSTVAL}-sigma

# define directories
GST_BINDIR=${VLTLDIR}/GetSimpleTuple/bin
TPF_BINDIR=${VLTLDIR}/analysis-omega/ThreePionFinder/bin
TGF_BINDIR=${VLTLDIR}/analysis-omega/TwoGammaFinder/bin
RED_BINDIR=${VLTLDIR}/analysis-omega/Reductor/bin

GST_OUTDIR=${WORKDIR}/out/GetSimpleTuple/syst/${SYSTSUFFIX}/${TARNAME}
TPF_OUTDIR=${WORKDIR}/out/ThreePionFinder/syst/${SYSTSUFFIX}/${TARNAME}
TGF_OUTDIR=${WORKDIR}/out/TwoGammaFinder/syst/${SYSTSUFFIX}/${TARNAME}
RED_OUTDIR=${WORKDIR}/out/Reductor/syst/${SYSTSUFFIX}/${TARNAME}
EVM_OUTDIR=${WORKDIR}/out/EventMixing/syst/${SYSTSUFFIX}/${TARNAME}

DATADIR=/cache/mss/clas/eg2a/production/Pass2/Clas
TMPDIR=${WORKDIR}/tmp/syst/${TARNAME}

# make output dirs, just in case
mkdir -p ${TMPDIR} ${GST_OUTDIR} ${TPF_OUTDIR} ${TGF_OUTDIR} ${RED_OUTDIR} ${EVM_OUTDIR}

source ${HOME}/software/env_scripts/set_all.sh # set root and clastool
echo ""

# swap TIdentificators
mv -v ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2.h ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2_orig.h
mv -v ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2_${SYSTSUFFIX}.h ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2.h
# recompile GST
cd ${VLTLDIR}/GetSimpleTuple
make clean; make
mv -v ${VLTLDIR}/GetSimpleTuple/bin/GetSimpleTuple_data ${VLTLDIR}/GetSimpleTuple/bin/GetSimpleTuple_${SYSTSUFFIX}
# restore original TIdentificator
mv -v ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2.h ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2_${SYSTSUFFIX}.h
mv -v ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2_orig.h ${VLTLDIR}/GetSimpleTuple/include/TIdentificatorV2.h

# copy binaries to output dirs
if [[ -e ${GST_BINDIR}/GetSimpleTuple_${SYSTSUFFIX} && -e ${TPF_BINDIR}/ThreePionFinder_data && -e ${TGF_BINDIR}/TwoGammaFinder_data &&
      -e ${RED_BINDIR}/Reductor && -e ${TPF_BINDIR}/ThreePionFinder_data ]]; then
    cp -v ${GST_BINDIR}/GetSimpleTuple_${SYSTSUFFIX} ${GST_OUTDIR}
    cp -v ${TPF_BINDIR}/ThreePionFinder_data         ${TPF_OUTDIR}
    cp -v ${TGF_BINDIR}/TwoGammaFinder_data          ${TGF_OUTDIR}
    cp -v ${RED_BINDIR}/Reductor                     ${RED_OUTDIR}
    cp -v ${TPF_BINDIR}/ThreePionFinder_data         ${EVM_OUTDIR}
else
    echo "ERROR: there are missing binaries. Check if every binary is compiled."
    echo ""
    exit 1
fi

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
    jobname="SYST_${TARNAME}_${RN}_${SYSTSUFFIX}"
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
    echo "source ${HOME}/software/env_scripts/set_all.sh"             >> ${jobfile} # set root v6.10.02 and clastool

    # GetSimpleTuple
    echo "cd ${GST_OUTDIR}"                                           >> ${jobfile} # enter GST output dir
    for file in ${DATADIR}/clas_${RN}*; do                                          # list all the files of a run
	    inputfile=$(readlink -f ${file})                                            # retrieve full path of each input file
	    echo "ln -s ${inputfile} ${inputfile##*/}"                    >> ${jobfile} # symbolic link each input file
    done
    echo "./GetSimpleTuple_${SYSTSUFFIX} -t${TARNAME} -r${RN}"        >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}.root ${TGF_OUTDIR}"            >> ${jobfile} # copy output files to 2GF output dir
    echo "cp -v pruned${TARNAME}_${RN}.root ${TPF_OUTDIR}"            >> ${jobfile} # copy output files to 3PF output dir
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
