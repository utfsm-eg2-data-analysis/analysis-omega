#!/bin/bash

##################################
# ./run_MakeRooFits.sh <bkgOpt>  #
#     <bkgOpt> = (1, 2)          #
##################################

bkgOpt="$@"

OUDIR=${PRODIR}/out/MakeRooFits/Q2/g/b${bkgOpt}
cd ${PRODIR}

./bin/MakeRooFits -h

# first attempt
./bin/MakeRooFits -tD -n1 -b${bkgOpt} -S > ${OUDIR}/roofit-D-n1.log
./bin/MakeRooFits -tD -n2 -b${bkgOpt} -S > ${OUDIR}/roofit-D-n2.log
./bin/MakeRooFits -tD -n3 -b${bkgOpt} -S > ${OUDIR}/roofit-D-n3.log
./bin/MakeRooFits -tD -n4 -b${bkgOpt} -S > ${OUDIR}/roofit-D-n4.log
./bin/MakeRooFits -tD -n5 -b${bkgOpt} -S > ${OUDIR}/roofit-D-n5.log

./bin/MakeRooFits -tC -n1 -b${bkgOpt} -S > ${OUDIR}/roofit-C-n1.log
./bin/MakeRooFits -tC -n2 -b${bkgOpt} -S > ${OUDIR}/roofit-C-n2.log
./bin/MakeRooFits -tC -n3 -b${bkgOpt} -S > ${OUDIR}/roofit-C-n3.log
./bin/MakeRooFits -tC -n4 -b${bkgOpt} -S > ${OUDIR}/roofit-C-n4.log
./bin/MakeRooFits -tC -n5 -b${bkgOpt} -S > ${OUDIR}/roofit-C-n5.log

./bin/MakeRooFits -tFe -n1 -b${bkgOpt} -S > ${OUDIR}/roofit-Fe-n1.log
./bin/MakeRooFits -tFe -n2 -b${bkgOpt} -S > ${OUDIR}/roofit-Fe-n2.log
./bin/MakeRooFits -tFe -n3 -b${bkgOpt} -S > ${OUDIR}/roofit-Fe-n3.log
./bin/MakeRooFits -tFe -n4 -b${bkgOpt} -S > ${OUDIR}/roofit-Fe-n4.log
./bin/MakeRooFits -tFe -n5 -b${bkgOpt} -S > ${OUDIR}/roofit-Fe-n5.log

./bin/MakeRooFits -tPb -n1 -b${bkgOpt} -S > ${OUDIR}/roofit-nb-n1.log
./bin/MakeRooFits -tPb -n2 -b${bkgOpt} -S > ${OUDIR}/roofit-nb-n2.log
./bin/MakeRooFits -tPb -n3 -b${bkgOpt} -S > ${OUDIR}/roofit-nb-n3.log
./bin/MakeRooFits -tPb -n4 -b${bkgOpt} -S > ${OUDIR}/roofit-nb-n4.log
./bin/MakeRooFits -tPb -n5 -b${bkgOpt} -S > ${OUDIR}/roofit-nb-n5.log

# second attempt
./bin/MakeRooFits -tD -n1 -b${bkgOpt} > ${OUDIR}/roofit-D-n1.log
./bin/MakeRooFits -tD -n2 -b${bkgOpt} > ${OUDIR}/roofit-D-n2.log
./bin/MakeRooFits -tD -n3 -b${bkgOpt} > ${OUDIR}/roofit-D-n3.log
./bin/MakeRooFits -tD -n4 -b${bkgOpt} > ${OUDIR}/roofit-D-n4.log
./bin/MakeRooFits -tD -n5 -b${bkgOpt} > ${OUDIR}/roofit-D-n5.log

./bin/MakeRooFits -tC -n1 -b${bkgOpt} > ${OUDIR}/roofit-C-n1.log
./bin/MakeRooFits -tC -n2 -b${bkgOpt} > ${OUDIR}/roofit-C-n2.log
./bin/MakeRooFits -tC -n3 -b${bkgOpt} > ${OUDIR}/roofit-C-n3.log
./bin/MakeRooFits -tC -n4 -b${bkgOpt} > ${OUDIR}/roofit-C-n4.log
./bin/MakeRooFits -tC -n5 -b${bkgOpt} > ${OUDIR}/roofit-C-n5.log

./bin/MakeRooFits -tFe -n1 -b${bkgOpt} > ${OUDIR}/roofit-Fe-n1.log
./bin/MakeRooFits -tFe -n2 -b${bkgOpt} > ${OUDIR}/roofit-Fe-n2.log
./bin/MakeRooFits -tFe -n3 -b${bkgOpt} > ${OUDIR}/roofit-Fe-n3.log
./bin/MakeRooFits -tFe -n4 -b${bkgOpt} > ${OUDIR}/roofit-Fe-n4.log
./bin/MakeRooFits -tFe -n5 -b${bkgOpt} > ${OUDIR}/roofit-Fe-n5.log

./bin/MakeRooFits -tPb -n1 -b${bkgOpt} > ${OUDIR}/roofit-nb-n1.log
./bin/MakeRooFits -tPb -n2 -b${bkgOpt} > ${OUDIR}/roofit-nb-n2.log
./bin/MakeRooFits -tPb -n3 -b${bkgOpt} > ${OUDIR}/roofit-nb-n3.log
./bin/MakeRooFits -tPb -n4 -b${bkgOpt} > ${OUDIR}/roofit-nb-n4.log
./bin/MakeRooFits -tPb -n5 -b${bkgOpt} > ${OUDIR}/roofit-nb-n5.log
