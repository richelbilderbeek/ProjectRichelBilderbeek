#!/bin/bash
#Script to check the status of crosscompiles
myfolderprefix="Tool"
myos='LubuntuToWindows'
mytempfile='tmp'$myos'.txt'
if [ -e $mytempfile ]
then
  rm $mytempfile
fi


for folder in `ls | egrep $myfolderprefix`
do
  echo $folder
  #Go in folder
  cd $folder

  for shfile in `ls | egrep $myos".sh"`
  do
    echo $shfile
    #Execute script, write results to temp file in Projects folder
    ./$shfile | egrep "SUCCESS|FAIL" >> ../$mytempfile

  done #next shfile

  #Go back to Projects folder
  cd ..

done #next folder

echo "\nResults: "

cat $mytempfile

rm $mytempfile
