#!/bin/bash
#Plots P(nc|E) for a range of different tempering levels
#Check correct number of command line arguments
if (( $# < 4 )); then
    echo "" >&2
    echo "Runs the following: " >&2
     echo "Usage  : showConfigDist_sqW.sh [base folder][int energy value][int LowestTemp][int HighestTemp]" >&2
   echo "Example: showConfigDist_sqW.sh outputFiles/N40_OpOut3/ 70 0 5  " >&2
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
  all="$all T$i/E$EnergyVal/normalised.dist"

done

echo $all
xmgrace -g 1200x900 $all &