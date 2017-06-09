#!/bin/bash
set -e #Quit if we get an error

#Count the number of arguments (accounting for options)
while getopts "n:" opt; do
    case $opt in
    n) nflag=true ; # Handle -n
    esac
done

if [ "$nflag" == "true" ]; then
    shift #Shift moves the arugment numbers down by one (to remove the option as a argument)
fi


#Check correct number of command line arguments (accounting for options)
if (( $# != 1 )); then
    echo "Begins/continues a cycle of self resubmitting square well runs" >&2
    echo "Usage  :  loopSub_sqW.sh  [previous job name]]" >&2
    echo "Example:  loopSub_sqW.sh 256T.472A16b9-1" >&2
    echo "Options -n=start a new run"
  exit 1
fi

#Assign argument names
jobName=$1

#Extract information from job name and create new jobname
jobNumber=$(echo "${jobName##*-}")
masterJobName=$(echo "${jobName%-*}")
newJobNumber=$(($jobNumber + 1))
newJobName=$masterJobName-$newJobNumber
echo 'Old run: '$jobName
echo 'New run: '$newJobName

#Check that the job number is not crazily large
#Needs adding!!!!


if [ "$nflag" == "true" ]; then
    newJobName=$jobName
    #Check the input file exisits
    if [ ! -f $newJobName ]; then
	echo "File not found!"
	exit 1
    fi
    
    #Read the number of temperatures from the new input file
    nProcs=$(cat inputFiles/$newJobName.dat | grep NUM_TEMPS | cut -d ':' -f 1)
    echo 'This will be a' $nProcs 'processor run'

    #Set up the folders and submission script
    ./setupRun.sh $newJobName $nProcs

else
    #Set up the new run (but don't yet submit)
    restartSub_sqW.sh $jobName $newJobName
fi

#Append the restart commands to the end of the new script
echo loopSub_sqW.sh $newJobName >> $newJobName.sh

#Submit the job!!
qsub $newJobName.sh
