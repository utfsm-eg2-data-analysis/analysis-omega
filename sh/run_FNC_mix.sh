#!/bin/bash

# set env
source /home/borquez/.bashrc

TARNAME=
RN=

# swap one pion at a time
./FilterNCombine_mix -t${TARNAME} -r${RN} -p211
./FilterNCombine_mix -t${TARNAME} -r${RN} -p-211
./FilterNCombine_mix -t${TARNAME} -r${RN} -p111

# swap all three pions
./FilterNCombine_mix -t${TARNAME} -r${RN} -p999
