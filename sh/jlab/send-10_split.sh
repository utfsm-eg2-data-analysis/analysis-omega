#!/bin/bash

# ./send-10_split.sh

source ~/.bashrc
cd ${PRODIR}/sh/jlab

./send_split.sh D 001 01
./send_split.sh D 001 02
./send_split.sh D 001 03
./send_split.sh D 001 04

./send_split.sh C 001 01
./send_split.sh C 001 02

./send_split.sh Fe 001 01
./send_split.sh Fe 001 02

./send_split.sh Pb 001 01
./send_split.sh Pb 001 02
