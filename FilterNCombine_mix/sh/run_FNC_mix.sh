#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

# run for every particle
./MixingBkg -t${TARNAME} -r${RN} -p211
./MixingBkg -t${TARNAME} -r${RN} -p-211
./MixingBkg -t${TARNAME} -r${RN} -p22

# then, mix all
./MixingBkg -t${TARNAME} -r${RN} -p1
