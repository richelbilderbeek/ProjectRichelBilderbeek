#!/bin/bash
#From http://richelbilderbeek.nl/CppMxe.htm

echo "Cross compiling to Windows"

echo "1/2: Creating Windows makefile"
myfile="../../Libraries/mxe/usr/bin/i686-pc-mingw32-qmake"

if [ -e $myfile ]
then
  echo "MXE crosscompiler '$myfile' found"
else
  echo "MXE crosscompiler '$myfile' not found"
  exit
fi

./$myfile CppMxeExample4.pro
exit


echo "2/2: making makefile"

make

echo "Done"
