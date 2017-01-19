#Check correct number of command line arguments
if (( $# < 1 )); then
    echo "Averages over the output of multiple runs, to improve accuracy." >&2
    echo "Usage  :  batchAverage_sqW.sh [.list file - see batchOutput.sh)]" >&2
    echo "Example:  batchAverage_sqW.sh N5Test.list" >&2
    echo "!!!! .list files should have a final carriage return at end!!!!" >&2
  exit 1
fi


for var in "$@"
do
    echo "$var"
    cp $var dum.arg
    echo $var".dat" >> dum.arg
    multiAverage_sqW  $(cat dum.arg)
    #multiAverage_sqW `< $var`
    all="$all $(tail -1 dum.arg)"
done

echo $all
xmgrace  -g 1200x900 $all &
rm dum.arg

