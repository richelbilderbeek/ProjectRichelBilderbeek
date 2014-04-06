#!/bin/sh
#From http://richelbilderbeek.nl/CppMxe.htm
myqmake="../../Libraries/mxe/usr/i686-pc-mingw32.static/qt5/bin/qmake"
#myqmake="../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake"
myprofile="CppMxeExample1.pro"
mybasename=`echo $myprofile | sed "s/\.pro//"`

echo "Cross compiling to Windows"

if [ ! -e $myqmake ]
then
  echo "FAIL:"$myqmake", "": FAIL (qmake not found)"
fi

echo "Remove previous makefile"
if [ -e Makefile ]
then
  rm Makefile
fi

echo "Creating Windows makefile"
$myqmake $myprofile

if [ ! -e Makefile ]
then
  echo "FAIL:"$myqmake", "$myprofile", "": FAIL (Makefile not found)"
  exit
fi

echo "2/2: making makefile"

make

if [ -e $mybasename ] || [ -e ./release/$mybasename".exe" ]
then
  echo $myprofile": SUCCESS"
else
  echo $myprofile": FAIL (executable not found)"
fi
