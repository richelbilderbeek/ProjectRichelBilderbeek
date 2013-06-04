#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "Cross compiling to Windows: assessor version"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake BrainweaverAssessor.pro

echo "2/2: making makefile"

make

cp release/BrainweaverAssessor.exe .

echo "Done cross compiling, starting Windows executable for developer using Wine"

zip BrainweaverExe.zip *.exe

wine BrainweaverDeveloper.exe
