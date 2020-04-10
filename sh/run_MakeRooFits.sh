#!/bin/bash

OUDIR=${PRODIR}/out/MakeRooFits/Z
cd ${PRODIR}

./bin/MakeRooFits -h

# first attempt
./bin/MakeRooFits -tD -z3 -S > ${OUDIR}/roofit-D-z3.log
./bin/MakeRooFits -tD -z4 -S > ${OUDIR}/roofit-D-z4.log
./bin/MakeRooFits -tD -z5 -S > ${OUDIR}/roofit-D-z5.log
./bin/MakeRooFits -tD -z6 -S > ${OUDIR}/roofit-D-z6.log
./bin/MakeRooFits -tD -z7 -S > ${OUDIR}/roofit-D-z7.log

./bin/MakeRooFits -tC -z3 -S > ${OUDIR}/roofit-C-z3.log
./bin/MakeRooFits -tC -z4 -S > ${OUDIR}/roofit-C-z4.log
./bin/MakeRooFits -tC -z5 -S > ${OUDIR}/roofit-C-z5.log
./bin/MakeRooFits -tC -z6 -S > ${OUDIR}/roofit-C-z6.log
./bin/MakeRooFits -tC -z7 -S > ${OUDIR}/roofit-C-z7.log

./bin/MakeRooFits -tFe -z3 -S > ${OUDIR}/roofit-Fe-z3.log
./bin/MakeRooFits -tFe -z4 -S > ${OUDIR}/roofit-Fe-z4.log
./bin/MakeRooFits -tFe -z5 -S > ${OUDIR}/roofit-Fe-z5.log
./bin/MakeRooFits -tFe -z6 -S > ${OUDIR}/roofit-Fe-z6.log
./bin/MakeRooFits -tFe -z7 -S > ${OUDIR}/roofit-Fe-z7.log

./bin/MakeRooFits -tPb -z3 -S > ${OUDIR}/roofit-Pb-z3.log
./bin/MakeRooFits -tPb -z4 -S > ${OUDIR}/roofit-Pb-z4.log
./bin/MakeRooFits -tPb -z5 -S > ${OUDIR}/roofit-Pb-z5.log
./bin/MakeRooFits -tPb -z6 -S > ${OUDIR}/roofit-Pb-z6.log
./bin/MakeRooFits -tPb -z7 -S > ${OUDIR}/roofit-Pb-z7.log

# second attempt
./bin/MakeRooFits -tD -z3 > ${OUDIR}/roofit-D-z3.log
./bin/MakeRooFits -tD -z4 > ${OUDIR}/roofit-D-z4.log
./bin/MakeRooFits -tD -z5 > ${OUDIR}/roofit-D-z5.log
./bin/MakeRooFits -tD -z6 > ${OUDIR}/roofit-D-z6.log
./bin/MakeRooFits -tD -z7 > ${OUDIR}/roofit-D-z7.log

./bin/MakeRooFits -tC -z3 > ${OUDIR}/roofit-C-z3.log
./bin/MakeRooFits -tC -z4 > ${OUDIR}/roofit-C-z4.log
./bin/MakeRooFits -tC -z5 > ${OUDIR}/roofit-C-z5.log
./bin/MakeRooFits -tC -z6 > ${OUDIR}/roofit-C-z6.log
./bin/MakeRooFits -tC -z7 > ${OUDIR}/roofit-C-z7.log

./bin/MakeRooFits -tFe -z3 > ${OUDIR}/roofit-Fe-z3.log
./bin/MakeRooFits -tFe -z4 > ${OUDIR}/roofit-Fe-z4.log
./bin/MakeRooFits -tFe -z5 > ${OUDIR}/roofit-Fe-z5.log
./bin/MakeRooFits -tFe -z6 > ${OUDIR}/roofit-Fe-z6.log
./bin/MakeRooFits -tFe -z7 > ${OUDIR}/roofit-Fe-z7.log

./bin/MakeRooFits -tPb -z3 > ${OUDIR}/roofit-Pb-z3.log
./bin/MakeRooFits -tPb -z4 > ${OUDIR}/roofit-Pb-z4.log
./bin/MakeRooFits -tPb -z5 > ${OUDIR}/roofit-Pb-z5.log
./bin/MakeRooFits -tPb -z6 > ${OUDIR}/roofit-Pb-z6.log
./bin/MakeRooFits -tPb -z7 > ${OUDIR}/roofit-Pb-z7.log
