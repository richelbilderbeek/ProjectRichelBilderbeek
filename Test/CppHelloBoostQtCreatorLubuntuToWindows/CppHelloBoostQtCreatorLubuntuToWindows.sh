#!/bin/bash
#From http://richelbilderbeek.nl/CppHelloBoostQtCreatorLubuntuToWindows.htm
echo "Cross compiling to Windows"

myfile="i686-pc-mingw32-qmake"
#myfile="../../Libraries/mxe/usr/bin/i686-pc-mingw32-qmake"
mytarget="CppHelloBoostQtCreatorLubuntuToWindows"
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
  echo "FAIL: qmake CppHelloBoostQtCreatorLubuntu.pro"
  exit
fi

echo "2/2: making makefile"

make

if [ -e /release/$target.exe ]
then
  echo "SUCCES"
else
  echo "FAIL"
fi

#Cleaning up
#rm ui_*.*
#rm Makefile
#rm Makefile.*
#rm $target
