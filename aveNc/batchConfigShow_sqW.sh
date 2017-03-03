#Check correct number of command line arguments
if (( $# != 2 )); then
    echo "Compares P(nc|E) average of multiple runs, to check reproducibility." >&2
    echo "Usage  :  batchConfigShow_sw.sh [.list file (as above)][Energy of Interest]" >&2
    echo "Example:  batchConfigShow_sw.sh  N5Test.list " >&2
    echo "" >&2
    echo "Requires a .list file of the form (same at batchOutput_sqW.sh):" >&2
    echo "[IGNORED][IGNORED]" >&2
    echo "[Input Filename (no .dat)]" >&2
    echo "eg:" >&2
    echo "0 20" >&2
    echo "N10Test2 0" >&2
    echo "N10Test3 0" >&2
    echo "" >&2
    echo "!!!! .list files should have a final carriage return at end!!!!" >&2
  exit 1
fi

#====Extract arguments====
ListFile=$1
EnergyVal=$2

#====Extract the folder names from the Listfile====
arr1=( $( cut -d' ' -f1 $ListFile ) )
#arr2=( $( cut -d' ' -f2 $1 ) )


cd outputFiles/
for i in $(seq 1 $(expr ${#arr1[@]} - 1))
do
    :
    echo  'Trying folder ' $i ${arr1[$i]}
   cd ${arr1[$i]}/configs
   aveNC_sqW Hist_$EnergyVal.dat Norm_$EnergyVal.dat Ave_$EnergyVal.dat
   all="$all $(pwd)/Ave_$EnergyVal.dat"

   cd ../../
done

#echo $all
xmgrace  -g 1200x900 $all &
