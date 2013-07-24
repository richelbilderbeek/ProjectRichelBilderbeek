#!/bin/bash
#myfile="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake" #Qt5
myfile="i686-pc-mingw32-qmake" #Qt4
mytarget="ProjectBrainweaverAssessor"
myprofile=$mytarget".pro"
myexe=$mytarget".exe"

#Cleaning up
rm *.o
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*
rm *_plugin_import.cpp

if [ ! -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo "FAIL: $myfile $myprofile"
  exit
fi

make

if [ -e ./release/$myexe ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL"
fi

#Cleaning up
rm *.o
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*
rm *_plugin_import.cpp
