#!/bin/bash
set -e #Quit if we get an error

#Count the number of arguments (accounting for options)
while getopts "na:" opt; do
    case $opt in
    n) 
	    nflag=true  # Handle -n
	    ;;

    a) 
	    aflag=true  # Handle -n
	    ;;
    esac
done

if [ "$nflag" == "true" ]; then
    shift #Shift moves the arugment numbers down by one (to remove the option as a argument)

fi

maxProc=16
if [ "$aflag" == "true" ]; then
    shift #Shift moves the arugment numbers down by one (to remove the option as a argument)
    maxProc=28
fi


#Check correct number of command line arguments (accounting for options)
if (( $# != 2 )); then
    echo "Begins/continues a cycle of self resubmitting square well runs" >&2
    echo "Usage  :  loopSub_sqW.sh  [run hours] [previous job name]]" >&2
    echo "Example:  loopSub_sqW.sh 167 256T.472A16b9-1" >&2
    echo "Options -n=start a new run"
  exit 1
fi

#Assign argument names
runHours=$1
jobName=$2


echo 'Run hours :'$runHours '   jobName :'$jobName


#Check that the input file exists
myFile=inputFiles/$jobName.dat
if [ ! -f $myFile  ]; then
    echo $myFile": File not found!"
    exit 1
fi
    


#Check for -lp string in the filename
if [[ $jobName == *"lp-"* ]]; then
echo "lp- detected in filename"
else
  echo 'The jobName ('$jobName') does not contain lp-**. Consider running the following command'
  echo 'cd inputFiles; sqWellCp.sh '$jobName'.dat '$jobName'lp-0.dat;cd ..'
  exit
fi


#Extract information from job name and create new jobname
jobNumber=$(echo "${jobName##*-}")
masterJobName=$(echo "${jobName%-*}")
#Test it's an integer
if [[ $jobNumber =~ ^-?[0-9]+$ ]]; then
    echo 'Job number = '$jobNumber
else
    echo "The job number has been detected as "$jobNumber.
    echo "This doesn't seem to be an integer. Correct the jobName ("$jobName") and retry"
    exit
fi



#Check that the job number is not crazily large
#Needs adding!!!!



# Create any required new input files
if [ "$nflag" == "true" ]; then #Just use the given name as the new job name
    newJobName=$jobName
    
else #Otherwise create a new one and create the job run
    newJobNumber=$(($jobNumber + 1))
    newJobName=$masterJobName'-'$newJobNumber
    echo 'Old run: '$jobName
    echo 'New run: '$newJobName
    
#Create the new input file
    cd inputFiles
    quickRestart.sh $jobName.dat $newJobName.dat
    cd ..
fi



#Read the number of temperatures from the new input file
nProcs=$(echo $(cat inputFiles/$newJobName.dat | grep NUM_TEMPS | cut -d ':' -f 1) | xargs)

#Test it's an integer
if [[ $nProcs =~ ^-?[0-9]+$ ]]; then
    echo 'Job has '$nProcs' temperature'
else
    echo "The nProcs has been detected as ("$nProcs")"
    echo "This doesn't seem to be an integer. Check the input file ("$jobName") and retry"
    exit
fi

#Check we're not exceeding the maximum number of processors
if [ "$nProcs" -gt "$maxProc" ]; then
	nProcs=$maxProc
fi

echo 'This will be a' $nProcs 'processor run for ' $runHours ' hours.'



#Generate the scripts
setupRestartRun_sqW.sh $newJobName $nProcs $runHours

#Append the restart commands to the end of the new script
echo loopSub_sqW.sh $runHours $newJobName >> $newJobName.sh

#Submit the job!!
if [ "$nflag" == "true" ]; then
    echo 'You need to submit the job now!'
    echo 'qsub ' $newJobName.sh
else
    qsub $newJobName.sh
fi