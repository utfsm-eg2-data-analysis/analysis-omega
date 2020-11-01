#!/bin/bash

# set env
source /home/borquez/.bashrc

setOption=
tarName=
rn=
nfiles_begin=
nfiles_end=

if [[ "${setOption}" == "old" || "${setOption}" == "usm" ]]; then
    ./GetSimpleTuple_sim -t${tarName} -r${rn}
    ./FilterNCombine_sim -t${tarName} -r${rn}
elif [[ "${setOption}" == "jlab" ]]; then
    for ((srn=$nfiles_begin; srn <= $nfiles_begin; srn++)); do
	./GetSimpleTuple_sim -t${tarName} -r${srn}
	./FilterNCombine_sim -t${tarName} -r${srn}
    done
fi
