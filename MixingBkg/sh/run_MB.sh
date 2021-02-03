#!/bin/bash

##############################################################
# ./run_MB.sh <target>                                       #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./run_MB.sh                                            #
#     ./run_MB.sh Fe                                         #
#     ./run_MB.sh Pb                                         #
##############################################################

# Only works for data!

#####
# Input
###

TARNAME="$@"

#####
# Main
###

# set env
source ~/.bashrc

# set main dirs
REDDIR=${WORKDIR}/out/GST_Reduced/data/${TARNAME}
MIXDIR=${VLTLDIR}/analysis-omega/MixingBkg/bin
OUTDIR=${WORKDIR}/out/MixingBkg/data/${TARNAME}
mkdir -p ${OUTDIR} # just in case

cp -v ${MIXDIR}/MixingBkg ${REDDIR} # copy binary to REDDIR

cd ${REDDIR}
for file in *.root; do
    file2=${file#*_}
    RN=${file2//.root}
    ./MixingBkg -t${TARNAME} -r${RN} # execute program
    mv -v bkgmix${TARNAME}_${RN}.root ${OUTDIR}/ # move output file to outdir
done

rm -v ${REDDIR}/MixingBkg
