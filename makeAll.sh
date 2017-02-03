#!/bin/sh
#Copy the shell scripts to a folder in the path
cp doBoth.sh ~/bin/
cp showAll.sh ~/bin/
cp sqWellCp.sh ~/bin/
cp batchOutput/batchOutput.sh ~/bin/
cp checkOutputFolder.sh ~/bin
cp quickRestart/quickRestart.sh ~/bin
ln -sf ~/source/SqWellScripts/batchAverage/batchAverage_sqW.sh ~/bin


#Check correct numnber of command line arguments
if (( $# > 1 )); then
   echo "usage: makeAll.sh [c compiler choice: defaults to gcc if not specified]"
  exit 1
fi

if (( $# < 1 )); then
    compiler=gcc
    echo "Defaulting to gcc compiler"
fi



#Check correct numnber of command line arguments
if [[ $# -eq 1 ]]; then
    compiler=$1
   echo "Using compiler $compiler."
fi



echo ""
for f in blockVary clipQuad collateClip dosMapping multiAverage; do
    echo $f
    cd $f
    make CC=$compiler
    cd ..
    echo ""
done


