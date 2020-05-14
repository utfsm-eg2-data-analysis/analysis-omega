#!/bin/bash

function print_help()
{
  printf "#######################################################################\n";
  printf "Usage:\n";
  printf "./run_omegaSim.sh --mode <mode> --Nevts <Nevts> --targ <targ> --pid <pid> --run1 <run1> --run2 <run2>\n";
  printf "where:\n";
  printf "<mode>  = 0 (interactive), 1 (farm)\n";
  printf "<Nevts> = number of events to generate\n";
  printf "<targ> = 0, 1, 2, 3, Where: (0,1,2,3,4) <==> (\"D\", \"C\", \"Fe\", \"Pb\")\n";
  printf "<pid> = pid of detected particle. eg. 223(221) for omega(eta)\n";
  printf "<run1,run2> = integers >=0 to loop over\n";
  printf "eg: ./run_omegaSim.sh --mode 0 --Nevts 100 --targ 0 --pid 223 --run1 0 --run2 0\n";
  printf "#######################################################################\n";

  exit 1;
}

#######################################################################

function process_args()
{
  arr=("$@")
  ic=0
  while [ $ic -le $((${#arr[@]}-1)) ]; do
    if [ "${arr[$ic]}" == "--mode" ]; then
      mode=${arr[$((ic+1))]}
    elif [ "${arr[$ic]}" == "--Nevts" ]; then
      Nevts=${arr[$((ic+1))]}
    elif [ "${arr[$ic]}" == "--targ" ]; then
      targ=${arr[$((ic+1))]}
    elif [ "${arr[$ic]}" == "--pid" ]; then
      pid=${arr[$((ic+1))]}
    elif [ "${arr[$ic]}" == "--run1" ]; then
      run1=${arr[$((ic+1))]}
    elif [ "${arr[$ic]}" == "--run2" ]; then
      run2=${arr[$((ic+1))]}
    else
      printf "*** Aborting: Unrecognized argument: ${arr[$((ic))]} ***\n\n";
      print_help;
    fi
    ((ic+=2))
  done
}

#######################################################################

function check_args()
{
  if [ $mode -ne 0 -a $mode -ne 1 ]; then
    printf "*** Aborting: wrong mode value. Possible values are 0 or 1 ***\n\n";
    print_help;
  fi

  if [ $Nevts -le 0 ]; then
    printf "*** Aborting: Number of events should be positive ***\n\n";
    print_help;
  fi

  if [ $targ -lt 0 -o $targ -gt 4 ]; then
    printf "*** Aborting: unrecognized target. Possible values are 0, 1, 2, 3, 4 ***\n\n";
    print_help;
  fi

#  if [ $pid -ne 223 -a $pid -ne 221 ]; then
#    printf "*** Aborting: unrecognized pid. Possible values are 223 ***\n\n";
#    print_help;
#  fi

  if [ $run1 -lt 0 -o $run2 -lt 0 ]; then
    printf "*** Aborting: Run number should be >= 0 ***\n\n";
    print_help;
  fi
}

#######################################################################

function print_args()
{
  echo mode:    $mode
  echo Nevts:   $Nevts
  echo targ:    $targ
  echo pid:     $pid
  echo run1:    $run1
  echo run2:    $run2
}

#######################################################################

function get_run()
{
  sr=$1
  srn=""
  if [ $sr -lt 10 ]; then
    srn="000$sr"
  elif [ $sr -lt 100 ]; then
    srn="00$sr"
  elif [ $sr -lt 1000 ]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

#######################################################################
###############################          ##############################
###############################   Main   ##############################
###############################          ##############################
#######################################################################

NARGS=12
if [ $# -ne $NARGS ]; then
  echo "Missing arguments. You provided $# args. It should be $NARGS.\n"
  print_help;
fi

argArray=("$@")
process_args "${argArray[@]}"
check_args
print_args

TOPOUDIR="/volatile/clas/claseg2/borquez/omegaSim"
SIMINDIR="/home/${USER}/simul_files"
if [ ! -d $SIMINDIR ]; then
  printf "Directory SIMINDIR:$SIMINDIR does not exist\n"
  exit 1
fi

sedi="sed -i "
targName=("D"   "C"   "Fe"   "Pb")
targType=("lt"  "st"  "st"  "st")
targA=(    2     12    56    208)
targZ=(    1     6     28    82)
targZpos=( -30   -25   -25   -25)
targVG2=(  1     2     2       2)

tarA="${targA[$targ]}"
tarZ="${targZ[$targ]}"
tarZpos="${targZpos[$targ]}"
tarVG2="${targVG2[$targ]}"
tarName="${targName[$targ]}"
tarType="${targType[$targ]}"

simfile="omegaSim${tarName}.sh"

leptobosfile=lepto${tarName}.A00
leptologfile=lepto${tarName}.log
leptoinfile=lepto${tarName}.txt

ffreadfile="ffread_eg2${tarName}_${tarType}.gsim"
gsimbosfile=gsim${tarName}.A00
gsimlogfile=gsim${tarName}.log

gppbosfile=gpp${tarName}.A00
gppntpfile=gpp${tarName}.hbook
gpplogfile=gpp${tarName}.log

tclfile=recsis${tarName}.tcl
rechisfile=recsis${tarName}_histos.hbook
recntpfile=recsis${tarName}.hbook
recbosfile=recsis${tarName}.A00
reclogfile=recsis${tarName}.log
recsislogfile=recsis${tarName}_log.log

recrootfile=recsis${tarName}.root
wrdstlogfile=WriteRootDst${tarName}.log

#Check if input files exist
if [ ! -f ${SIMINDIR}/omegaSim.sh ]; then
  echo "${SIMINDIR}/omegaSim.sh does not exist"
  exit 1
fi

if [ ! -f ${SIMINDIR}/ffread_eg2.gsim ]; then
  echo "${SIMINDIR}/ffread_eg2.gsim does not exist"
  exit 1
fi

if [ ! -f ${SIMINDIR}/leptotxt.pl ]; then
  echo "${SIMINDIR}/leptotxt.pl does not exist"
  exit 1
fi

if [ ! -f ${SIMINDIR}/recsis_eg2.tcl ]; then
  echo "${SIMINDIR}/recsis_eg2.tcl does not exist"
  exit 1
fi

for (( ir=$run1; ir<=$run2; ir++ )); do
  printf "\n";
  srun=$(get_run "$ir")
  run="run${srun}"

  if [ "${mode}" == "0" ]; then

    IFARMDIR="${TOPOUDIR}/ifarm/${tarName}/${run}"
    OUDIR="${TOPOUDIR}/output/${tarName}"
    mkdir -p ${IFARMDIR}
    cd ${IFARMDIR}
    cp ${SIMINDIR}/omegaSim.sh     ${IFARMDIR}/${simfile}
    cp ${SIMINDIR}/ffread_eg2.gsim ${IFARMDIR}/${ffreadfile}
    cp ${SIMINDIR}/recsis_eg2.tcl  ${IFARMDIR}/${tclfile}

    $sedi "s|^Nevts=|Nevts=${Nevts}|g"           ${simfile}
    $sedi "s|^pid=|pid=${pid}|g"                 ${simfile}
    $sedi "s|^targ=|targ=${targ}|g"              ${simfile}
    $sedi "s|^SIMINDIR=|SIMINDIR=${SIMINDIR}|g"  ${simfile}

    chmod 755 ./${simfile}
    ./${simfile}

  elif [ "${mode}" == "1" ]; then

    FARMDIR="${TOPOUDIR}/farm/${tarName}/${run}"
    OUDIR="${TOPOUDIR}/output/${tarName}"
    mkdir -p ${FARMDIR}
    cd ${FARMDIR}

    jobfile="${FARMDIR}/job_omega.xml"
    proj="eg2a"
    track="analysis"
    mail="andres.borquez.14@sansano.usm.cl"
    time="240"
    diskspace="500"
    memusage="1000"
    osname="general"
    jobname=omegaSim${tarName}_${srun}

    echo "<Request>"                                                                       > $jobfile
    echo "  <Project name=\"$proj\"></Project>"                                           >> $jobfile
    echo "  <Track name=\"$track\"></Track>"                                              >> $jobfile
    echo "  <Email email=\"$mail\" request=\"true\" job=\"true\"/>"                       >> $jobfile
    echo "  <TimeLimit time=\"$time\" unit=\"minutes\"></TimeLimit>"                      >> $jobfile
    echo "  <DiskSpace space=\"$diskspace\" unit=\"MB\"></DiskSpace>"                     >> $jobfile
    echo "  <Memory space=\"$memusage\" unit=\"MB\"></Memory>"                            >> $jobfile
    echo "  <CPU core=\"1\"></CPU>"                                                       >> $jobfile
    echo "  <OS name=\"$osname\"></OS>"                                                   >> $jobfile
    echo "  <Job>"                                                                        >> $jobfile
    echo "    <Name name=\"${jobname}\"></Name>"                                          >> $jobfile
    echo "    <Input src=\"file:${SIMINDIR}/omegaSim.sh\"      dest=\"${simfile}\"/>"     >> $jobfile
    echo "    <Input src=\"file:${SIMINDIR}/leptotxt.pl\"      dest=\"leptotxt.pl\"/>"    >> $jobfile
    echo "    <Input src=\"file:${SIMINDIR}/ffread_eg2.gsim\"  dest=\"${ffreadfile}\"/>"  >> $jobfile
    echo "    <Input src=\"file:${SIMINDIR}/recsis_eg2.tcl\"   dest=\"${tclfile}\"/>"     >> $jobfile
    echo "    <Command><![CDATA["                                                         >> $jobfile
    echo "      $sedi \"s|^Nevts=|Nevts=${Nevts}|g\"           ${simfile}"                >> $jobfile
    echo "      $sedi \"s|^pid=|pid=${pid}|g\"                 ${simfile}"                >> $jobfile
    echo "      $sedi \"s|^targ=|targ=${targ}|g\"              ${simfile}"                >> $jobfile
    echo "      $sedi \"s|^SIMINDIR=|SIMINDIR=${SIMINDIR}|g\"  ${simfile}"                >> $jobfile
    echo "      chmod 755 ./${simfile}"                                                   >> $jobfile
    echo "      sh ${simfile}"                                                            >> $jobfile
    echo "    ]]></Command>"                                                              >> $jobfile
    #echo "    <Output src=\"${leptoinfile}\"    dest=\"${FARMDIR}/${leptoinfile}\"/>"       >> $jobfile
    #echo "    <Output src=\"${simfile}\"        dest=\"${FARMDIR}/${simfile}\"/>"           >> $jobfile
    #echo "    <Output src=\"${ffreadfile}\"     dest=\"${FARMDIR}/${ffreadfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${tclfile}\"        dest=\"${FARMDIR}/${tclfile}\"/>"           >> $jobfile
    #echo "    <Output src=\"${leptobosfile}\"   dest=\"${FARMDIR}/${leptobosfile}\"/>"      >> $jobfile
    #echo "    <Output src=\"${leptologfile}\"   dest=\"${FARMDIR}/${leptologfile}\"/>"      >> $jobfile
    #echo "    <Output src=\"${gsimbosfile}\"    dest=\"${FARMDIR}/${gsimbosfile}\"/>"       >> $jobfile
    #echo "    <Output src=\"${gsimlogfile}\"    dest=\"${FARMDIR}/${gsimlogfile}\"/>"       >> $jobfile
    #echo "    <Output src=\"${gppbosfile}\"     dest=\"${FARMDIR}/${gppbosfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${gppntpfile}\"     dest=\"${FARMDIR}/${gppntpfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${gpplogfile}\"     dest=\"${FARMDIR}/${gpplogfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${rechisfile}\"     dest=\"${FARMDIR}/${rechisfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${recntpfile}\"     dest=\"${FARMDIR}/${recntpfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${recbosfile}\"     dest=\"${FARMDIR}/${recbosfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${reclogfile}\"     dest=\"${FARMDIR}/${reclogfile}\"/>"        >> $jobfile
    #echo "    <Output src=\"${recsislogfile}\"  dest=\"${FARMDIR}/${recsislogfile}\"/>"     >> $jobfile
    echo "    <Output src=\"${recrootfile}\"    dest=\"${FARMDIR}/${recrootfile}\"/>"      >> $jobfile
    #echo "    <Output src=\"${wrdstlogfile}\"   dest=\"${FARMDIR}/${wrdstlogfile}\"/>"      >> $jobfile
    #echo "    <Stdout dest=\"${FARMDIR}/job${tarName}.out\"></Stdout>"                      >> $jobfile
    #echo "    <Stderr dest=\"${FARMDIR}/job${tarName}.err\"></Stderr>"                      >> $jobfile
    echo "  </Job>"                                                                       >> $jobfile
    echo "</Request>"                                                                     >> $jobfile

    echo "Running job $jobfile..."
    jsub --xml $jobfile

  fi
done
