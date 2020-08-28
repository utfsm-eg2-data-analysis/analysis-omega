#!/bin/bash

####################################################################################################################################
# ./gett.sh <tape file> <output dir>                                                                                               #
#     both parameters must be absolute locations                                                                                   #
#                                                                                                                                  #
# EG: ./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_01.root /home/borquez/volatile/omegaSim/output/D/43/ #
####################################################################################################################################

# Script to get files from tape as auger jobs
# (exclusive for my simulation files!)

#####
# Input
###

inputArray=("$@")

INFILE="${inputArray[0]}"
OUDIR="${inputArray[1]}"

#####
# Main
###

# set env
source ~/.bashrc
cd ${PRODIR}

XMLDIR=${PRODIR}/xml/gett/
mkdir -p $XMLDIR

# declaration of variables
#jobfile=
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
jobtime="30" # minutes
jobspace="1" # GB
jobmemory="512" # MB

# strings processing
basename="${INFILE##*/}"
tarName="${basename#recsis}"
tarName="${tarName%_*}"
runNumber="${basename%.root}"
runNumber="${runNumber##*_}"
dirname="${INFILE%/*}"
nDir="${dirname##*/}"

jobname="gett_${tarName}-${nDir}_${runNumber}"
jobfile="${XMLDIR}/${jobname}.xml"

echo ${jobname}

echo "<Request>"                                                            > ${jobfile}
echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"      >> ${jobfile}
echo "  <Project name=\"${jobproject}\"/>"                                 >> ${jobfile}
echo "  <Track name=\"${jobtrack}\"/>"                                     >> ${jobfile}
echo "  <OS name=\"${jobos}\"/>"                                           >> ${jobfile}
echo "  <Name name=\"${jobname}\"/>"                                       >> ${jobfile}
echo "  <TimeLimit time=\"${jobtime}\" unit=\"minutes\"/>"                 >> ${jobfile}
echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                    >> ${jobfile}
echo "  <Memory space=\"${jobmemory}\" unit=\"MB\"/>"                      >> ${jobfile}
echo "  <CPU core=\"1\"/>"                                                 >> ${jobfile}
# set input
echo "  <Input src=\"mss:${INFILE}\" dest=\"${basename}\"/>"               >> ${jobfile}
# command empty
echo "  <Command><![CDATA["                                                >> ${jobfile}
echo "    ls -lrth ${basename}"                                            >> ${jobfile}
echo "  ]]></Command>"                                                     >> ${jobfile}
# set outputs
echo "  <Output src=\"${basename}\" dest=\"${OUDIR}/${basename}\"/>"       >> ${jobfile}
echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                       >> ${jobfile}
echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                       >> ${jobfile}
echo "  <Job>"                                                             >> ${jobfile}
echo "  </Job>"                                                            >> ${jobfile}
echo "</Request>"                                                          >> ${jobfile}

echo "Submitting job: ${jobfile}"
jsub --xml ${jobfile}

