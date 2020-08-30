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

function get_num()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="00$sr"
  elif [[ $sr -lt 100 ]]; then
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
jobtrack="debug" # "debug" or "analysis"
jobos="general"
#jobname=
jobtime="1" # hour
jobspace="1" # GB
jobmemory="1" # GB
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
echo "  <TimeLimit time=\"${jobtime}\" unit=\"hours\"/>"                          >> ${jobfile}
echo "  <DiskSpace space=\"${jobspace}\" unit=\"GB\"/>"                           >> ${jobfile}
echo "  <Memory space=\"${jobmemory}\" unit=\"GB\"/>"                             >> ${jobfile}
echo "  <CPU core=\"1\"/>"                                                        >> ${jobfile}
# define input files
runscript="${PRODIR}/sh/jlab/run_split.sh"
realscript="/home/borquez/volatile/hsplit/hsplit.sh" # good
thefile="${INDIR}/${nDir}/recsis${tarName}_${runNumber}.root"
# move input files to node dir
echo "  <Input src=\"${runscript}\"  dest=\"run_split.sh\"/>"                     >> ${jobfile}
echo "  <Input src=\"${realscript}\" dest=\"hsplit.sh\"/>"                        >> ${jobfile}
echo "  <Input src=\"${thefile}\"    dest=\"recsis.root\"/>"                      >> ${jobfile}
# set command
echo "  <Command><![CDATA["                                                       >> ${jobfile}
echo "    sed -i \"s|^optionA=|optionA=--F|g\"         run_split.sh"              >> ${jobfile}
echo "    sed -i \"s|^optionB=|optionB=35|g\"          run_split.sh"              >> ${jobfile} # updated!
echo "    sed -i \"s|^optionC=|optionC=recsis.root|g\" run_split.sh"              >> ${jobfile}
echo "    chmod 755 ./run_split.sh"                                               >> ${jobfile}
echo "    sh run_split.sh"                                                        >> ${jobfile}
echo "  ]]></Command>"                                                            >> ${jobfile}
# define and make output dirs
REALOUDIR=$OUDIR/$nDir
mkdir -p $REALOUDIR
outfile1=$REALOUDIR/recsis${tarName}_${runNumber}_01.root
outfile2=$REALOUDIR/recsis${tarName}_${runNumber}_02.root
outfile3=$REALOUDIR/recsis${tarName}_${runNumber}_03.root
# move output files from node dir
echo "  <Output src=\"recsis_01.root\" dest=\"${outfile1}\"/>"                    >> ${jobfile}
echo "  <Output src=\"recsis_02.root\" dest=\"${outfile2}\"/>"                    >> ${jobfile}
echo "  <Output src=\"recsis_03.root\" dest=\"${outfile3}\"/>"                    >> ${jobfile}
echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
echo "  <Job>"                                                                    >> ${jobfile}
echo "  </Job>"                                                                   >> ${jobfile}
echo "</Request>"                                                                 >> ${jobfile}

echo "Submitting job: ${jobfile}"
jsub --xml ${jobfile}
