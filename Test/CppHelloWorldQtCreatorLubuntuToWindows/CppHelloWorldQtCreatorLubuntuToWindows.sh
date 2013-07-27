#!/bin/bash
#From http://richelbilderbeek.nl/CppHelloWorldQtCreatorLubuntuToWindows.htm
echo "Cross compiling to Windows"

#myfile="i686-pc-mingw32-qmake"
myfile="../../Libraries/mxe/usr/bin/i686-pc-mingw32-qmake"
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

if [ -e ./release/$mytarget ]
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
