#!/bin/bash
mymake="make.exe"
myqmake="/usr/lib/qt4/bin/qmake.exe"
mytarget="CppHelloCpp11QtCreatorCygwin"
myprofile=$mytarget.pro
myexe=$mytarget.exe


if [ -e $myqmake ]
then
  echo "Compiler '$myqmake' found"
else
  echo "Compiler '$myqmake' not found directly"
  #exit
fi

if [ -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' found"
else
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

echo "1/2: Creating Windows makefile"
$myqmake $myprofile

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: $myqmake $myprofile"
  exit
fi

if [ -e $mymake ]
then
  echo "Compiler '$mymake' found"
else
  echo "Compiler '$mymake' not found directly"
  #exit
fi

echo "2/2: making makefile"

$mymake

echo $myexe

if [ -e $myexe ]
then
  echo "SUCCESS"
else
  echo "FAIL"
fi

#Cleaning up
rm *.o
rm $myexe
rm Makefile
