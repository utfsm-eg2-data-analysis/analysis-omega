#!/bin/bash

#####################################
# ./gather_farm.sh <target>         #
#     <target> = (D, D2, C, Fe, Pb) #
#####################################

tarName="$@"

if [[ ${tarName} = "D" ]]; then
  auxDir="31"
elif [[ ${tarName} = "D2" ]]; then
  auxDir="32"
elif [[ ${tarName} = "C" ]]; then
  auxDir="08"
elif [[ ${tarName} = "Fe" ]]; then
  auxDir="10"
elif [[ ${tarName} = "Pb" ]]; then
  auxDir="03"
fi

FARMDIR=/home/borquez/volatile/omegaSim/farm/${tarName}

if [[ ${tarName} = "D2" ]]; then
  tarName="D"
fi

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
