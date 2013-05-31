#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "Cross compiling to Windows: developer version"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake ProjectVanDenBogaart.pro

echo "2/2: making makefile"

make

echo "Done cross compiling, starting Windows executable using Wine"

cd release

wine ProjectVanDenBogaart.exe
