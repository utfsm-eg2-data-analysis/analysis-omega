#!/bin/bash

#PBS -N FNC_usm-C
#PBS -V
#PBS -q utfsm
#PBS -l walltime=24:00:00
#PBS -l cput=24:00:00
#PBS -m ae
#PBS -M andres.borquez.14@sansano.usm.cl

sh ${PRODIR}/sh/run_FilterNCombine.sh --targ C --set usm
