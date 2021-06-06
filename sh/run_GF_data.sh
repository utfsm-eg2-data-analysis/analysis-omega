#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

./GetSimpleTuple_data -t${TARNAME} -r${RN}
./FilterNCombine_data -t${TARNAME} -r${RN}
