#!/bin/bash

##############################################################
# ./run_R.sh <target>                                        #
#     <target> = (C, Fe, Pb)                                 #
#                                                            #
# EG: ./run_R.sh C                                           #
#     ./run_R.sh Fe                                          #
#     ./run_R.sh Pb                                          #
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
GSTDIR=${WORKDIR}/out/GetSimpleTuple/data/${TARNAME}
REDDIR=${VLTLDIR}/analysis-omega/Reductor/bin
OUTDIR=${WORKDIR}/out/GST_Reduced/data
mkdir -p ${OUTDIR} # just in case

cp -v ${REDDIR}/Reductor ${GSTDIR} # copy binary to GSTDIR

cd ${GSTDIR}
for file in *.root; do
    file2=${file#*_}
    RN=${file2//.root}
    ./Reductor -t${TARNAME} -r${RN} # execute program
    mv -v pruned${TARNAME}_${RN}_red.root ${OUTDIR}/ # move output file to outdir
done

rm -v ${GSTDIR}/Reductor
