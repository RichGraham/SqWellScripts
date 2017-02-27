#!/bin/bash

#Check correct number of command line arguments
if (( $# < 5 )); then
    echo "Computes P(nc|E) for a specific E for temps LowestTemp....HighestTemp and plots dists" >&2
    echo "Runs the following: " >&2
    echo " - updateConfigDist_sqW: takes all config files in a folder and updates the current distribution" >&2
    echo " ">&2
   echo "Usage  : allConfigDist_sqW.sh [base folder][int LowestTemp][int HighestTemp] [int LowestEnergy][int Highest Energy]" >&2
   echo "Example:  " >&2
  exit 1
fi

#====Extract arguments====
BaseFolder=$1
LowestTemp=$2
HighestTemp=$3
LowestE=$4
HighestE=$5


for i in $(seq $LowestE $HighestE)
do
    echo Energy level: $i
    confUpEn_sqW.sh $BaseFolder $i $LowestTemp $HighestTemp

done

