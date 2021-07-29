#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

# GST + TPF
./GetSimpleTuple_sim -t${TARNAME} -r${RN}
./ThreePionFinder_sim -t${TARNAME} -r${RN}