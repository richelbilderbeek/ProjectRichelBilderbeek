#!/bin/bash
#Script to check the status of compiles
myos='Lubuntu'
mytempfile='tmp'$myos'.txt'
if [ -e $mytempfile ]
then
  rm $mytempfile
fi


for mytest in CodeToHtml TestAbout
do
myfolder='Tool'$mytest
myscript=$myfolder$myos'.sh'

if [ ! -d $myfolder ]
then
  echo "Folder '$myfolder' not found"
  continue
fi

cd $myfolder

if [ ! -e $myscript ]
then
  echo "Compile script '$myscript' not found"
  continue
fi

#echo $mytest >> ../$mytempfile
./$myscript | egrep "SUCCESS|FAIL" >> ../$mytempfile

cd ..

done

cat $mytempfile #| sed 'N;s/\n/: /'

rm $mytempfile
