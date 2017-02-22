#A Script for reseting the names of configuration files, removing the DONE prefix.

for i in DONE*
do
    #echo "`echo $i | sed 's/DONE//' | sed 's/_x//'`"
    mv "$i" "`echo $i | sed 's/DONE//'| sed 's/_x//'`"
done

rm  distribution.dist
