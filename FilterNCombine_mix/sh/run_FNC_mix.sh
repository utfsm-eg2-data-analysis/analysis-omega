#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

# run for every particle
./FilterNCombine_mix -t${TARNAME} -r${RN} -p211
./FilterNCombine_mix -t${TARNAME} -r${RN} -p-211
./FilterNCombine_mix -t${TARNAME} -r${RN} -p111
