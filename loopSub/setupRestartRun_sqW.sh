#!/bin/bash
#set -e Dont set quit on error and checkOutputFolder might generate some errors

#Check correct number of command line arguments
if (( $# != 3 )); then
   echo "Generates output folders and submission scripts for an hpc SqWellChain run" >&2
   echo "Usage  :  setupRestartRun.sh [name of the input file (no .dat)]] [number of hpc processors][run hours]" >&2
   echo $1 $2 $3
   echo "Example:  ./setupRestartRun.sh N10TestRun 12 167" >&2
  exit 1
fi

#====Extract arguments====
NAME=$1
nProcessors=$2
runHours=$3

wDir=$(pwd)
echo $wDir

./createDirs.sh $NAME
cp ~/source/SqWellScripts/loopSub/restartMasterSub.sh $NAME.tmp
sed  -e "s/<NAME>/$NAME/g" $NAME.tmp > $NAME.sh
sed  -e "s/<NCPU>/$nProcessors/g" $NAME.sh > $NAME.tmp
sed  -e "s/<RUN_HOURS>/$runHours/g" $NAME.tmp > $NAME.sh
sed  -e "s:<WORKING_DIR>:$wDir:g" $NAME.sh > $NAME.tmp
mv $NAME.tmp $NAME.sh

#Run this part last!!
cd inputFiles
checkOutputFolder.sh $NAME.dat

echo 'setpRestartRun.sh: Created HPC submission script '$NAME.sh