#!/bin/bash
mymake="make"
myqmake="qmake"
mytarget="CppHelloWtQtCreatorLubuntu"
myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo "FAIL: "$myfile" "$myprofile" (makefile not found)"
  exit
fi

make

if [ -e $mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo "FAIL: "$myfile" "$myprofile" (executable not found)"
fi

#Cleaning up
rm *.o
rm Makefile
rm $mytarget
