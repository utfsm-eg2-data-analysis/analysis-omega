#!/bin/bash

#################################
# ./run_SystPi0Fits.sh <target> #
#     <target> = (D, C, Fe, Pb) #
#################################

tarName="$@"

cd ${PRODIR}

./bin/SystPi0Fits -h

# First attempt

./bin/SystPi0Fits -t${tarName} -z3 -s3.  -S
./bin/SystPi0Fits -t${tarName} -z3 -s3.5 -S
./bin/SystPi0Fits -t${tarName} -z3 -s4.  -S
./bin/SystPi0Fits -t${tarName} -z3 -s4.5 -S
./bin/SystPi0Fits -t${tarName} -z3 -s5.  -S

./bin/SystPi0Fits -t${tarName} -z4 -s3.  -S
./bin/SystPi0Fits -t${tarName} -z4 -s3.5 -S
./bin/SystPi0Fits -t${tarName} -z4 -s4.  -S
./bin/SystPi0Fits -t${tarName} -z4 -s4.5 -S
./bin/SystPi0Fits -t${tarName} -z4 -s5.  -S

./bin/SystPi0Fits -t${tarName} -z5 -s3.  -S
./bin/SystPi0Fits -t${tarName} -z5 -s3.5 -S
./bin/SystPi0Fits -t${tarName} -z5 -s4.  -S
./bin/SystPi0Fits -t${tarName} -z5 -s4.5 -S
./bin/SystPi0Fits -t${tarName} -z5 -s5.  -S

./bin/SystPi0Fits -t${tarName} -z6 -s3.  -S
./bin/SystPi0Fits -t${tarName} -z6 -s3.5 -S
./bin/SystPi0Fits -t${tarName} -z6 -s4.  -S
./bin/SystPi0Fits -t${tarName} -z6 -s4.5 -S
./bin/SystPi0Fits -t${tarName} -z6 -s5.  -S

./bin/SystPi0Fits -t${tarName} -z7 -s3.  -S
./bin/SystPi0Fits -t${tarName} -z7 -s3.5 -S
./bin/SystPi0Fits -t${tarName} -z7 -s4.  -S
./bin/SystPi0Fits -t${tarName} -z7 -s4.5 -S
./bin/SystPi0Fits -t${tarName} -z7 -s5.  -S

# Second attempt

./bin/SystPi0Fits -t${tarName} -z3 -s3.  
./bin/SystPi0Fits -t${tarName} -z3 -s3.5 
./bin/SystPi0Fits -t${tarName} -z3 -s4.  
./bin/SystPi0Fits -t${tarName} -z3 -s4.5 
./bin/SystPi0Fits -t${tarName} -z3 -s5.  

./bin/SystPi0Fits -t${tarName} -z4 -s3.  
./bin/SystPi0Fits -t${tarName} -z4 -s3.5 
./bin/SystPi0Fits -t${tarName} -z4 -s4.  
./bin/SystPi0Fits -t${tarName} -z4 -s4.5 
./bin/SystPi0Fits -t${tarName} -z4 -s5.  

./bin/SystPi0Fits -t${tarName} -z5 -s3.  
./bin/SystPi0Fits -t${tarName} -z5 -s3.5 
./bin/SystPi0Fits -t${tarName} -z5 -s4.  
./bin/SystPi0Fits -t${tarName} -z5 -s4.5 
./bin/SystPi0Fits -t${tarName} -z5 -s5.  

./bin/SystPi0Fits -t${tarName} -z6 -s3.  
./bin/SystPi0Fits -t${tarName} -z6 -s3.5 
./bin/SystPi0Fits -t${tarName} -z6 -s4.  
./bin/SystPi0Fits -t${tarName} -z6 -s4.5 
./bin/SystPi0Fits -t${tarName} -z6 -s5.  

./bin/SystPi0Fits -t${tarName} -z7 -s3.
./bin/SystPi0Fits -t${tarName} -z7 -s3.5
./bin/SystPi0Fits -t${tarName} -z7 -s4.
./bin/SystPi0Fits -t${tarName} -z7 -s4.5
./bin/SystPi0Fits -t${tarName} -z7 -s5.



