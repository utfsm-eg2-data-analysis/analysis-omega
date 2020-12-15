#!/bin/bash

##############################################################
# ./send_GF_sim.sh <set> <target> <ndir>                     #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (01, 02, ...)                               #
#                                                            #
# EG: ./send_GF_sim.sh old Fe                                #
#     ./send_GF_sim.sh usm D                                 #
#     ./send_GF_sim.sh jlab Pb 00                            #
##############################################################

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

INPUTARRAY=("$@")

SETOPTION="${INPUTARRAY[0]}"
TARNAME="${INPUTARRAY[1]}"
NDIR="${INPUTARRAY[2]}"

#####
# Main
###

# set env
source ~/.bashrc

# define important dirs
TMPDIR=${WORKDIR}/tmp/sim/${SETOPTION}/${TARNAME}
GSTDIR=${VLTLDIR}/GetSimpleTuple
FNCDIR=${VLTLDIR}/analysis-omega/FilterNCombine
if [[ "$SETOPTION" == "jlab" ]]; then
    SIMDIR=/cache/mss/clas/eg2a/production/Simulation/omega_lepto/${TARNAME}/${NDIR} # sims stored in cache
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/jlab/${TARNAME}/${NDIR}
    OUDIR2=${WORKDIR}/out/FilterNCombine/jlab/${TARNAME}/${NDIR}
else
    SIMDIR=/cache/mss/clas/eg2a/production/Simulation/omega_lepto/${SETOPTION}/${TARNAME} # sims stored in cache
    OUDIR1=${WORKDIR}/out/GetSimpleTuple/${SETOPTION}/${TARNAME}
    OUDIR2=${WORKDIR}/out/FilterNCombine/${SETOPTION}/${TARNAME}
fi
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2}

# obtain run numbers
NFILES=$(ls -1 ${SIMDIR} | wc -l)

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="2" # hours
jobspace="2" # GB
jobmemory="2" # GB

if [[ "${SETOPTION}" == "old" || "${SETOPTION}" == "usm" ]]; then
    for ((COUNTER=1; COUNTER <= $NFILES; COUNTER++)); do
	RN=$(get_num_2dig $COUNTER) # starts at 01
	
	jobname="GF_${SETOPTION}-${TARNAME}_${RN}"
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
	thebinary2="${FNCDIR}/bin/FilterNCombine_sim"
	execfile="${VLTLDIR}/analysis-omega/sh/run_GF_sim.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_GF_sim.sh\"/>"                   >> ${jobfile}
	inrootfile="${SIMDIR}/recsis${TARNAME}_${RN}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"recsis${TARNAME}_${RN}.root\" copyOption=\"link\"/>"      >> ${jobfile}
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^SETOPTION=|SETOPTION=${SETOPTION}|g\" run_GF_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\"       run_GF_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^RN=|RN=${RN}|g\"                      run_GF_sim.sh"        >> ${jobfile}
	echo "    chmod 755 ./run_GF_sim.sh"                                              >> ${jobfile}
	echo "    sh run_GF_sim.sh"                                                       >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set outputs
	outrootfile1="${OUDIR1}/pruned${TARNAME}_${RN}.root"
	outrootfile2="${OUDIR2}/comb${TARNAME}_${RN}.root"
	echo "  <Output src=\"pruned${TARNAME}_${RN}.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
	echo "  <Output src=\"comb${TARNAME}_${RN}.root\"   dest=\"${outrootfile2}\"/>"   >> ${jobfile}
	# set logs
	echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
	echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
	echo "  <Job>"                                                                    >> ${jobfile}
	echo "  </Job>"                                                                   >> ${jobfile}
	echo "</Request>"                                                                 >> ${jobfile}

	echo "Submitting job: ${jobfile}"
	jsub --xml ${jobfile}
    done
elif [[ "${SETOPTION}" == "jlab" ]]; then
    # divide each dir into 4 sets
    nsets=$(($NFILES/25))
    if [[ $(($NFILES%25)) > 0 ]]; then ((nsets++)); fi
    for ((set_index=0; set_index < $nsets; set_index++)); do
	jobname="GF_${TARNAME}-${NDIR}-${set_index}"
	jobfile="${TMPDIR}/${jobname}.xml"

	echo ${jobname}

	echo "<Request>"                                                                   > ${jobfile}
	echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
	echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
	echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
	echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
	echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
	jobtime="8" # hours
	echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
	echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
	echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
	echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
	# set inputs
	thebinary1="${GSTDIR}/bin/GetSimpleTuple_sim"
	thebinary2="${FNCDIR}/bin/FilterNCombine_sim"
	execfile="${VLTLDIR}/analysis-omega/sh/run_GF_sim.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"GetSimpleTuple_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_GF_sim.sh\"/>"                   >> ${jobfile}
       	# arrange set limits
	NFILES_BEGIN=$(($set_index*25)) # rn starts at 00
	diff=25
	if [[ $set_index == $(($nsets-1)) ]]; then diff=$(($NFILES-$NFILES_BEGIN)); fi
	NFILES_END=$(($NFILES_BEGIN + $diff - 1))
	# set input files
	for ((COUNTER=${NFILES_BEGIN}; COUNTER<=${NFILES_END}; COUNTER++)); do
	    RN=$(get_num_2dig $COUNTER)
	    inrootfile="${SIMDIR}/recsis${TARNAME}_${RN}.root"
	    echo "  <Input src=\"${inrootfile}\" dest=\"recsis${TARNAME}_${RN}.root\" copyOption=\"link\"/>" >> ${jobfile}
	done
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^SETOPTION=|SETOPTION=${SETOPTION}|g\" run_GF_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_GF_sim.sh"              >> ${jobfile}
	echo "    sed -i \"s|^NFILES_BEGIN=|NFILES_BEGIN=${NFILES_BEGIN}|g\" run_GF_sim.sh" >> ${jobfile}
	echo "    sed -i \"s|^NFILES_END=|NFILES_END=${NFILES_END}|g\" run_GF_sim.sh"       >> ${jobfile}
	echo "    chmod 755 ./run_GF_sim.sh"                                              >> ${jobfile}
	echo "    sh run_GF_sim.sh"                                                       >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set output files
	for ((COUNTER=${NFILES_BEGIN}; COUNTER<=${NFILES_END}; COUNTER++)); do
	    RN=$(get_num_2dig $COUNTER)
	    outrootfile1="${OUDIR1}/pruned${TARNAME}_${RN}.root"
	    outrootfile2="${OUDIR2}/comb${TARNAME}_${RN}.root"
	    echo "  <Output src=\"pruned${TARNAME}_${RN}.root\" dest=\"${outrootfile1}\"/>" >> ${jobfile}
	    echo "  <Output src=\"comb${TARNAME}_${RN}.root\"   dest=\"${outrootfile2}\"/>" >> ${jobfile}
	done
	# set logs
	echo "  <Stdout dest=\"${TMPDIR}/${jobname}.out\"/>"                              >> ${jobfile}
	echo "  <Stderr dest=\"${TMPDIR}/${jobname}.err\"/>"                              >> ${jobfile}
	echo "  <Job>"                                                                    >> ${jobfile}
	echo "  </Job>"                                                                   >> ${jobfile}
	echo "</Request>"                                                                 >> ${jobfile}

	echo "Submitting job: ${jobfile}"
	jsub --xml ${jobfile}
    done
fi
