#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

./GetSimpleTuple_data -t${TARNAME} -r${RN}
./ThreePionFinder_data -t${TARNAME} -r${RN}
./Reductor -t${TARNAME} -r${RN}
./ThreePionFinder_data -t${TARNAME} -r"${RN}_red" -m211
./ThreePionFinder_data -t${TARNAME} -r"${RN}_red" -m-211
./ThreePionFinder_data -t${TARNAME} -r"${RN}_red" -m111
./ThreePionFinder_data -t${TARNAME} -r"${RN}_red" -m999
