#!/bin/bash
myfile="qmake"
mytarget="ToolTestAbout"
myprofile=$mytarget.pro

if [ ! -e $myprofile ]
then
  echo 
  echo $mytarget": FAIL (Qt Creator project "$myprofile" not found)"
  exit
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL ("$myfile $myprofile" failed)"
  exit
fi

make

if [ -e $mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL ("$mytarget" not found)"
fi

#Cleaning up
rm $mytarget
#rm -r release
#rm -r debug
rm Makefile
#rm Makefile.*
rm ui_*
rm *.o
rm moc_*
rm qrc_*
