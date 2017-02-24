#!/bin/bash

#Check correct number of command line arguments
if (( $# < 3 )); then
    echo "Computes P(nc|E) for a specific E for temps 0....HighestTemp" >&2
    echo "Runs the following: " >&2
    echo " - updateConfigDist_sqW: takes all config files in a folder and updates the current distribution" >&2
    echo " ">&2
   echo "Usage  :  confUpEn_sqW.sh [base folder][int EnergyVal][int HighestTemp]" >&2
   echo "Example:  confUpEn_sqW.sh outputFiles/N40_OpOut1/ 100 12" >&2
  exit 1
fi

#====Extract arguments====
BaseFolder=$1
EnergyVal=$2
HighestTemp=$3

cd $BaseFolder/configs

for i in $(seq 0 $HighestTemp)
do
    cd T$i/E$EnergyVal
    pwd
    updateConfigDist_sqW *.dat
    all="$all $(pwd)/normalised.dist"
    cd ../../

done
xmgrace -g 1200x900 $all &
