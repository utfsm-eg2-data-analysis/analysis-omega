#!/bin/bash

##############################################################
# ./send_RE_sim.sh <set> <target> <ndir>                     #
#     <set>    = (old, usm, jlab)                            #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (00, 01, 02, ...)                           #
#                                                            #
# EG: ./send_RE_sim.sh old Fe                                #
#     ./send_RE_sim.sh usm D                                 #
#     ./send_RE_sim.sh jlab Pb 00                            #
##############################################################

# RE stands for Reductor-EventMixing

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
REDDIR=${VLTLDIR}/analysis-omega/Reductor
FNCDIR=${VLTLDIR}/analysis-omega/FilterNCombine
if [[ "$SETOPTION" == "jlab" ]]; then
    INDIR=${WORKDIR}/out/GetSimpleTuple/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR1=${WORKDIR}/out/Reductor/${SETOPTION}/${TARNAME}/${NDIR}
    OUDIR2=${WORKDIR}/out/EventMixing/${SETOPTION}/${TARNAME}/${NDIR}
else
    INDIR=${WORKDIR}/out/GetSimpleTuple/${SETOPTION}/${TARNAME}
    OUDIR1=${WORKDIR}/out/Reductor/${SETOPTION}/${TARNAME}
    OUDIR2=${WORKDIR}/out/EventMixing/${SETOPTION}/${TARNAME}
fi
mkdir -p ${TMPDIR} ${OUDIR1} ${OUDIR2}

# obtain run numbers
NFILES=$(ls -1 ${INDIR} | wc -l)

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime= # different for (old,usm) vs (jlab)
jobspace= # different for (old,usm) vs (jlab)
jobmemory="3" # GB

