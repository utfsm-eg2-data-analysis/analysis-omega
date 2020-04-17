#!/bin/bash

##################################
# ./run_MakeRooFits.sh <bkgOpt>  #
#     <bkgOpt> = (1, 2)          #
##################################

bkgOpt="$@"

cd ${PRODIR}
./bin/MakeRooFits -h

# first attempt
#./bin/MakeRooFits -tD -z6 -b${bkgOpt} -S
#./bin/MakeRooFits -tD -z7 -b${bkgOpt} -S
#./bin/MakeRooFits -tD -z3 -b${bkgOpt} -S
#./bin/MakeRooFits -tD -z4 -b${bkgOpt} -S
#./bin/MakeRooFits -tD -z5 -b${bkgOpt} -S
#
#./bin/MakeRooFits -tC -z6 -b${bkgOpt} -S
#./bin/MakeRooFits -tC -z7 -b${bkgOpt} -S
#./bin/MakeRooFits -tC -z3 -b${bkgOpt} -S
#./bin/MakeRooFits -tC -z4 -b${bkgOpt} -S
#./bin/MakeRooFits -tC -z5 -b${bkgOpt} -S
#
#./bin/MakeRooFits -tFe -z6 -b${bkgOpt} -S
#./bin/MakeRooFits -tFe -z7 -b${bkgOpt} -S
#./bin/MakeRooFits -tFe -z3 -b${bkgOpt} -S
#./bin/MakeRooFits -tFe -z4 -b${bkgOpt} -S
#./bin/MakeRooFits -tFe -z5 -b${bkgOpt} -S
#
#./bin/MakeRooFits -tPb -z6 -b${bkgOpt} -S
#./bin/MakeRooFits -tPb -z7 -b${bkgOpt} -S
#./bin/MakeRooFits -tPb -z3 -b${bkgOpt} -S
#./bin/MakeRooFits -tPb -z4 -b${bkgOpt} -S
#./bin/MakeRooFits -tPb -z5 -b${bkgOpt} -S

# second attempt
./bin/MakeRooFits -tD -z6 -b${bkgOpt}
./bin/MakeRooFits -tD -z7 -b${bkgOpt}
./bin/MakeRooFits -tD -z3 -b${bkgOpt}
./bin/MakeRooFits -tD -z4 -b${bkgOpt}
./bin/MakeRooFits -tD -z5 -b${bkgOpt}

./bin/MakeRooFits -tC -z6 -b${bkgOpt}
./bin/MakeRooFits -tC -z7 -b${bkgOpt}
./bin/MakeRooFits -tC -z3 -b${bkgOpt}
./bin/MakeRooFits -tC -z4 -b${bkgOpt}
./bin/MakeRooFits -tC -z5 -b${bkgOpt}

./bin/MakeRooFits -tFe -z6 -b${bkgOpt}
./bin/MakeRooFits -tFe -z7 -b${bkgOpt}
./bin/MakeRooFits -tFe -z3 -b${bkgOpt}
./bin/MakeRooFits -tFe -z4 -b${bkgOpt}
./bin/MakeRooFits -tFe -z5 -b${bkgOpt}

./bin/MakeRooFits -tPb -z6 -b${bkgOpt}
./bin/MakeRooFits -tPb -z7 -b${bkgOpt}
./bin/MakeRooFits -tPb -z3 -b${bkgOpt}
./bin/MakeRooFits -tPb -z4 -b${bkgOpt}
./bin/MakeRooFits -tPb -z5 -b${bkgOpt}
