#!/bin/bash
mymake="make"
myqmake="qmake"
mytarget="CppHelloWtQtCreatorLubuntu"
myprofile=$mytarget.pro


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

echo "1/2: Creating Windows makefile"
$myqmake $myprofile

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: $myqmake $myprofile"
  exit
fi

echo "2/2: Making makefile"

$mymake

if [ -e $mytarget ]
then
  echo "SUCCESS"
else
  echo "FAIL"
fi

#Cleaning up
rm *.o
rm Makefile
rm $mytarget
