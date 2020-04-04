#!/bin/bash

cd ${PRODIR}

./bin/MakePlots-DvsR -h

#./bin/MakePlots-DvsR -tC -kQ2
./bin/MakePlots-DvsR -tC -kNu
#./bin/MakePlots-DvsR -tC -kW
#./bin/MakePlots-DvsR -tC -kIMD
./bin/MakePlots-DvsR -tC -k3
./bin/MakePlots-DvsR -tC -kZ
./bin/MakePlots-DvsR -tC -kPt2


