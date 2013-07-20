#!/bin/bash
myfile="qmake-qt4"
mytarget="ToolTestAbout"
myprofile=$mytarget.pro


if [ -e $myfile ]
then
  echo "MXE crosscompiler '$myfile' found"
else
  echo "MXE crosscompiler '$myfile' not found directly, but perhaps it is in the PATH"
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
$myfile $myprofile

if [ -e Makefile ]
then
  echo "Makefile created successfully"
else
  echo "FAIL: $myfile $myprofile"
  exit
fi

echo "2/2: making makefile"

make

if [ -e $mytarget ]
then
  echo $mytarget" (Qt4): SUCCESS"
else
  echo $mytarget" (Qt4): FAIL"
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
