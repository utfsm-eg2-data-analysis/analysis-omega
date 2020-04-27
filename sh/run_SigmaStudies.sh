#!/bin/bash

######################################################
# ./run_SigmaStudies.sh  <kinvarOpt>                 #
#     <kinvarOpt> = (Z, Pt2, Q2, Nu)                 #
#                                                    #
# EG: ./run_SigmaStudies.sh Pt2                      #
######################################################

kinvar="$@"

cd ${PRODIR}

arrayM=(36 38 40 42)
arrayW=(1.5 2 2.5)

for mean in "${arrayM[@]}"; do
    for width in "${arrayW[@]}"; do
	# make fits
        ./sh/run_MakeRooFits.sh --bkg 1 --kinvar ${kinvar} --mean ${mean} --width ${width}
	# plot params
	./bin/PlotParams -k${kinvar} -Fg -b1 -C${mean}
	mv -v out/MakeRooFits/params-${kinvar}-g-b1.png out/MakeRooFits/params-${kinvar}-g-b1_${mean}_${width}.png
	# execute makemr
	./bin/MakeMR-bs -k${kinvar} -Fg -b1
	mv -v out/MakeMR/bs/bs-MR-${kinvar}-g-b1.png out/MakeMR/bs/bs-MR-${kinvar}-g-b1_${mean}_${width}.png 
    done
done

