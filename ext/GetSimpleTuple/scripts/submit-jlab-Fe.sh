#!/bin/bash

#PBS -N GST_jlab-Fe
#PBS -V
#PBS -q utfsm
#PBS -l walltime=10:00:00
#PBS -l cput=10:00:00
#PBS -m ae
#PBS -M andres.borquez.14@sansano.usm.cl

SHDIR=/user/b/borquez/omega/GetSimpleTuple/scripts
cd $SHDIR

./run_GST-Sim.sh jlab-Fe
