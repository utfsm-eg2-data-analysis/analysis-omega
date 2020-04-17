#!/bin/bash

cd ${PRODIR}
./bin/MakeSimFits -h

# first try
./bin/MakeSimFits -tD -z3 -S
./bin/MakeSimFits -tD -z4 -S 
./bin/MakeSimFits -tD -z5 -S
./bin/MakeSimFits -tD -z6 -S 
./bin/MakeSimFits -tD -z7 -S 

./bin/MakeSimFits -tC -z3 -S 
./bin/MakeSimFits -tC -z4 -S 
./bin/MakeSimFits -tC -z5 -S 
./bin/MakeSimFits -tC -z6 -S 
./bin/MakeSimFits -tC -z7 -S 

./bin/MakeSimFits -tFe -z3 -S
./bin/MakeSimFits -tFe -z4 -S
./bin/MakeSimFits -tFe -z5 -S
./bin/MakeSimFits -tFe -z6 -S
./bin/MakeSimFits -tFe -z7 -S

./bin/MakeSimFits -tPb -z3 -S
./bin/MakeSimFits -tPb -z4 -S
./bin/MakeSimFits -tPb -z5 -S
./bin/MakeSimFits -tPb -z6 -S
./bin/MakeSimFits -tPb -z7 -S

# second try
./bin/MakeSimFits -tD -z3
./bin/MakeSimFits -tD -z4 
./bin/MakeSimFits -tD -z5
./bin/MakeSimFits -tD -z6 
./bin/MakeSimFits -tD -z7 

./bin/MakeSimFits -tC -z3 
./bin/MakeSimFits -tC -z4 
./bin/MakeSimFits -tC -z5 
./bin/MakeSimFits -tC -z6 
./bin/MakeSimFits -tC -z7 

./bin/MakeSimFits -tFe -z3
./bin/MakeSimFits -tFe -z4
./bin/MakeSimFits -tFe -z5
./bin/MakeSimFits -tFe -z6
./bin/MakeSimFits -tFe -z7

./bin/MakeSimFits -tPb -z3
./bin/MakeSimFits -tPb -z4
./bin/MakeSimFits -tPb -z5
./bin/MakeSimFits -tPb -z6
./bin/MakeSimFits -tPb -z7
