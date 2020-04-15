#!/bin/bash

cd ${PRODIR}

mkdir -p tmp

mkdir -p out/prunedData/C
mkdir -p out/prunedData/Fe
mkdir -p out/prunedData/Pb

mkdir -p out/filterData/C
mkdir -p out/filterData/Fe
mkdir -p out/filterData/Pb

mkdir -p out/prunedSim/old
mkdir -p out/prunedSim/old/C
mkdir -p out/prunedSim/old/Fe
mkdir -p out/prunedSim/usm/D
mkdir -p out/prunedSim/usm/C
mkdir -p out/prunedSim/usm/Fe
mkdir -p out/prunedSim/usm/Pb
mkdir -p out/prunedSim/jlab/D
mkdir -p out/prunedSim/jlab/C
mkdir -p out/prunedSim/jlab/Fe

mkdir -p out/filterSim/simrec/old/C
mkdir -p out/filterSim/simrec/old/Fe
mkdir -p out/filterSim/simrec/usm/D
mkdir -p out/filterSim/simrec/usm/C
mkdir -p out/filterSim/simrec/usm/Fe
mkdir -p out/filterSim/simrec/usm/Pb
mkdir -p out/filterSim/simrec/jlab/D
mkdir -p out/filterSim/simrec/jlab/C
mkdir -p out/filterSim/simrec/jlab/Fe

mkdir -p out/filterSim/gsim/old/C
mkdir -p out/filterSim/gsim/old/Fe
mkdir -p out/filterSim/gsim/usm/D
mkdir -p out/filterSim/gsim/usm/C
mkdir -p out/filterSim/gsim/usm/Fe
mkdir -p out/filterSim/gsim/usm/Pb
mkdir -p out/filterSim/gsim/jlab/D
mkdir -p out/filterSim/gsim/jlab/C
mkdir -p out/filterSim/gsim/jlab/Fe

mkdir -p out/MakePlots
mkdir -p out/GetQuantiles

mkdir -p out/MakeRooFits/Z
mkdir -p out/MakeRooFits/Pt2
mkdir -p out/MakeRooFits/Q2
mkdir -p out/MakeRooFits/Nu

mkdir -p out/MakeMR/nbs
mkdir -p out/MakeMR/bs
mkdir -p out/MakeMR/sn
mkdir -p out/MakeMR/sim

mkdir -p out/SystPi0/Z
mkdir -p out/SystPi0/Pt2
mkdir -p out/SystPi0/Q2
mkdir -p out/SystPi0/Nu
