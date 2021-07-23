#!/bin/bash

#############################################################
# ./usm_TRE_data.sh <target>                                #
#     <target> = (C, Fe, Pb)                                #
#                                                           #
# EG: ./usm_TRE_data.sh C                                   #
#     ./usm_TRE_data.sh Fe                                  #
#     ./usm_TRE_data.sh Pb                                  #
#############################################################

# One script to rule them all, now for the USM cluster.

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
GSTDIR=${HOME}/GetSimpleTuple # necessary because of the RN lists
TGFDIR=${HOME}/analysis-omega/TwoGammaFinder
REDDIR=${HOME}/analysis-omega/Reductor

TMPDIR=${WORKDIR}/tmp/data/${TARNAME}
PRUDIR=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME} # results after GST
OUDIR1=${WORKDIR}/out/TwoGammaFinder/data/${TARNAME}
OUDIR2=${WORKDIR}/out/Reductor_2G/data/${TARNAME}
OUDIR3=${WORKDIR}/out/EventMixing_2G/data/${TARNAME}

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2} ${OUDIR3}
# copy binary files
cp ${TGFDIR}/bin/TwoGammaFinder_data ${OUDIR1}
cp ${REDDIR}/bin/Reductor_2G         ${OUDIR2}
cp ${TGFDIR}/bin/TwoGammaFinder_data ${OUDIR3}

# obtain run numbers
if [[ "${TARNAME}" == "C" ]]; then
    RNLIST=${GSTDIR}/include/C-thickD2rn.txt
elif [[ "${TARNAME}" == "Fe" ]]; then
    RNLIST=${GSTDIR}/include/Fe-thickD2rn.txt
elif [[ "${TARNAME}" == "Pb" ]]; then
    RNLIST=${GSTDIR}/include/Pb-thinD2rn.txt
fi
NFILES=$(wc -l < ${RNLIST})

# start
for ((COUNTER=1; COUNTER <= ${NFILES}; COUNTER++)); do # ${NFILES} or 1
    # update RN value
    RN=$(sed -n "$COUNTER{p;q}" ${RNLIST}) # data from RNLIST

    # setting jobname
    jobname="TRE_${TARNAME}_${RN}"
    jobfile="${TMPDIR}/${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=08:00:00"                                    >> ${jobfile} # 4hrs or 15min for test
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    # TwoGammaFinder
    echo "cd ${OUDIR1}"                                               >> ${jobfile} # enter output dir 1
    echo "cp -v ${PRUDIR}/pruned${TARNAME}_${RN}.root ${OUDIR1}"      >> ${jobfile} # copy GST files
    echo "./TwoGammaFinder_data -t${TARNAME} -r${RN}"                 >> ${jobfile} # execute program
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied GST files
    # Reductor_2G
    echo "cd ${OUDIR2}"                                               >> ${jobfile} # enter output dir 2
    echo "cp -v ${PRUDIR}/pruned${TARNAME}_${RN}.root ${OUDIR2}"      >> ${jobfile} # copy GST files
    echo "./Reductor_2G -t${TARNAME} -r${RN}"                         >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}_red.root ${OUDIR3}"            >> ${jobfile} # copy output files to dir 3
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied GST files
    # EventMixing
    echo "cd ${OUDIR3}"                                               >> ${jobfile} # enter output dir 3
    echo "./TwoGammaFinder_data -t${TARNAME} -r${RN}_red -m22"        >> ${jobfile} # execute program, swap gammas
    echo "rm -v pruned${TARNAME}_${RN}_red.root"                      >> ${jobfile} # remove copied RE_2G files

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
