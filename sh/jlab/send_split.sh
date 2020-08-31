#!/bin/bash

##############################################################
# ./send_split.sh <target> <ndir> <rn>                       #
#     <target> = (D, C, Fe, Pb)                              #
#     <ndir>   = (001, 002, ...)                             #
#     <rn>     = (00 - 99)                                   #
#                                                            #
# EG: ./send_split.sh C 006 99                               #
##############################################################

# Exclusive for JLAB cluster

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

inputArray=("$@")

tarName="${inputArray[0]}"
nDir="${inputArray[1]}"
runNumber="${inputArray[2]}"

#####
# Main
###

# set env
source ~/.bashrc

INDIR=/home/borquez/volatile/omegaSim/output/$tarName
OUDIR=/home/borquez/volatile/omegaSim/output/$(echo "${tarName}2")
XMLDIR=${PRODIR}/xml/split/${tarName}/${nDir}

# just in case
mkdir -p $OUDIR
mkdir -p $XMLDIR

# declaration of variables
#jobfile=
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="analysis" # "debug" or "analysis"
jobos="general"
#jobname=
jobtime="15" # minutes
jobspace="1" # GB
jobmemory="512" # MB
#inrootfile=
#outrootfile=
jobname="SPLIT_${tarName}-${nDir}-${runNumber}"
jobfile="${XMLDIR}/${jobname}.xml"

echo ${jobname}

echo "<Request>"                                                                   > ${jobfile}
echo "  <Email email=\"${jobemail}\" request=\"true\" job=\"true\"/>"             >> ${jobfile}
echo "  <Project name=\"${jobproject}\"/>"                                        >> ${jobfile}
echo "  <Track name=\"${jobtrack}\"/>"                                            >> ${jobfile}
echo "  <OS name=\"${jobos}\"/>"                                                  >> ${jobfile}
echo "  <Name name=\"${jobname}\"/>"                                              >> ${jobfile}
echo "  <TimeLimit time=\"${jobtime}\" unit=\"minutes\"/>"                        >> ${jobfile}
echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
echo "  <Memory space=\"${jobmemory}\" unit=\"MB\"/>"                             >> ${jobfile}
echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
# define input files
runscript="${PRODIR}/sh/jlab/run_split.sh"
realscript="/home/borquez/volatile/hsplit/hsplit.sh" # good
thefile="${INDIR}/${nDir}/recsis${tarName}_${runNumber}.root"
# move input files to node dir
echo "  <Input src=\"${runscript}\"  dest=\"run_split.sh\"/>"                     >> ${jobfile}
echo "  <Input src=\"${realscript}\" dest=\"hsplit.sh\"/>"                        >> ${jobfile}
echo "  <Input src=\"${thefile}\"    dest=\"recsis.root\"/>"                      >> ${jobfile}
# how many files do you desire? hardcoded
howmany=35
# set command
echo "  <Command><![CDATA["                                                       >> ${jobfile}
echo "    sed -i \"s|^optionA=|optionA=--F|g\"         run_split.sh"              >> ${jobfile}
echo "    sed -i \"s|^optionB=|optionB=${howmany}|g\"  run_split.sh"              >> ${jobfile}
echo "    sed -i \"s|^optionC=|optionC=recsis.root|g\" run_split.sh"              >> ${jobfile}
echo "    chmod 755 ./run_split.sh"                                               >> ${jobfile}
echo "    sh run_split.sh"                                                        >> ${jobfile}
echo "  ]]></Command>"                                                            >> ${jobfile}
# define and make output dirs
REALOUDIR=$OUDIR/$nDir
mkdir -p $REALOUDIR
# loop for future split files
for ((counter=1; counter <= $howmany; counter++)); do
    scounter=$(get_num_2dig $counter)
    outfile=$REALOUDIR/recsis${tarName}_${runNumber}_${scounter}.root
    # move output files from node dir
    echo "  <Output src=\"recsis_${scounter}.root\" dest=\"${outfile}\"/>"        >> ${jobfile}
done
echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
echo "  <Job>"                                                                    >> ${jobfile}
echo "  </Job>"                                                                   >> ${jobfile}
echo "</Request>"                                                                 >> ${jobfile}

echo "Submitting job: ${jobfile}"
jsub --xml ${jobfile}
