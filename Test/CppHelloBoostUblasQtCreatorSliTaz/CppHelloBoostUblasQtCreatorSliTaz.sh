#!/bin/bash
myfile="qmake"
mytarget="CppHelloBoostUblasQtCreatorSliTaz"
myprofile=$mytarget.pro


if [ -e $myfile ]
then
  echo "Compiler '$myfile' found"
else
  echo "Compiler '$myfile' not found directly"
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
