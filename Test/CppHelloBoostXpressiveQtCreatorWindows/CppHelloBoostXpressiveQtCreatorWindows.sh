#!/bin/bash
mymake="e:/Qt/Qt5.1.0/Tools/mingw48_32/bin/mingw32-make.exe"
myqmake="e:/Qt/Qt5.1.0/5.1.0/mingw48_32/bin/qmake.exe"
mytarget="CppHelloBoostXpressiveQtCreatorWindows"
myprofile=$mytarget.pro
myexe=release/$mytarget.exe


if [ -e $myqmake ]
then
  echo "Compiler '$myqmake' found"
else
  echo "Compiler '$myqmake' not found directly"
  #exit
fi

if [ -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' found"
else
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

echo "1/2: Creating makefile"

$myqmake $myprofile

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: $myqmake $myprofile"
  exit
fi

if [ -e $mymake ]
then
  echo "Compiler '$mymake' found"
else
  echo "Compiler '$mymake' not found directly"
  #exit
fi

echo "2/2: Making makefile"

$mymake

echo $myexe

if [ -e $myexe ]
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
