#Check correct number of command line arguments
if (( $# != 1 )); then
    echo "Computes P(nc|E) averaged over multiple runs and saves to folder" >&2
    echo "Usage  :  configAllE_sqW.sh [.list file as below]" >&2
    echo "Example:  ******* " >&2
    echo "" >&2
    echo "Requires a .list file of the form (same at batchOutput_sqW.sh):" >&2
    echo "[IGNORED][Maximum Energy]" >&2
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


#====Extract the folder names from the Listfile====
arr1=( $( cut -d' ' -f1 $ListFile ) )
arr2=( $( cut -d' ' -f2 $1 ) )
MaxEnergy=${arr2[0]}

#Extract just the name from the list file
outFolder=${ListFile%.*}
mkdir -p $outFolder


for EnergyVal in $(seq 1 $MaxEnergy)
do
    :
    allFolders=""
    for i in $(seq 1 $(expr ${#arr1[@]} - 1))
    do
	:
	allFolders="$allFolders outputFiles/${arr1[$i]}/configs/Hist_$EnergyVal.dat"
    done
    multiAveNc_sqW $allFolders $outFolder/BatchAve_$EnergyVal.dat
done
