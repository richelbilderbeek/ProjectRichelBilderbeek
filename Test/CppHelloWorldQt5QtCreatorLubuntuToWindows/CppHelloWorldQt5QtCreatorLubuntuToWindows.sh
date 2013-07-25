#!/bin/bash
myfile="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
mytarget="CppHelloWorldQt5QtCreatorLubuntuToWindows"
myprofile=$mytarget.pro
myexe=$mytarget".exe"

if [ ! -e $myprofile ]
then
  echo "FAIL: Qt Creator project '$myprofile' not found"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo "FAIL: "$myfile" "$myprofile" (makefile not found)"
  exit
fi

make

if [ -e ./release/$myexe ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL (executable not found)"
fi

#Cleaning up
#rm *.o
#rm Makefile
#rm Makefile.*
#rm -r release
#rm -r debug
