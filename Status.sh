#!/bin/bash
#Script to check the status of compiles
#Copies executables (both Linux and Win32) executables to ~/bin (overwrites older)
set -u
set -x verbose #echo on

#echo $PATH

for superfolder in `ls`
do
  if [ ! -d $superfolder ]
  then
    echo $superfolder" is not a folder"
    continue
  fi

  echo "superfolder:"$superfolder
  cd $superfolder


  for folder in `ls`
  do
    if [ ! -d $folder ]
    then
      echo $folder" is not a folder"
      continue
    fi

    echo "folder: "$folder
    #Go in folder
    cd $folder

    rm *.pro.user

    for myprofile in `ls | egrep ".pro\>"`
    do
      echo $myprofile
      mybasename=`echo $myprofile | sed "s/\.pro//"`

      #echo "mybasename: "$mybasename
     
      #For every .pro file, 
      # 0: compile
      # 1: crosscompile using Qt5
      for type in {0,1}
      do
        myqmake=""
        mytypestr=""

        #Cleaning up
        #rm Makefile
        #rm Makefile.*
        #rm -r release
        #rm -r debug
        #rm ui_*.h
        #rm qrc_*.cpp
        #rm moc_*.cpp
        #rm object_script*.*
        #rm *.o
        #rm *_plugin_import.cpp

        case $type in

        0) myqmake="i686-w64-mingw32.static-qmake-qt5" mytypestr="Qt5LubuntuToWindows" ;;
        1) myqmake="qmake" mytypestr="LubuntuLaptop" ;;
        esac

        echo "Creating makefile"

        $myqmake $myprofile

        if [ ! -e Makefile ]
        then
          echo "FAIL:"$myqmake", "$myprofile", "$mytypestr": FAIL (Makefile not found)"
          continue
        fi

        echo "Starting make"

        make


        if [ -e $mybasename ] || [ -e ./release/$mybasename".exe" ]
        then
          echo $myprofile", "$mytypestr": SUCCESS"
          if [ -e $mybasename ] 
          then
            cp $mybasename ~/bin/ 
            rm $mybasename
          fi
          if [ -e ./release/$mybasename".exe" ] 
          then 
            cp ./release/$mybasename".exe" ~/bin/
          fi
        else
          echo $myprofile", "$mytypestr": FAIL (executable not found)"
        fi

        #Cleaning up
        #rm Makefile
        #rm Makefile.*
        #rm -r release
        #rm -r debug
        #rm ui_*.h
        #rm qrc_*.cpp
        #rm moc_*.cpp
        #rm object_script*.*
        #rm *.o
        #rm *_plugin_import.cpp


      done #next type

    done #next profile

    #Go back to supfolder
    cd ..

  done #next folder

  #Go back to ProjectRichelBilderbeek main folder
  cd ..

done #next superfolder

echo "DONE"
