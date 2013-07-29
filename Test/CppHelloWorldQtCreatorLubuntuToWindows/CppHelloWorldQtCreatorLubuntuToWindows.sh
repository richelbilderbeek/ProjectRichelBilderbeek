#!/bin/bash
myfile="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
mytarget="CppHelloWorldQtCreatorLubuntuToWindows"
myprofile=$mytarget.pro


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

if [ -e ./release/$mytarget".exe" ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL"
fi
echo "2/2: making makefile"
make

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
