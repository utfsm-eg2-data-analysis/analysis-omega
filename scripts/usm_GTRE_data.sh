#!/bin/bash

#############################################################
# ./usm_GTRE_data.sh <target>                               #
#     <target> = (C, Fe, Pb)                                #
#                                                           #
# EG: ./usm_GTRE_data.sh C                                  #
#     ./usm_GTRE_data.sh Fe                                 #
#     ./usm_GTRE_data.sh Pb                                 #
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
GSTDIR=${HOME}/GetSimpleTuple
TPFDIR=${HOME}/analysis-omega/ThreePionFinder
REDDIR=${HOME}/analysis-omega/Reductor
DATADIR=/data/jlab/mss/clas/eg2a/production/Pass2/Clas

TMPDIR=${WORKDIR}/tmp/data/${TARNAME}
OUDIR1=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
OUDIR2=${WORKDIR}/out/ThreePionFinder/data/${TARNAME}
OUDIR3=${WORKDIR}/out/Reductor/data/${TARNAME}
OUDIR4=${WORKDIR}/out/EventMixing/data/${TARNAME}

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2} ${OUDIR3} ${OUDIR4}
# copy binary files
cp ${GSTDIR}/bin/GetSimpleTuple_data ${OUDIR1}
cp ${TPFDIR}/bin/ThreePionFinder_data ${OUDIR2}
cp ${REDDIR}/bin/Reductor            ${OUDIR3}
cp ${TPFDIR}/bin/ThreePionFinder_data ${OUDIR4}

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
    jobname="GTRE_${TARNAME}_${RN}"
    jobfile="${TMPDIR}/${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=4:00:00"                                     >> ${jobfile} # 4hrs or 15min for test
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    # GetSimpleTuple
    echo "cd ${OUDIR1}"                                               >> ${jobfile} # enter output dir 1
    for file in ${DATADIR}/clas_${RN}*; do # extract all run numbers
	inputfile=$(readlink -f ${file})
	echo "ln -s ${inputfile} ${inputfile##*/}"                        >> ${jobfile} # sym. link data files
    done
    echo "./GetSimpleTuple_data -t${TARNAME} -r${RN}"                 >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}.root ${OUDIR2}"                >> ${jobfile} # copy output files to dir 2
    echo "cp -v pruned${TARNAME}_${RN}.root ${OUDIR3}"                >> ${jobfile} # copy output files to dir 3
    echo "rm -v clas_${RN}*.root"                                     >> ${jobfile} # remove copied input files
    # ThreePionFinder
    echo "cd ${OUDIR2}"                                               >> ${jobfile} # enter output dir 2
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}"                >> ${jobfile} # execute program
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied input files
    # Reductor
    echo "cd ${OUDIR3}"                                               >> ${jobfile} # enter output dir 3
    echo "./Reductor -t${TARNAME} -r${RN}"                            >> ${jobfile} # execute program
    echo "cp -v pruned${TARNAME}_${RN}_red.root ${OUDIR4}"            >> ${jobfile} # copy output files to dir 4
    echo "rm -v pruned${TARNAME}_${RN}.root"                          >> ${jobfile} # remove copied input files
    # EventMixing
    echo "cd ${OUDIR4}"                                               >> ${jobfile} # enter output dir 4
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}_red -m211"      >> ${jobfile} # execute program, swap pi+
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}_red -m-211"     >> ${jobfile} # execute program, swap pi-
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}_red -m111"      >> ${jobfile} # execute program, swap pi0
    echo "./ThreePionFinder_data -t${TARNAME} -r${RN}_red -m999"      >> ${jobfile} # execute program, swap all
    echo "rm -v pruned${TARNAME}_${RN}_red.root"                      >> ${jobfile} # remove copied input files

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
