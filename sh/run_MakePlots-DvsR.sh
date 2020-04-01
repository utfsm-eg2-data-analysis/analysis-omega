#!/bin/bash

cd ${PRODIR}

./bin/MakePlots-DvsR -h

#./bin/MakePlots-DvsR -tC -kQ 
./bin/MakePlots-DvsR -tC -kN
#./bin/MakePlots-DvsR -tC -kW
#./bin/MakePlots-DvsR -tC -kM

#./bin/MakePlots-DvsR -tFe -kQ
./bin/MakePlots-DvsR -tFe -kN
#./bin/MakePlots-DvsR -tFe -kW
#./bin/MakePlots-DvsR -tFe -kM

#./bin/MakePlots-DvsR -tD -kQ
./bin/MakePlots-DvsR -tD -kN
#./bin/MakePlots-DvsR -tD -kW
#./bin/MakePlots-DvsR -tD -kM

