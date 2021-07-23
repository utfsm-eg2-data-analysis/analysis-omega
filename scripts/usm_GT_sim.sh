#!/bin/bash

##############################################################
# ./usm_GT_sim.sh <set> <target> <ndir>                      #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (00, 01, 02, ...)                           #
#                                                            #
# EG: ./usm_GT_sim.sh old Fe                                 #
#     ./usm_GT_sim.sh usm D                                  #
#     ./usm_GT_sim.sh jlab Pb 00                             #
##############################################################

# One script to filter the necessary simulations.
# The environment variables HOME, PRODIR and WORKDIR must be properly defined.

#####
# Functions
###

function get_num_2dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

function get_num_4dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="000$sr"
  elif [[ $sr -lt 100 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 1000 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

#####
# Input
###

INPUTARRAY=("$@")

SETOPTION="${INPUTARRAY[0]}"
TARNAME="${INPUTARRAY[1]}"
NDIR="${INPUTARRAY[2]}"

#####
# Main
###

# set env, WORKDIR and VLTLDIR should be set
source ~/.bashrc

# define important dirs
GSTDIR=${HOME}/GetSimpleTuple
TPFDIR=${PRODIR}/ThreePionFinder
if [[ "${SETOPTION}" == "jlab" ]]; then
	TMPDIR=${WORKDIR}/tmp/sim/${SETOPTION}/${TARNAME}/${NDIR}
	SIMDIR=${WORKDIR}/simulations/${SETOPTION}/${TARNAME}/${NDIR} # location of omega simulations in USM cluster
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/sim/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR2=${WORKDIR}/out/ThreePionFinder/sim/${SETOPTION}/${TARNAME}/${NDIR}
else
	TMPDIR=${WORKDIR}/tmp/sim/${SETOPTION}/${TARNAME}
	SIMDIR=${WORKDIR}/simulations/${SETOPTION}/${TARNAME} # location of omega simulations in USM cluster
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/sim/${SETOPTION}/${TARNAME}
    OUDIR2=${WORKDIR}/out/ThreePionFinder/sim/${SETOPTION}/${TARNAME}
fi

# make dirs, just in case
mkdir -p ${OUDIR1} ${OUDIR2} ${TMPDIR}

# define number of jobs per target or ndir
if [[ "${SETOPTION}" == "old" ]]; then
	NJOBS=1 # per target
elif [[ "${SETOPTION}" == "usm" ]]; then
	NJOBS=4 # per target
elif [[ "${SETOPTION}" == "jlab" ]]; then
	NJOBS=3 # per ndir
fi

# copy binaries to TMPDIR
cp ${GSTDIR}/bin/GetSimpleTuple_sim ${TMPDIR}
cp ${TPFDIR}/bin/ThreePionFinder_sim ${TMPDIR}

# start
for ((JOB=0; JOB < ${NJOBS}; JOB++)); do

	jobname="${SETOPTION}-${TARNAME}_${JOB}"
	jobfile="${TMPDIR}/${jobname}.sh"

	echo ${jobname}

    echo "#!/bin/bash"                                                 > ${jobfile}
    echo "#SBATCH -J ${jobname}"                                      >> ${jobfile}
    echo "#SBATCH -o ${TMPDIR}/${jobname}.out"                        >> ${jobfile}
    echo "#SBATCH -e ${TMPDIR}/${jobname}.err"                        >> ${jobfile}
    echo "#SBATCH --time=6:00:00"                                     >> ${jobfile} # 6hrs or 15min for test
    echo "#SBATCH --mem=2GB"                                          >> ${jobfile}
    echo ""                                                           >> ${jobfile}
    echo "source ${HOME}/.bashrc"                                     >> ${jobfile}
    echo "cd ${TMPDIR}"                                               >> ${jobfile}

	# define start and end of RN depending on the job
	NFILES=$(ls -1 ${SIMDIR} | wc -l)
    if [[ "${SETOPTION}" == "old" ]]; then
        START=1
        END=${NFILES}
    else
        START=$((1 + ${JOB}*${NFILES}/${NJOBS}))
        END=$((${START} + ${NFILES}/${NJOBS} - 1))
        if [[ $(($JOB+1)) -eq $NJOBS ]]; then ((END+=1)); fi
    fi

	for ((COUNTER=${START}; COUNTER <= ${END}; COUNTER++)); do
		# update RN value
		if [[ "${SETOPTION}" == "jlab" ]]; then
			RN=$(get_num_2dig $(($COUNTER-1))) # starts at 00
		else
			RN=$(get_num_4dig $COUNTER) # starts at 0001
		fi
		# retrieve full path of input file
		inputfile=$(readlink -f ${SIMDIR}/recsis${TARNAME}_${RN}.root)
		# symbolic link the respective input file
		echo "ln -s ${inputfile} ${inputfile##*/}"                    >> ${jobfile}
		# execute program sequentially
		echo "./GetSimpleTuple_sim -t${TARNAME} -r${RN}"              >> ${jobfile}
		echo "./ThreePionFinder_sim -t${TARNAME} -r${RN}"             >> ${jobfile}
		# move output files to output dirs
		echo "mv -v pruned${TARNAME}_${RN}.root ${OUDIR1}"            >> ${jobfile}
		echo "mv -v comb${TARNAME}_${RN}.root ${OUDIR2}"              >> ${jobfile}
		# remove copied input files
		echo "rm -v recsis${TARNAME}_${RN}.root"                      >> ${jobfile}
		echo ""                                                       >> ${jobfile}
	done

    echo "Submitting job: ${jobfile}"
    sbatch ${jobfile} # submit job!
done
