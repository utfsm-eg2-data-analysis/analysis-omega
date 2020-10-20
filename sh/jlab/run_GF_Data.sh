#!/bin/bash

# set env
source /home/borquez/.bashrc

tarName=
rn=

./GetSimpleTuple -d${tarName} -r${rn}
./FilterNCombine_data -t${tarName} -r${rn}
