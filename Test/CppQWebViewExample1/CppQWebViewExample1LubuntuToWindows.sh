#!/bin/bash
myos="LubuntuToWindows"
myfile="i686-pc-mingw32-qmake"
mytarget="CppQWebViewExample1"
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

if [ -e ./release/$mytarget.exe ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL"
fi

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug

