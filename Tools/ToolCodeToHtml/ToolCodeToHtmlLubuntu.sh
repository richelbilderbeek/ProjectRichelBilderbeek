#!/bin/bash
myfile="qmake"

for mytarget in "ToolCodeToHtmlConsole" "ToolCodeToHtmlDesktop" "ToolCodeToHtmlWebsite"
do

myprofile=$mytarget".pro"
myexe=$mytarget

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

if [ -e $mytarget ]
then
  echo $mytarget": SUCCESS"
else
  echo $mytarget": FAIL ("$mytarget" not found)"
fi

#Cleaning up
rm qrc_*.*
rm ui_*.*
rm moc_*.*
rm *.o
rm Makefile
rm Makefile.*
#rm -r release
#rm -r debug

done
