#!/bin/sh
#From http://richelbilderbeek.nl/CppMxe.htm

#Don't put the full path here. It has to be found in the 
# In /home/yourusername/.bashrc add the following line add the end instead:
# export PATH=$PATH:/home/richel/GitHubs/ProjectRichelBilderbeek/Libraries/mxe/usr/bin/
#myqmake="i686-pc-mingw32.static-qmake-qt4"
myqmake="i686-w64-mingw32.static-qmake-qt5"

echo "Displaying cross compiler version (if it is not found, set the path to YourFolder/mxe/usr/bin"
$myqmake -v

for myprofile in `ls | egrep ".pro\>"`
do
  #echo $myprofile
  mybasename=`echo $myprofile | sed "s/\.pro//"`

  #echo "mybasename: "$mybasename

  # echo "Cleaning up"
  # rm Makefile
  # rm Makefile.*
  # rm -r release
  # rm -r debug
  # rm ui_*.h
  # rm qrc_*.cpp
  # rm moc_*.cpp
  # rm object_script*.*
  # rm *.o
  # rm *_plugin_import.cpp
  # rm *.exe #Also clean up the executable

  echo "Creating makefile"

  $myqmake $myprofile

  if [ ! -e Makefile ]
  then
    echo "FAIL:"$myqmake", "$myprofile": FAIL (Makefile not found)"
    continue
  fi

  echo "Start make"

  make


  if [ -e ./release/$mybasename".exe" ]
  then
    echo $myprofile", : SUCCESS"
    if [ -e ./release/$mybasename".exe" ]
    then
      cp ./release/$mybasename".exe" .
    fi
  else
    echo $myprofile", "$mytypestr": FAIL (executable not found)"
  fi

  #Cleaning up
  # rm Makefile
  # rm Makefile.*
  # rm -r release
  # rm -r debug
  # rm ui_*.h
  # rm qrc_*.cpp
  # rm moc_*.cpp
  # rm object_script*.*
  # rm *.o
  # rm *_plugin_import.cpp

done #next myprofile
