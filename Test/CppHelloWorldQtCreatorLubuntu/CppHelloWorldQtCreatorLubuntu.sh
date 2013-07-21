#!/bin/bash
mymake="make"
myqmake="qmake"
mytarget="CppHelloWorldQtCreatorLubuntu"
myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

$myqmake $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL"  
  exit
fi

$mymake

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
