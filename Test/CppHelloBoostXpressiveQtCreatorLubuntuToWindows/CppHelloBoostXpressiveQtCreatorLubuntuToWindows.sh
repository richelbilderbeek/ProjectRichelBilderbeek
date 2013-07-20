#!/bin/bash
myfile="i686-pc-mingw32-qmake"
mytarget="CppHelloBoostXpressiveQtCreatorLubuntuToWindows"
myprofile=$mytarget.pro
myexefile=release/$mytarget.exe


if [ -e $myfile ]
then
  echo "MXE crosscompiler '$myfile' found"
else
  echo "MXE crosscompiler '$myfile' not found directly, but perhaps it is in the PATH"
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

$myfile $myprofile

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: $myfile $myprofile"
  exit
fi

echo "2/2: Making makefile"

make

if [ -e $myexefile ]
then
  echo "SUCCESS"
else
  echo $myexefile
  echo "FAIL"
fi

#Cleaning up
rm -r release
rm -r debug
rm Makefile
rm Makefile.*
