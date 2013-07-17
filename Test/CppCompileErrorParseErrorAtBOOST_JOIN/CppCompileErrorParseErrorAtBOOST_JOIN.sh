#!/bin/bash
#From http://richelbilderbeek.nl/CppHelloBoostQtCreatorLubuntuToWindows.htm
echo "Cross compiling to Windows"

myfile="i686-pc-mingw32-qmake"
mytarget="CppCompileErrorParseErrorAtBOOST_JOIN"
myprofile=$mytarget.pro
myexefile=./release/$mytarget.exe


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
  echo "FAIL: qmake $myprofile"
  exit
fi

echo "2/2: making makefile"

make

if [ -e $myexefile ]
then
  echo "SUCCESS"
else
  echo "FAIL"
fi

#Cleaning up
rm -r debug
rm -r release
rm Makefile
rm Makefile.*
