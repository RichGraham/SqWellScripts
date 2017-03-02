#!/bin/bash
#Plots P(nc|E) for a range of different tempering levels
#Check correct number of command line arguments
if (( $# < 4 )); then
    echo "" >&2
    echo "Runs the following: " >&2
     echo "Usage  : showAllConfigDist_sqW.sh [base folder][int energy value][int LowestTemp][int HighestTemp]" >&2
   echo "Example: showAllConfigDist_sqW.sh outputFiles/N40_OpOut3/ 70 0 5  " >&2
  exit 1
fi

#====Extract arguments====
BaseFolder=$1
EnergyVal=$2
LowestTemp=$3
HighestTemp=$4

cd $BaseFolder/configs

#Run the code to average over all tempering levels (at fixed E)
aveNC_sqW Hist_$EnergyVal.dat Norm_$EnergyVal.dat Ave_$EnergyVal.dat

#Plot the data for a selected range of temperatures
for i in $(seq $(($LowestTemp+2)) $(($HighestTemp+2)))
do
  all="$all -graph 0 -autoscale none -block Norm_$EnergyVal.dat -bxy 1:$i "
done
#echo $all

xmgrace -pexec "s0 line linewidth 8"  -g 1200x900 -graph 0 Ave_$EnergyVal.dat -autoscale xy   $all &
