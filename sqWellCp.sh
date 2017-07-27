#!/bin/bash

#Check correct numnber of command line arguments
if (( $# != 2 )); then
    echo "Creates a copy of an input file with a new name and new output folders" >&2
    echo "Usage:  sqWellCp.sh [orginal input file] [copied inputfile]" >&2
    echo "Example: sqWellCp.sh N10TestRun.dat N5TestRun.dat" >&2
  exit 1
fi

#====Extract arguments====
originalFile=$1
newFile=$2


#Check that the newFile is not already there
if [  -f $newFile ]; then
    echo "File $newFile already exists: refusing to overwrite!!!! "
    exit 1
fi

#Check that the original files does exist
if [ ! -f $originalFile ]; then
    echo "File $originalFile does not exist: can't continue!!! "
    exit 1
fi

#Extract the first part of the filenames
old=${originalFile%.*}
new=${newFile%.*}
echo $old $new

#Copy the file and replace the filename within the new file so that the output folders have the correct name
cat $originalFile | sed -e "s/$old\//$new\//" > $newFile
