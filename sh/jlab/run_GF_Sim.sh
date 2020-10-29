#!/bin/bash

# set env
source /home/borquez/.bashrc

tarName=
rn=

./GetSimpleTuple_sim -t${tarName} -r${rn}
./FilterNCombine_sim -t${tarName} -r${rn}
