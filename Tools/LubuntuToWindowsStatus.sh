#!/bin/bash
#Script to check the status of MXE crosscompiles
myos="LubuntuToWindows"
mytempfile='tmp'$myos'.txt'

if [ -e $mytempfile ]
then
  rm $mytempfile
fi


for mytest in BoostLexical_Cast BoostRegex BoostXpressive Cpp11 Qt Qwt World
do
myfolder='CppHello'$mytest'QtCreator'$myos
myscript=$myfolder'.sh'

if [ ! -d $myfolder ]
then
  echo "Folder '$myfolder' not found"
  continue
fi

cd $myfolder

if [ ! -e $myscript ]
then
  echo "MXE crosscompiler script '$myscript' not found"
  continue
fi

echo $mytest >> ../$mytempfile
./$myscript | egrep "SUCCESS|FAIL" >> ../$mytempfile

cd ..

done

cat $mytempfile | sed 'N;s/\n/: /'

