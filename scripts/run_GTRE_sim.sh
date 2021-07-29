#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

# 0) GST + FNC
./GetSimpleTuple_sim -t${TARNAME} -r${RN}
./ThreePionFinder_sim -t${TARNAME} -r${RN}
# 1) Reductor
./Reductor -t${TARNAME} -r${RN} -s0 # MC
./Reductor -t${TARNAME} -r${RN} -s1 # SimRec
# 2) Event-Mixing, SimRec
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red" -m"211"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red" -m"-211"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red" -m"111"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red" -m"999"
# 3) Event-Mixing, MC
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"211"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"-211"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"111"
./ThreePionFinder_sim -t"${TARNAME}" -r"${RN}_red_MC" -g"999"
