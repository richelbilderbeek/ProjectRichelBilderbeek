#!/bin/bash
mymake="make"
myqmake="qmake"
mytarget="CppHelloWtQtCreatorLubuntu"
myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo $mytarget": FAIL: (Qt Creator project not found)"
  exit
fi

$myqmake $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL: (makefile not found)"
  exit
fi

$mymake

if [ -e $mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL: (executable not found)"
fi

#Cleaning up
rm *.o
rm Makefile
rm $mytarget
