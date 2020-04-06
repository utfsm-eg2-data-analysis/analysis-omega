#!/bin/bash

OUDIR=${PRODIR}/out/MakeSimFits/Z
cd ${PRODIR}

./bin/MakeSimFits -h

./bin/MakeSimFits -tD -z3 > ${OUDIR}/simfit-D-z3.log
./bin/MakeSimFits -tD -z4 > ${OUDIR}/simfit-D-z4.log
./bin/MakeSimFits -tD -z5 > ${OUDIR}/simfit-D-z5.log
./bin/MakeSimFits -tD -z6 > ${OUDIR}/simfit-D-z6.log
./bin/MakeSimFits -tD -z7 > ${OUDIR}/simfit-D-z7.log

./bin/MakeSimFits -tC -z3 > ${OUDIR}/simfit-C-z3.log
./bin/MakeSimFits -tC -z4 > ${OUDIR}/simfit-C-z4.log
./bin/MakeSimFits -tC -z5 > ${OUDIR}/simfit-C-z5.log
./bin/MakeSimFits -tC -z6 > ${OUDIR}/simfit-C-z6.log
./bin/MakeSimFits -tC -z7 > ${OUDIR}/simfit-C-z7.log

./bin/MakeSimFits -tFe -z3 > ${OUDIR}/simfit-Fe-z3.log
./bin/MakeSimFits -tFe -z4 > ${OUDIR}/simfit-Fe-z4.log
./bin/MakeSimFits -tFe -z5 > ${OUDIR}/simfit-Fe-z5.log
./bin/MakeSimFits -tFe -z6 > ${OUDIR}/simfit-Fe-z6.log
./bin/MakeSimFits -tFe -z7 > ${OUDIR}/simfit-Fe-z7.log

./bin/MakeSimFits -tPb -z3 > ${OUDIR}/simfit-Pb-z3.log
./bin/MakeSimFits -tPb -z4 > ${OUDIR}/simfit-Pb-z4.log
./bin/MakeSimFits -tPb -z5 > ${OUDIR}/simfit-Pb-z5.log
./bin/MakeSimFits -tPb -z6 > ${OUDIR}/simfit-Pb-z6.log
./bin/MakeSimFits -tPb -z7 > ${OUDIR}/simfit-Pb-z7.log
