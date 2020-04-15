#!/bin/bash
#PBS -m n # no email
#PBS -l walltime=90:00:00 # maximum time on wall
#PBS -o /dev/null # no stdout
#PBS -e /dev/null # no stderr
#PBS -q utfsm # use specific queue

#source /user/o/orsosa/set_64bit.sh;
#dir=$PBS_O_WORKDIR
cd $TMPDIR

#opt options: data | simrec | gsim 
opt="gsim" 

# tt data options: C-thickD2 | Fe-thickD2 | Pb-thinD2
# tt sim options:  C_D (0-5) | C/C_xyz (0-6)

tt="C/C_xyz"

cp /user/o/orsosa/osoto_ana/gammECorr.root .
cp /user/o/orsosa/osoto_ana/eta_id .
if [ $opt == "data" ]; then
    cp /user/o/orsosa/osoto_ana/${tt}rn.txt . # for data only
    runlist="${tt}rn.txt" # for data only
    outdir="/data/tsunami/user/o/orsosa/eg2_data_pruned/${tt}" # for data only
    rn=`sed -n "$PBS_ARRAYID{p;q}" $runlist` # for data only
#    cp /data/atlas/users/orsosa/eg2_data_pruned/$tt/pruned_$rn.root data.root  # for data only 
    cp /data/tsunami/user/o/orsosa/eg2_data_pruned/$tt/pruned_$rn.root data.root  # for data only 

else
    sim=""
    if [ $opt == "simrec" ]; then
	sim="rec";
    elif [ $opt == "gsim" ]; then 
	sim="gsim";
    fi # for sim only
    echo $sim
    simdir=/data/tsunami/user/o/orsosa/eg2_sim_pruned_new
#    outdir="/data/user/o/orsosa/eg2_sim_pruned/$tt/$sim" # for sim only    
    outdir=$simdir/$tt/$sim # for sim only    
    rn=$PBS_ARRAYID # for sim only
#    cp /data/atlas/users/orsosa/eg2_sim_pruned/$tt/pruned_simul_$rn.root data.root # for sim only
#    cp /data/user/o/orsosa/eg2_sim_pruned/$tt/pruned_simul_$rn.root data.root # for sim only
    file=$(ls -tr $simdir/$tt/*5e6*.root | sed -n "$PBS_ARRAYID{p;q}") #could be changed for find to increase speed.
    cp $file data.root
    mkdir -p $outdir 2> /dev/null
fi

echo "outdir: "
echo $outdir

./eta_id -t $opt

#cp etaout_aa_all_bk.root $outdir"/etaout_aa_all_"$rn"_bk.root"
#cp etaout_pippimaa_all.root $outdir"/etaout_pippimaa_all_"$rn".root"

cp etaout_aa_only.root $outdir"/etaout_aa_only_"$rn".root"
