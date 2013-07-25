#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "1. Cross compiling to Windows: desktop application version"

echo "1.1: Creating Windows makefile"
../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake ProjectRichelBilderbeekDesktop.pro
# i686-pc-mingw32-qmake ProjectRichelBilderbeekDesktop.pro

echo "1.2: making makefile"
make

echo "1.3: copying executable"
cp release/ProjectRichelBilderbeekDesktop.exe .
