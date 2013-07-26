#!/bin/bash
myfile="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
mytarget="ToolKalmanFiltererDesktop"
myprofile=$mytarget.pro
myexe=$mytarget.exe

if [ ! -e $myprofile ]
then
  echo $mytarget": FAIL (Qt Creator project "$myprofile" not found)"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL (makefile not found)"
  exit
fi

make

if [ -e ./release/$myexe ]
then
  echo $mytarget": SUCCESS"
  cp ./release/$myexe ./$myexe
else
  echo $mytarget": FAIL (executable not found)"
fi


#Cleaning up
rm *.o
rm object_script.*
rm -r release
rm -r debug
rm Makefile
rm Makefile.*
rm ui_*
