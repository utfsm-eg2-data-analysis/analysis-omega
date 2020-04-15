#!/bin/bash

tt="C-thickD2"
t="C"

runlist="/user/b/borquez/borquez_data/RunNumbers/${tt}rn.txt"
lines=`wc -l < ${runlist}`

COUNTER=0
while [ $COUNTER -lt ${lines} ]; do
    let COUNTER=COUNTER+1
    echo $COUNTER
    rn=`sed -n "$COUNTER{p;q}" ${runlist}`
    echo ${rn}
    cp -v /user/b/borquez/borquez_data/EG2Pruned/${tt}/prune_data_${rn}.root /user/b/borquez/borquez_data/EG2Pruned/prune_data_${tt}.root
    ./OmegaID -td -T${t}
    mv -v /user/b/borquez/borquez_data/EG2Pruned/wout_${tt}.root /user/b/borquez/borquez_data/EG2Pruned/${tt}/wout_${rn}.root
    rm -v /user/b/borquez/borquez_data/EG2Pruned/prune_data_${tt}.root
done
