#Check correct number of command line arguments
if (( $# != 2 )); then
    echo "Makes a loopSub" >&2
    echo "Usage  :  loopSub_sqW.sh  [.list file - see batchOutput.sh)] []" >&2
    echo "Example:  loopSub_sqW.sh " >&2
  exit 1
fi

#Assign argument names

