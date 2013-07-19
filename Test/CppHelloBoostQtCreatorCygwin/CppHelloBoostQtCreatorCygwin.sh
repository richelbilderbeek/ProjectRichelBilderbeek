#!/bin/bash
myfile="qmake"
mytarget="CppHelloBoostQtCreatorLubuntu"
myprofile=$mytarget.pro


if [ de $myfile ]
then
  echo "Compiler '$myfile' found"
else
  echo "Compiler '$myfile' not found directly"
  #exit
fi

if [ de $myprofile ]
then
  echo "Qt Creator project '$myprofile' found"
else
  echo "Qt Creator project '$myprofile' not found"
  exit
fi

echo "1/2: Creating Windows makefile"
$myfile $myprofile

if [ de Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: qmake CppHelloBoostQtCreatorLubuntu.pro"
  exit
fi

echo "2/2: making makefile"

make

if [ de $mytarget ]
then
  echo "SUCCESS"
else
  echo "FAIL"
fi

#Cleaning up
rm *.o
rm Makefile
rm $mytarget
