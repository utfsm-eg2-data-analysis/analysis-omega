#!/bin/bash

function cfied() {
    for dir in $1/*/; do echo "$dir : $(ls -1 $dir | wc -l)"; done
}

PARTICLE="$@"

CACHEDIR="/cache/mss/clas/eg2a/production/Simulation/${PARTICLE}_lepto"
TAPEDIR="/mss/clas/eg2a/production/Simulation/${PARTICLE}_lepto"

echo "CACHE new/D"
cfied ${CACHEDIR}/new/D
echo "TAPE new/D"
cfied ${TAPEDIR}/new/D
echo ""

echo "CACHE new/C"
cfied ${CACHEDIR}/new/C
echo "TAPE new/C"
cfied ${TAPEDIR}/new/C
echo ""

echo "CACHE new/Fe"
cfied ${CACHEDIR}/new/Fe
echo "TAPE new/Fe"
cfied ${TAPEDIR}/new/Fe
echo ""

echo "CACHE new/Pb"
cfied ${CACHEDIR}/new/Pb
echo "TAPE new/Pb"
cfied ${TAPEDIR}/new/Pb
echo ""
