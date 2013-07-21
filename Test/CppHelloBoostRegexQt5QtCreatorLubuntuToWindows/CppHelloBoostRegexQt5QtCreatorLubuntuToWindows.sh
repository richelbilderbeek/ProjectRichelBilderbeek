#!/bin/bash
myfile="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
mytarget="CppHelloBoostRegexQt5QtCreatorLubuntuToWindows"
myprofile=$mytarget.pro

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
rm -r release
rm -r debug
rm Makefile
rm Makefile.*
