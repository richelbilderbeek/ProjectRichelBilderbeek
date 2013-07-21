#!/bin/bash
myfile="i686-pc-mingw32-qmake"

for mytarget in "ToolCodeToHtmlDesktop" #"ToolCodeToHtmlConsole" "ToolCodeToHtmlDesktop" "ToolCodeToHtmlWebsite"
do

myprofile=$mytarget".pro"
myexe=$mytarget".exe"

if [ ! -e $myprofile ]
then
  echo 
  echo $mytarget": FAIL (Qt Creator project "$myprofile" not found)"
  continue
fi

$myfile $myprofile

if [ ! -e Makefile ]
then
  echo $mytarget": FAIL ("$myfile $myprofile" failed)"
  continue
fi

make

if [ -e ./release/$mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL"
fi

#Cleaning up
rm qrc_*.*
rm ui_*.*
rm moc_*.*
rm *.o
rm Makefile
rm Makefile.*
rm -r release
rm -r debug

done
