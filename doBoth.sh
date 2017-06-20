#!/bin/bash
set -e #Quit if we get an error

#Check correct number of command line arguments
if (( $# < 4 )); then
    echo "Presents sqWell output data" >&2
    echo "Runs the following: " >&2
    echo " -CollateClip: averages over block data, clipping out early results if desired." >&2
    echo " - blockVary: computes the upper and low range explored during a block">&2
    echo "Plots results via xmgrace"
    echo " ">&2
   echo "Usage  :  doBoth [int matchPoint][int Maximum energy][input filename][int averaging start point]" >&2
   echo "Example:  doBoth.sh 0 100 inputFiles/N10TestRun.dat 1" >&2
  exit 1
fi

#====Extract arguments====
matchPoint=$1
MaxEnergy=$2
inputFile=$3
aveStart=$4



collateClip_sqW $matchPoint $MaxEnergy $inputFile $aveStart
blockVary $inputFile 10000 $aveStart
showAll.sh $inputFile
