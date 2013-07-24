#!/bin/bash
#Script to check the status of compiles
mytempfile="tmpStatus.txt"
if [ -e $mytempfile ]
then
  rm $mytempfile
fi


for folder in `ls | egrep "Cpp"`
do
  echo $folder
  #Go in folder
  cd $folder

  for myprofile in `ls | egrep ".pro\>"`
  do
    #echo $myprofile
    mybasename=`echo $pyprofile | egrep [A-Za-z]{4}[A-Za-z]*\.`
  
    echo $mybasename
 
    #For every .pro file, 
    # 0: compile
    # 1: crosscompile using Qt4
    # (2: crosscompile using Qt5)
    #Execute script, write results to temp file in Projects folder
    #./$shfile | egrep "SUCCESS|FAIL" >> ../$mytempfile
    for type in 0 1 2
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
      1) myqmake="i686-pc-mingw32-qmake" mytypestr="Qt4LubuntuToWindows" ;; 
      2) myqmake="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake" mytypestr="Qt5LubuntuToWindows" ;; 
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
      else
        echo $myprofile", "$mytypestr": FAIL (executable not found)" >> ../$mytempfile
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

      exit #tmp
    done #next type

  done #next profile

  #Go back to Projects folder
  cd ..

done #next folder

echo ""

cat $mytempfile
