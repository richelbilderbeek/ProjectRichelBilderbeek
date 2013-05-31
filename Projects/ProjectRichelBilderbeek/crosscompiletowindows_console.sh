#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "1. Cross compiling to Windows: console application version"

echo "1.1: Creating Windows makefile"
i686-pc-mingw32-qmake ProjectRichelBilderbeekConsole.pro

echo "1.2: making makefile"
make

echo "1.3: copying executable"
cp release/ProjectRichelBilderbeekConsole.exe .
