#!/bin/bash

cd ${PRODIR}

./bin/MakePlots-2D -h

#./bin/MakePlots-2D -d -tD  -yQ2  -xNu
#./bin/MakePlots-2D -d -tD  -yPt2 -xZ
#./bin/MakePlots-2D -d -tC  -yQ2  -xNu
#./bin/MakePlots-2D -d -tC  -yPt2 -xZ
#./bin/MakePlots-2D -d -tFe -yQ2  -xNu
#./bin/MakePlots-2D -d -tFe -yPt2 -xZ

#./bin/MakePlots-2D -s -tD  -yQ2  -xNu
#./bin/MakePlots-2D -s -tD  -yPt2 -xZ
./bin/MakePlots-2D -s -tC  -yQ2  -xNu
./bin/MakePlots-2D -s -tC  -yPt2 -xZ
#./bin/MakePlots-2D -s -tFe -yQ2  -xNu
#./bin/MakePlots-2D -s -tFe -yPt2 -xZ
