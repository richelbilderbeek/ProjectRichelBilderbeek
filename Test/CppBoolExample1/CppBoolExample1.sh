#!/bin/bash

#myqmake="i686-pc-mingw32-qmake" #Qt4
myqmake="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"

rm *.pro.user

for myprofile in `ls | egrep ".pro\>"`
do
  echo $myprofile
  mytarget=`echo $myprofile | sed "s/\.pro//"`

  $myqmake $myprofile

  if [ ! -e Makefile ]
  then
    echo "FAIL: $myqmake $myprofile"
    exit
  fi

  make

  if [ -e ./release/$mytarget".exe" ]
  then
    echo $mytarget": SUCCESS"
    #cp ./release/$mytarget".exe" ./$mytarget".exe"
    #cp ./release/$mytarget".exe" "../../../.wine/drive_c/windows/system32/"$mytarget".exe"
    cp ./release/$mytarget".exe" ~/bin/

  else
    echo $mytarget": FAIL"
    exit
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

done #next .pro file
