for var in "$@"
do
    echo "$var"
    multiAverage_sqW `< $var`
    all="$all $(tail -1 $var)"
done

#arr1=( $( cut -d' ' -f1 $1 ) )
#arr2=( $( cut -d' ' -f2 $1 ) )


#for i in $(seq 1 $(expr ${#arr1[@]} - 1))
#do
#   :
#   echo ${arr1[$i]} ${arr2[$i]}
#   doBoth.sh ${arr1[0]} ${arr2[0]} inputFiles/${arr1[$i]}.dat ${arr2[$i]}
#   all="$all outputFiles/weightFiles/${arr1[$i]}.dat"
#done

echo $all
xmgrace  -g 1200x900 $all &


