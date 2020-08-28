#!/bin/bash

#####
# Functions
###

function get_num_2dig()
{
  sr=$1
  srn=""
  if [[ $sr -lt 10 ]]; then
    srn="0$sr"
  else
    srn="$sr"
  fi
  echo $srn
}

#####
# Main
###

# D 43
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_65.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_73.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_76.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_88.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_89.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_90.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_91.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_92.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_93.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_94.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_95.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_96.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_97.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_98.root /home/borquez/volatile/omegaSim/output/D/43/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/43/recsisD_99.root /home/borquez/volatile/omegaSim/output/D/43/

# D 44
for ((rn=0; rn<100; rn++)); do
    srn=$(get_num_2dig "$rn")
    ./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/D/44/recsisD_${srn}.root /home/borquez/volatile/omegaSim/output/D/44/
done

# Fe 01
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_00.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_03.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_06.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_07.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_08.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_10.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_13.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_19.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_22.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_25.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_26.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_28.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_31.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_32.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_37.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_38.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_39.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_41.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_43.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_44.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_45.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_47.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_54.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_56.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_60.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_61.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_63.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_66.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_69.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_70.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_72.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_74.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_75.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_76.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_85.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_86.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_88.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_89.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_90.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_91.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_92.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_95.root /home/borquez/volatile/omegaSim/output/Fe/01/
./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/01/recsisFe_98.root /home/borquez/volatile/omegaSim/output/Fe/01/

# Fe 08
for ((rn2=0; rn2<100; rn2++)); do
    srn=$(get_num_2dig "$rn2")
    ./gett.sh /mss/clas/eg2a/production/Simulation/omega_lepto/Fe/08/recsisFe_${srn}.root /home/borquez/volatile/omegaSim/output/Fe/08/
done
