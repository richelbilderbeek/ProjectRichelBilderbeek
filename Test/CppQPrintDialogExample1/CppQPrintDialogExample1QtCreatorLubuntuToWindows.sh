#!/bin/bash

#myqmake="i686-pc-mingw32-qmake" #Qt4
myqmake="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
mytarget="CppQPrintDialogExample1"

myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

$myqmake $myprofile

if [ ! -e Makefile ]
then
  echo "FAIL: $myqmake $myprofile"
  exit
fi

make

if [ -e ./release/$mytarget".exe" ]
then
  echo $mytarget": SUCCESS"
  cp ./release/$mytarget".exe" ./$mytarget".exe"
  cp ./release/$mytarget".exe" "../../../.wine/drive_c/windows/system32/"$mytarget".exe"

else
  echo $mytarget": FAIL"
fi

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*
rm *_plugin_import.cpp
