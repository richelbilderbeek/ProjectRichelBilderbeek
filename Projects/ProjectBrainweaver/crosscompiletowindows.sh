#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

rm -r release
rm -r debug

echo "Cross compiling to Windows: student version"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake BrainweaverStudent.pro

echo "2/2: making makefile"

make

cp release/BrainweaverStudent.exe .
rm -r release
rm -r debug

echo "Cross compiling to Windows: assessor version"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake BrainweaverAssessor.pro

echo "2/2: making makefile"

make

cp release/BrainweaverAssessor.exe .
rm -r release
rm -r debug


echo "Cross compiling to Windows: developer version"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake BrainweaverDeveloper.pro

echo "2/2: making makefile"

make

cp release/BrainweaverDeveloper.exe .
rm -r release
rm -r debug


echo "Done cross compiling, starting Windows executable for developer using Wine"

zip BrainweaverExe.zip *.exe

wine BrainweaverDeveloper.exe
