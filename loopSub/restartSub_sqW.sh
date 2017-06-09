#!/bin/bash

set -e

#Check correct number of command line arguments
if (( $# != 2 )); then
    echo "Takes an input file, creates a restart file and submits the run" >&2
    echo "Usage  :  restartSub_sqW.sh  [previous run name] [restart run name]" >&2
    echo "Example:  restartSub_sqW.sh 256T.472A16b9-1 256T.472A16b9-2 " >&2
  exit 1
fi

#Assign argument names
previousName=$1
restartName=$2

#Create the restart file
cd inputFiles
quickRestart.sh $previousName.dat $restartName.dat
cd ..

#Read the number of temperatures from the new input file
#Cut the first column from the line in the inputfile labelled NUM_TEMPS
nProcs=$(cat inputFiles/$restartName.dat | grep NUM_TEMPS | cut -d ':' -f 1)
echo 'This will be a' $nProcs 'processor run'

#Set up the folders and submission script
./setupRun.sh $restartName $nProcs

#Don't submit yet as the loopSub_sqW.sh script needs to add the restart part to the end of the run

