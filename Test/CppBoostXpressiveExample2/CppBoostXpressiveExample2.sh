#!/bin/bash
#Script to check the status of compiles
#Copies executables (both Linux and Win32) executables to ~/bin (overwrites older)
#set -x verbose #echo on

mytempfile="tmp.txt"
if [ -e $mytempfile ]
then
  rm $mytempfile
fi

rm *.pro.user

for myprofile in `ls | egrep ".pro\>"`
do
  echo $myprofile
  mybasename=`echo $myprofile | sed "s/\.pro//"`
 
  #For every .pro file, 
  # 0: compile
  # 1: crosscompile using Qt5
  for type in 0 1
  do
    myqmake=""
    mytypestr=""

    #Cleaning up
    rm Makefile
    rm Makefile.*
    rm -r release
    rm -r debug
    rm ui_*.h
    rm qrc_*.cpp
    rm moc_*.cpp
    rm object_script*.*
    rm *.o
    rm *_plugin_import.cpp

    case $type in
    0) myqmake="qmake" mytypestr="Lubuntu" ;;
    1) myqmake="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake" mytypestr="Qt5LubuntuToWindows" ;; 
    esac

    $myqmake $myprofile

    if [ ! -e Makefile ]
    then
      echo $myprofile", "$mytypestr": FAIL (Makefile not found)" >> ../$mytempfile
      continue
    fi

    make


    if [ -e $mybasename ] || [ -e ./release/$mybasename".exe" ]
    then
      echo $myprofile", "$mytypestr": SUCCESS" >> ../$mytempfile
      #echo "SUCCESS for mybasename: "$mybasename
      if [ -e $mybasename ] 
      then
        #echo "(1) cp "$mybasename" ~/bin/" 
        cp $mybasename ~/bin/ 
        rm $mybasename
      fi
      if [ -e ./release/$mybasename".exe" ] 
      then 
        #echo "(2) cp ./release/"$mybasename".exe ~/bin/"
        cp ./release/$mybasename".exe" ~/bin/
      fi
    else
      echo $myprofile", "$mytypestr": FAIL (executable not found)" >> ../$mytempfile
      #echo "FAIL for mybasename: "$mybasename
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
    rm *.o
    rm *_plugin_import.cpp


  done #next type

done #next profile

cat $mytempfile

rm $mytempfile

