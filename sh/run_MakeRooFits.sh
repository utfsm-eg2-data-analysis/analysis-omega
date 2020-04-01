#!/bin/bash

OUDIR=${PRODIR}/out/MakeRooFits/Z
cd ${PRODIR}

./bin/MakeRooFits -h

./bin/MakeRooFits -tD -z3 > ${OUDIR}/roofit-D-z3.log
./bin/MakeRooFits -tD -z4 > ${OUDIR}/roofit-D-z4.log
./bin/MakeRooFits -tD -z5 > ${OUDIR}/roofit-D-z5.log
./bin/MakeRooFits -tD -z6 > ${OUDIR}/roofit-D-z6.log
./bin/MakeRooFits -tD -z7 > ${OUDIR}/roofit-D-z7.log
