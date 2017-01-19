#Check correct number of command line arguments
if (( $# < 1 )); then
    echo "Compares the output of multiple runs, to check reproducibility." >&2
    echo "" >&2
    echo "Requires a .list file of the form:" >&2
    echo "[matchpoint for FE][Maximum energy]" >&2
    echo "[Input Filename (no .dat)][block to start averaging from]" >&2
    echo "eg:" >&2
    echo "0 20" >&2
    echo "N10Test2 0" >&2
    echo "N10Test3 0" >&2
    echo "" >&2
   echo "Usage  :  batchOutput.sh [.list file (as above)]" >&2
   echo "Example:  batchOutput.sh N5Test.list " >&2
  exit 1
fi

arr1=( $( cut -d' ' -f1 $1 ) )
arr2=( $( cut -d' ' -f2 $1 ) )



for i in $(seq 1 $(expr ${#arr1[@]} - 1))
do
   :
   echo 'About to run doBoth.sh' ${arr1[$i]} ${arr2[$i]} 
   
   doBoth.sh ${arr1[0]} ${arr2[0]} inputFiles/${arr1[$i]}.dat ${arr2[$i]};
  
   all="$all outputFiles/weightFiles/${arr1[$i]}.dat"
done

echo $all
xmgrace  -g 1200x900 $all &


