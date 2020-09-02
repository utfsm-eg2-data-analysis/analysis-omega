#!/bin/bash

##############################################################
# ./send_f1.sh <target>                                      #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./send_f1.sh C                                         #
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

function get_num_3dig()
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

tarName="$@"

#####
# Main
###

# set env
source ~/.bashrc
cd ${PRODIR}

# define important dirs
DATADIR=${PRODIR}/out/GetSimpleTuple/data/${tarName}
XMLDIR=${PRODIR}/xml/f1/${tarName}
OUDIR=${PRODIR}/out/FilterNCombine/f1/${tarName}

mkdir -p ${XMLDIR}
mkdir -p ${OUDIR}

# set input option
if [[ ${tarName} = "C" ]]; then
    rnlist=${PRODIR}/include/C-thickD2rn.txt
elif [[ ${tarName} = "Fe" ]]; then
    rnlist=${PRODIR}/include/Fe-thickD2rn.txt
elif [[ ${tarName} = "Pb" ]]; then
    rnlist=${PRODIR}/include/Pb-thinD2rn.txt
fi
nfiles=$(wc -l < ${rnlist})

# declaration of variables
jobemail="andres.borquez.14@sansano.usm.cl"
jobproject="eg2a"
jobtrack="debug" # "debug" or "analysis"
jobos="general"
jobtime="2" # hours
jobspace="1" # GB
jobmemory="2" # GB
thebinary="${PRODIR}/bin/FilterNCombine_f1"
execfile="${PRODIR}/sh/jlab/run_f1.sh"

for ((COUNTER=1; COUNTER <= 10; COUNTER++)); do # "10" or "${nfiles}"
    # update rn value
    rn=$(sed -n "$COUNTER{p;q}" $rnlist) # data from rnlist

    # setting jobname
    jobname="f1-${tarName}_${rn}"
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
    # set inputs
    echo "  <Input src=\"${thebinary}\"  dest=\"FilterNCombine_f1\"/>"                >> ${jobfile}
    echo "  <Input src=\"${execfile}\"   dest=\"run_f1.sh\"/>"                        >> ${jobfile}
    inrootfile="${DATADIR}/pruned${tarName}_${rn}.root"
    echo "  <Input src=\"${inrootfile}\" dest=\"pruned${tarName}_${rn}.root\"/>"      >> ${jobfile}
    # set command
    echo "  <Command><![CDATA["                                                       >> ${jobfile}
    echo "    sed -i \"s|^tarName=|tarName=${tarName}|g\" run_f1.sh"                  >> ${jobfile}
    echo "    sed -i \"s|^rn=|rn=${rn}|g\" run_f1.sh"                                 >> ${jobfile}
    echo "    chmod 755 ./run_f1.sh"                                                  >> ${jobfile}
    echo "    sh run_f1.sh"                                                           >> ${jobfile}
    echo "  ]]></Command>"                                                            >> ${jobfile}
    # set outputs
    outrootfile="${OUDIR}/comb${tarName}_${rn}.root"
    echo "  <Output src=\"comb${tarName}_${rn}.root\" dest=\"${outrootfile}\"/>"      >> ${jobfile}
    echo "  <Stdout dest=\"${XMLDIR}/${jobname}.out\"/>"                              >> ${jobfile}
    echo "  <Stderr dest=\"${XMLDIR}/${jobname}.err\"/>"                              >> ${jobfile}
    echo "  <Job>"                                                                    >> ${jobfile}
    echo "  </Job>"                                                                   >> ${jobfile}
    echo "</Request>"                                                                 >> ${jobfile}

    echo "Submitting job: ${jobfile}"
    jsub --xml ${jobfile}
done
