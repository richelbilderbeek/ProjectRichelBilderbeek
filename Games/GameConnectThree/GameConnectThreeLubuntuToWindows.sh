#!/bin/bash
#myfile="/usr/i686-pc-mingw32/qt5/bin/qmake"
myfile="i686-pc-mingw32-qmake"
mytarget="GameConnectThreeDesktop"
myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL"
  exit
fi

make

if [ ! -e ./release/$mytarget ]
then
  echo $mytarget": FAIL"
fi
echo "2/2: making makefile"
make



#Cleaning up
rm -r release
rm -r debug
rm Makefile
rm Makefile.*
rm ui_*
