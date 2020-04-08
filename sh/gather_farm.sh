#!/bin/bash

#################################
# ./gather_farm.sh <target>     #
#     <target> = (D, C, Fe, Pb) #
#################################

tarName="$@"

if [[ ${tarName} = "D" ]]; then
  auxDir="06"
elif [[ ${tarName} = "C" ]]; then
  auxDir="06"
elif [[ ${tarName} = "Fe" ]]; then
  auxDir="06"
elif [[ ${tarName} = "Pb" ]]; then
  auxDir="00"
fi

FARMDIR=/home/borquez/volatile/omegaSim/farm/${tarName}
OUDIR=/home/borquez/volatile/omegaSim/output/${tarName}/${auxDir}

mkdir -p ${OUDIR}

cd ${FARMDIR}
echo "Executing gather_farm.sh..."

for dir in */
do
  cd ${dir}
  mv -v recsis${tarName}.root ${OUDIR}/recsis${tarName}_${dir:3:4}.root
  rm *
  cd ..
done

rm -rfv run*

echo "Everything ready, sir!"
