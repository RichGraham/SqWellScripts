#Check correct number of command line arguments
if (( $# != 2 )); then
    echo "Takes an input file, creates a restart file and submits the run" >&2
    echo "Usage  :  restartSub_sqW.sh  [previous run name] [restart run name]" >&2
    echo "Example:  restartSub_sqW.sh " >&2
  exit 1
fi

#Assign argument names
previousName=$1
restartName=$2

#Create the restart file
cd inputfiles
quickRestart.sh
