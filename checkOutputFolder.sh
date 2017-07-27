#Check correct number of command line arguments
if (( $# < 1 )); then
   echo "Checks that the input filename and output folder name are the same (to ensure that output data are not written to the wrong place!)" >&2
   echo "Usage  : checkOutputFolder [inputfile name] " >&2
   echo "Example:  checkOutputFolder.sh N10TestRun.dat" >&2
  exit 1
fi

filename=${1%.*}
s=$(sed '34q;d' $1)
foldername=$(echo $s | awk -F[//] '{print $2}')
echo "Testing if file and folder name match..."
echo $foldername " (Folder)"
echo $filename " (Input file name)"

if [ "$foldername" == "$filename" ];
        then
            echo "...they are the same."
else
    echo ""
    echo "**********************************************************************"
    echo "!!!!!!!!!!!!!File and folder names do not match!!!!!!!!!!!!!!!!!!!!!!!"
        echo "**********************************************************************"
fi

