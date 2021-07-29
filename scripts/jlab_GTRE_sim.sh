#!/bin/bash

##############################################################
# ./jlab_GTRE_sim.sh <set> <target> <ndir>                   #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (00, 01, 02, ...)                           #
#                                                            #
# EG: ./jlab_GTRE_sim.sh old Fe                              #
#     ./jlab_GTRE_sim.sh usm D                               #
#     ./jlab_GTRE_sim.sh jlab C 01                           #
##############################################################

# Script made to filter omega simulations.
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

source ${HOME}/.bashrc

# define important dirs
GSTDIR=${VLTLDIR}/GetSimpleTuple
TPFDIR=${PRODIR}/ThreePionFinder
REDDIR=${PRODIR}/Reductor

if [[ "${SETOPTION}" == "jlab" ]]; then
    SIMDIR=/cache/mss/clas/eg2a/production/Simulation/omega_lepto/${TARNAME}/${NDIR} # sims stored in cache
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR2=${WORKDIR}/out/ThreePionFinder/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR3=${WORKDIR}/out/Reductor_3P/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR4=${WORKDIR}/out/EventMixing_3P/${SETOPTION}/${TARNAME}/${NDIR}
	TMPDIR=${WORKDIR}/tmp/${SETOPTION}/${TARNAME}/${NDIR}
else
    SIMDIR=/cache/mss/clas/eg2a/production/Simulation/omega_lepto/${SETOPTION}/${TARNAME} # sims stored in cache
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/${SETOPTION}/${TARNAME}
    OUDIR2=${WORKDIR}/out/ThreePionFinder/${SETOPTION}/${TARNAME}
    OUDIR3=${WORKDIR}/out/Reductor_3P/${SETOPTION}/${TARNAME}
    OUDIR4=${WORKDIR}/out/EventMixing_3P/${SETOPTION}/${TARNAME}
	TMPDIR=${WORKDIR}/tmp/${SETOPTION}/${TARNAME}
fi
# make dirs, just in case
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2} ${OUDIR3} ${OUDIR4}

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="8" # hours
jobspace="6" # GB
jobmemory="2" # GB

NFILES=$(ls -1 ${SIMDIR} | wc -l)
for ((COUNTER=1; COUNTER <= ${NFILES}; COUNTER++)); do
	# update RN value
	if [[ "${SETOPTION}" == "jlab" ]]; then
		RN=$(get_num_2dig $((${COUNTER}-1))) # starts at 00
	else
		RN=$(get_num_4dig ${COUNTER}) # starts at 0001
	fi

	# setting jobname
	jobname="GTRE_${SETOPTION}-${TARNAME}_${RN}"
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
	thebinary3="${REDDIR}/bin/Reductor"
	execfile="${PRODIR}/scripts/run_GTRE_sim.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"ThreePionFinder_sim\"/>"             >> ${jobfile}
	echo "  <Input src=\"${thebinary3}\"  dest=\"Reductor\"/>"                        >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_GTRE_sim.sh\"/>"                 >> ${jobfile}
	inrootfile="${SIMDIR}/recsis${TARNAME}_${RN}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"recsis${TARNAME}_${RN}.root\" />"     >> ${jobfile}
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\"       run_GTRE_sim.sh"      >> ${jobfile}
	echo "    sed -i \"s|^RN=|RN=${RN}|g\"                      run_GTRE_sim.sh"      >> ${jobfile}
	echo "    chmod 755 ./run_GTRE_sim.sh"                                            >> ${jobfile}
	echo "    sh run_GTRE_sim.sh"                                                     >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set outputs
	outrootfile01="${OUDIR1}/pruned${TARNAME}_${RN}.root"
	outrootfile02="${OUDIR2}/comb${TARNAME}_${RN}.root"
	outrootfile03="${OUDIR3}/pruned${TARNAME}_${RN}_red.root"
	outrootfile04="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPip.root"
	outrootfile05="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPim.root"
	outrootfile06="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sPi0.root"
	outrootfile07="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_sAll.root"
	outrootfile08="${OUDIR3}/pruned${TARNAME}_${RN}_red_MC.root"
	outrootfile09="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_MC_sPip.root"
	outrootfile10="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_MC_sPim.root"
	outrootfile11="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_MC_sPi0.root"
	outrootfile12="${OUDIR4}/bkgmix${TARNAME}_${RN}_red_MC_sAll.root"
	echo "  <Output src=\"pruned${TARNAME}_${RN}.root\"             dest=\"${outrootfile01}\"/>" >> ${jobfile}
	echo "  <Output src=\"comb${TARNAME}_${RN}.root\"               dest=\"${outrootfile02}\"/>" >> ${jobfile}
	echo "  <Output src=\"pruned${TARNAME}_${RN}_red.root\"         dest=\"${outrootfile03}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPip.root\"    dest=\"${outrootfile04}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPim.root\"    dest=\"${outrootfile05}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPi0.root\"    dest=\"${outrootfile06}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sAll.root\"    dest=\"${outrootfile07}\"/>" >> ${jobfile}
	echo "  <Output src=\"pruned${TARNAME}_${RN}_red_MC.root\"      dest=\"${outrootfile08}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPip.root\" dest=\"${outrootfile09}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPim.root\" dest=\"${outrootfile10}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPi0.root\" dest=\"${outrootfile11}\"/>" >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sAll.root\" dest=\"${outrootfile12}\"/>" >> ${jobfile}
	# set logs
	echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
	echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
	echo "  <Job>"                                                                    >> ${jobfile}
	echo "  </Job>"                                                                   >> ${jobfile}
	echo "</Request>"                                                                 >> ${jobfile}

	echo "Submitting job: ${jobfile}"
	jsub --xml ${jobfile}
done
