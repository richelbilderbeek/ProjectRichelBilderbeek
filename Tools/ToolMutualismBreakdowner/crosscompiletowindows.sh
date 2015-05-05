#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "Cross compiling to Windows"

echo "1/2: Creating Windows makefile"
i686-w64-mingw32.static-qmake-qt5 ToolMutualismBreakdowner.pro


echo "2/2: making makefile"

make

echo "Done"
