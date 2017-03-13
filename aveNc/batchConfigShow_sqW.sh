#Check correct number of command line arguments
if (( $# != 2 )); then
    echo "Compares P(nc|E) over of multiple runs with their average, to check reproducibility." >&2
    echo "Usage  :  batchConfigShow_sw.sh [.list file (as below)][Energy of Interest]" >&2
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

#====Average over individual files====
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
cd ../

for i in $(seq 1 $(expr ${#arr1[@]} - 1))
do
    :
    allFolders="$allFolders outputFiles/${arr1[$i]}/configs/Hist_$EnergyVal.dat"
done


#====Make an output filename from arugments====
OutputName=${ListFile%.*}_PncE_$EnergyVal.dat

#====Run the averaging code====
multiAveNc_sqW $allFolders $OutputName


#echo $all
xmgrace  -pexec "s0 line linewidth 8" -g 1200x900 $OutputName $all &
