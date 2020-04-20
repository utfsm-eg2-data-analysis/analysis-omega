#!/bin/bash
echo "#run Fcup_g2";
cat $1 |  xargs -I V bash -c 'echo "V $(./get_FCUP_run.sh V)"'
