#!/bin/bash
myfile="i686-pc-mingw32-qmake"
mytarget="CppHelloBoostLexical_CastQtCreatorLubuntuToWindows"
myprofile=$mytarget.pro


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

echo "2/2: making makefile"

make

if [ -e ./release/$mytarget.exe ]
then
  echo "SUCCESS"
else
  echo "FAIL"
fi

#Cleaning up
rm -r release
rm -r debug
rm Makefile
rm Makefile.*
