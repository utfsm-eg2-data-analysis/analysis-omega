#!/bin/bash
ls /data/jlab/mss/clas/eg2a/production/Pass2/Clas/clas_$1_*.pass2.root | tail -1 | xargs -I V root -l -b -q V -e 'SCALER->Scan("SC_TRGS.Fcup_g2")' 2>/dev/null | tail -3 | head -1 | awk '{print $6}'
