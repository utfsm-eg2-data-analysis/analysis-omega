#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

./TwoGammaFinder_data -t${TARNAME} -r${RN}
./Reductor_2G -t${TARNAME} -r${RN}
./TwoGammaFinder_data -t${TARNAME} -r"${RN}_red" -m22
