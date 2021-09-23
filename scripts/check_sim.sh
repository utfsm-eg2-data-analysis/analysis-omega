#!/bin/bash

function cfied()
{
    for dir in $1/*/; do echo "$dir : $(ls -1 $dir | wc -l)"; done
}

CACHEDIR=/cache/mss/clas/eg2a/production/Simulation/omega_lepto
TAPEDIR=/mss/clas/eg2a/production/Simulation/omega_lepto

echo "CACHE old"
cfied ${CACHEDIR}/old
echo "TAPE old"
cfied ${TAPEDIR}/old
echo ""

echo "CACHE usm"
cfied ${CACHEDIR}/usm
echo "TAPE usm"
cfied ${TAPEDIR}/usm
echo ""

echo "CACHE jlab/D"
cfied ${CACHEDIR}/D
echo "TAPE jlab/D"
cfied ${TAPEDIR}/D
echo ""

echo "CACHE jlab/C"
cfied ${CACHEDIR}/C
echo "TAPE jlab/C"
cfied ${TAPEDIR}/C
echo ""

echo "CACHE jlab/Fe"
cfied ${CACHEDIR}/Fe
echo "TAPE jlab/Fe"
cfied ${TAPEDIR}/Fe
echo ""

echo "CACHE jlab/Pb"
cfied ${CACHEDIR}/Pb
echo "TAPE jlab/Pb"
cfied ${TAPEDIR}/Pb
echo ""
