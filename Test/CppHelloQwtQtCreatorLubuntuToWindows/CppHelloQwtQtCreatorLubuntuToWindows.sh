#!/bin/bash
#From http://richelbilderbeek.nl/CppHelloQwtQtCreatorLubuntuToWindows.htm
echo "Cross compiling to Windows"

myfile="i686-pc-mingw32-qmake"
mytarget="CppHelloQwtQtCreatorLubuntuToWindows"
myprofile=$mytarget.pro


if [ -e $myfile ]
then
  echo "MXE crosscompiler '$myfile' found"
else
  echo "MXE crosscompiler '$myfile' not found"
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
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm object_script.CppHelloQwtQtCreatorLubuntuToWindows.*
