#!/bin/bash

##############################################################
# ./jlab_GT_sim-bkg.sh <target>                              #
#     <target> = (D, C, Fe, Pb)                              #
#                                                            #
# EG: ./jlab_GT_sim-bkg.sh Fe                                #
##############################################################

# Script made to filter background simulations for the OMEGA-ML project.
# Please, make sure the environment variables HOME, PRODIR, VLTLDIR and WORKDIR are properly defined.

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

#####
# Input
###

TARNAME="$@"

#####
# Main
###

# set env, WORKDIR and VLTLDIR should be set
source ${HOME}/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp/bkg/${TARNAME}
GSTDIR=${VLTLDIR}/GetSimpleTuple
TPFDIR=${PRODIR}/ThreePionFinder
OUDIR1=${WORKDIR}/out/GetSimpleTuple/bkg/${TARNAME}
OUDIR2=${WORKDIR}/out/ThreePionFinder/bkg/${TARNAME}
SIMDIR=${WORKDIR}/simulations-bkg/${TARNAME} # important input dir

# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2}

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="3" # hours
jobspace="6" # GB
jobmemory="2" # GB

# obtain run numbers
NFILES=$(ls -1 ${SIMDIR} | wc -l)

for ((COUNTER=0; COUNTER < ${NFILES}; COUNTER++)); do
	RN=$(get_num_2dig $COUNTER) # starts at 00

	jobname="GT_bkg-${TARNAME}_${RN}"
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
	thebinary1="${GSTDIR}/bin/GetSimpleTuple_sim"
	thebinary2="${TPFDIR}/bin/ThreePionFinder_sim"
	execfile="${VLTLDIR}/analysis-omega/scripts/run_GT_sim-bkg.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"ThreePionFinder_sim\"/>"             >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_GT_sim-bkg.sh\"/>"               >> ${jobfile}
	inrootfile="${SIMDIR}/recsis${TARNAME}_${RN}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"recsis${TARNAME}_${RN}.root\" />"     >> ${jobfile}
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_GT_sim-bkg.sh"          >> ${jobfile}
	echo "    sed -i \"s|^RN=|RN=${RN}|g\"                run_GT_sim-bkg.sh"          >> ${jobfile}
	echo "    chmod 755 ./run_GT_sim-bkg.sh"                                          >> ${jobfile}
	echo "    sh run_GT_sim-bkg.sh"                                                   >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set outputs
	outrootfile01="${OUDIR1}/pruned${TARNAME}_${RN}.root"
	outrootfile02="${OUDIR2}/comb${TARNAME}_${RN}.root"
	echo "  <Output src=\"pruned${TARNAME}_${RN}.root\" dest=\"${outrootfile01}\"/>"  >> ${jobfile}
	echo "  <Output src=\"comb${TARNAME}_${RN}.root\"   dest=\"${outrootfile02}\"/>"  >> ${jobfile}
	# set logs
	echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
	echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
	echo "  <Job>"                                                                    >> ${jobfile}
	echo "  </Job>"                                                                   >> ${jobfile}
	echo "</Request>"                                                                 >> ${jobfile}

	echo "Submitting job: ${jobfile}"
	jsub --xml ${jobfile}
done
