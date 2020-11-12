#!/bin/bash

##############################################################
# ./send_GF_basic.sh <target>                                #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_GF_basic.sh C                                   #
#     ./send_GF_basic.sh Fe                                  #
#     ./send_GF_basic.sh Pb                                  #
##############################################################

#####
# Input
###

tarName="$@"

#####
# Main
###

# set env, should set PRODIR and WORKDIR
source ~/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp


GSTDIR=${WORKDIR}/GetSimpleTuple/data/${tarName}
FNCDIR=${WORKDIR}/FilterNCombine/data/${tarName}

INDIR=/data/jlab/mss/clas/eg2a/production/Pass2/Clas

# make dirs, just in case
mkdir -p ${TMPDIR}
mkdir -p ${GSTDIR} ${FNCDIR}

# obtain run numbers
if [[ "${tarName}" == "C" ]]; then
    rnlist=${PRODIR}/include/C-thickD2rn.txt
elif [[ "${tarName}" == "Fe" ]]; then
    rnlist=${PRODIR}/include/Fe-thickD2rn.txt
elif [[ "${tarName}" == "Pb" ]]; then
    rnlist=${PRODIR}/include/Pb-thinD2rn.txt
fi
nfiles=$(wc -l < ${rnlist})

for ((COUNTER=1; COUNTER <= ${nfiles}; COUNTER++)); do # ${nfiles} or 1
    # update rn value
    rn=$(sed -n "$COUNTER{p;q}" ${rnlist}) # data from rnlist
    
    # make node dir
    JOBDIR=${TMPDIR}/job/data/${tarName}/${rn}
    mkdir -p ${JOBDIR}
    
    # setting jobname
    jobname="GF_basic-${tarName}_${rn}"
    jobfile="${JOBDIR}/${jobname}.sh"

    echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${JOBDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${JOBDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=4:00:00"                                     >> ${jobfile}
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    # first, set env and copy files into nodedir
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    echo "cp -v ${PRODIR}/bin/GetSimpleTuple_basic ${JOBDIR}/"        >> ${jobfile}
    echo "cp -v ${PRODIR}/bin/FilterNCombine_data ${JOBDIR}/"         >> ${jobfile}
    for file in ${INDIR}/clas_${rn}*; do
	inrootfile=$(readlink -f ${file})
	echo "cp ${inrootfile} ${JOBDIR}/"                            >> ${jobfile}
    done
    # execute
    echo "cd ${JOBDIR}"                                               >> ${jobfile}
    echo "./GetSimpleTuple_basic -t${tarName} -r${rn}"                >> ${jobfile}
    echo "./FilterNCombine_data -t${tarName} -r${rn}"                 >> ${jobfile}
    # move outputs and clean remaining files
    echo "mv -v pruned${tarName}_${rn}.root ${GSTDIR}/"               >> ${jobfile}
    echo "mv -v comb${tarName}_${rn}.root   ${FNCDIR}/"               >> ${jobfile}
    echo "rm -v GetSimpleTuple_basic"                                 >> ${jobfile}
    echo "rm -v FilterNCombine_data"                                  >> ${jobfile}
    echo "rm -v *.root"                                               >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile}
done
