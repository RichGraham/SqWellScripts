#!/bin/sh
#Copy the shell scripts to a folder in the path
cp doBoth.sh ~/bin/
cp showAll.sh ~/bin/
cp sqWellCp.sh ~/bin/
cp batchOutput/batchOutput.sh ~/bin/
cp checkOutputFolder.sh ~/bin
cp quickRestart/quickRestart.sh ~/bin
ln -sf ~/source/SqWellScripts/batchAverage/batchAverage_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/updateConfigDist/resetNames_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/updateConfigDist/confUpEn_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/updateConfigDist/allConfigDist_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/updateConfigDist/showConfigDist_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/aveNc/showAllConfigDist_sqW.sh ~/bin
ln -sf ~/source/SqWellScripts/aveNc/batchConfigShow_sqW.sh  ~/bin
ln -sf ~/source/SqWellScripts/aveNc/configAllE_sqW.sh  ~/bin

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
for f in blockVary clipQuad collateClip dosMapping multiAverage updateConfigDist aveNc multiAveNc OP_mapping; do
    echo $f
    cd $f
    make CC=$compiler
    cd ..
    echo ""
done