if [[ "${SETOPTION}" == "old" || "${SETOPTION}" == "usm" ]]; then
    for ((COUNTER=1; COUNTER <= $NFILES; COUNTER++)); do
	RN=$(get_num_2dig $COUNTER) # starts at 01
	
	jobname="RE_${SETOPTION}-${TARNAME}_${RN}"
	jobfile="${TMPDIR}/${jobname}.xml"

	echo ${jobname}

	echo "<Request>"                                                                   > ${jobfile}
	echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
	echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
	echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
	echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
	echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
	jobtime="4" # hours
	echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
	jobspace="1" # GB
	echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
	echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
	echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
	# set inputs
	thebinary1="${REDDIR}/bin/Reductor"
	thebinary2="${FNCDIR}/bin/FilterNCombine_sim"
	execfile="${VLTLDIR}/analysis-omega/sh/run_RE_sim.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"Reductor\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_RE_sim.sh\"/>"                   >> ${jobfile}
	inrootfile="${INDIR}/pruned${TARNAME}_${RN}.root"
	echo "  <Input src=\"${inrootfile}\" dest=\"pruned${TARNAME}_${RN}.root\" copyOption=\"link\"/>"      >> ${jobfile}
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^SETOPTION=|SETOPTION=${SETOPTION}|g\" run_RE_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\"       run_RE_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^RN=|RN=${RN}|g\"                      run_RE_sim.sh"        >> ${jobfile}
	echo "    chmod 755 ./run_RE_sim.sh"                                              >> ${jobfile}
	echo "    sh run_RE_sim.sh"                                                       >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set outputs for out/Reductor
	outrootfileA="${OUDIR1}/pruned${TARNAME}_${RN}_red.root"
	outrootfileB="${OUDIR1}/pruned${TARNAME}_${RN}_red_MC.root"
	# set outputs for out/EventMixing
	outrootfile1="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPip.root"
	outrootfile2="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPim.root"
	outrootfile3="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPi0.root"
	outrootfile4="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sAll.root"
	outrootfile5="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPip.root"
	outrootfile6="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPim.root"
	outrootfile7="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPi0.root"
	outrootfile8="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sAll.root"
	# extract outputs to out/Reductor
	echo "  <Output src=\"pruned${TARNAME}_${RN}_red.root\" dest=\"${outrootfileA}\"/>"   >> ${jobfile}
	echo "  <Output src=\"pruned${TARNAME}_${RN}_red_MC.root\" dest=\"${outrootfileB}\"/>"   >> ${jobfile}
	# extract outputs to out/EventMixing
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPip.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPim.root\" dest=\"${outrootfile2}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPi0.root\" dest=\"${outrootfile3}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sAll.root\" dest=\"${outrootfile4}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPip.root\" dest=\"${outrootfile5}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPim.root\" dest=\"${outrootfile6}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPi0.root\" dest=\"${outrootfile7}\"/>"   >> ${jobfile}
	echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sAll.root\" dest=\"${outrootfile8}\"/>"   >> ${jobfile}
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
	jobname="RE_${TARNAME}-${NDIR}-${set_index}"
	jobfile="${TMPDIR}/${jobname}.xml"

	echo ${jobname}

	echo "<Request>"                                                                   > ${jobfile}
	echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
	echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
	echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
	echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
	echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
	jobtime="12" # hours
	echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
	jobspace="12" # GB
	echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
	echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
	echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
	# set inputs
	thebinary1="${REDDIR}/bin/Reductor"
	thebinary2="${FNCDIR}/bin/FilterNCombine_sim"
	execfile="${VLTLDIR}/analysis-omega/sh/run_RE_sim.sh"
	echo "  <Input src=\"${thebinary1}\"  dest=\"Reductor\"/>"              >> ${jobfile}
	echo "  <Input src=\"${thebinary2}\"  dest=\"FilterNCombine_sim\"/>"              >> ${jobfile}
	echo "  <Input src=\"${execfile}\"    dest=\"run_RE_sim.sh\"/>"                   >> ${jobfile}
       	# arrange set limits
	NFILES_BEGIN=$(($set_index*25)) # rn starts at 00
	diff=25
	if [[ $set_index == $(($nsets-1)) ]]; then diff=$(($NFILES-$NFILES_BEGIN)); fi
	NFILES_END=$(($NFILES_BEGIN + $diff - 1))
	# prevent giant initial files
	if [[ "${set_index}" == "0" && "${NDIR}" == "00" ]]; then
	    if [[ "${TARNAME}" == "D" || "${TARNAME}" == "C" || "${TARNAME}" == "Fe" ]]; then
		NFILES_BEGIN=6		
	    fi
	fi
	# set input files
	for ((COUNTER=${NFILES_BEGIN}; COUNTER<=${NFILES_END}; COUNTER++)); do
	    RN=$(get_num_2dig $COUNTER)
	    inrootfile="${INDIR}/pruned${TARNAME}_${RN}.root"
	    echo "  <Input src=\"${inrootfile}\" dest=\"pruned${TARNAME}_${RN}.root\" copyOption=\"link\"/>" >> ${jobfile}
	done
	# set command
	echo "  <Command><![CDATA["                                                       >> ${jobfile}
	echo "    sed -i \"s|^SETOPTION=|SETOPTION=${SETOPTION}|g\" run_RE_sim.sh"        >> ${jobfile}
	echo "    sed -i \"s|^TARNAME=|TARNAME=${TARNAME}|g\" run_RE_sim.sh"              >> ${jobfile}
	echo "    sed -i \"s|^NFILES_BEGIN=|NFILES_BEGIN=${NFILES_BEGIN}|g\" run_RE_sim.sh" >> ${jobfile}
	echo "    sed -i \"s|^NFILES_END=|NFILES_END=${NFILES_END}|g\" run_RE_sim.sh"       >> ${jobfile}
	echo "    chmod 755 ./run_RE_sim.sh"                                              >> ${jobfile}
	echo "    sh run_RE_sim.sh"                                                       >> ${jobfile}
	echo "  ]]></Command>"                                                            >> ${jobfile}
	# set output files
	for ((COUNTER=${NFILES_BEGIN}; COUNTER<=${NFILES_END}; COUNTER++)); do
	    RN=$(get_num_2dig $COUNTER)
	    # set outputs for out/Reductor
	    outrootfileA="${OUDIR1}/pruned${TARNAME}_${RN}_red.root"
	    outrootfileB="${OUDIR1}/pruned${TARNAME}_${RN}_red_MC.root"
	    # set outputs for out/EventMixing
	    outrootfile1="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPip.root"
	    outrootfile2="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPim.root"
	    outrootfile3="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sPi0.root"
	    outrootfile4="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_sAll.root"
	    outrootfile5="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPip.root"
	    outrootfile6="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPim.root"
	    outrootfile7="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sPi0.root"
	    outrootfile8="${OUDIR2}/bkgmix${TARNAME}_${RN}_red_MC_sAll.root"
	    # extract outputs to out/Reductor
	    echo "  <Output src=\"pruned${TARNAME}_${RN}_red.root\" dest=\"${outrootfileA}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"pruned${TARNAME}_${RN}_red_MC.root\" dest=\"${outrootfileB}\"/>"   >> ${jobfile}
	    # extract outputs to out/EventMixing
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPip.root\" dest=\"${outrootfile1}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPim.root\" dest=\"${outrootfile2}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sPi0.root\" dest=\"${outrootfile3}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_sAll.root\" dest=\"${outrootfile4}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPip.root\" dest=\"${outrootfile5}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPim.root\" dest=\"${outrootfile6}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sPi0.root\" dest=\"${outrootfile7}\"/>"   >> ${jobfile}
	    echo "  <Output src=\"bkgmix${TARNAME}_${RN}_red_MC_sAll.root\" dest=\"${outrootfile8}\"/>"   >> ${jobfile}
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
