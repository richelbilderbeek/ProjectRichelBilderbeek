#!/bin/bash

myfile="qmake"
for mytarget in "ProjectBrainweaverDeveloper" "ProjectBrainweaverStudent" "ProjectBrainweaverAssessor"
do

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
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*

done
