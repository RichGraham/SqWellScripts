#!/bin/bash

#Check correct number of command line arguments
if (( $# < 4 )); then
    echo "Computes P(nc|E) for a specific E for temps LowestTemp....HighestTemp" >&2
    echo "Runs the following: " >&2
    echo " - updateConfigDist_sqW: takes all config files in a folder and updates the current distribution" >&2
    echo " ">&2
   echo "Usage  :  confUpEn_sqW.sh [base folder][int EnergyVal][int LowestTemp][int HighestTemp]" >&2
   echo "Example:  confUpEn_sqW.sh outputFiles/N40_OpOut1/ 100 0 11" >&2
  exit 1
fi

#====Extract arguments====
BaseFolder=$1
EnergyVal=$2
LowestTemp=$3
HighestTemp=$4

cd $BaseFolder/configs

for i in $(seq $LowestTemp $HighestTemp)
do
    cd T$i/E$EnergyVal
    pwd
    updateConfigDist_sqW *.dat
    #all="$all $(pwd)/normalised.dist"
    cd ../../

done
#xmgrace -g 1200x900 $all &
