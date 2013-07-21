#!/bin/bash
myfile="qmake"
mytarget="CppHelloQwtQtCreatorLubuntu"
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

if [ -e $mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL"
fi

#Cleaning up
rm *.o
rm Makefile
rm $mytarget
