#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "Cross compiling to Windows"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake ToolTestQtRoundedEditRectItem.pro

echo "2/2: making makefile"

make

echo "Done cross compiling, running Windows executable with Wine"

cd release

wine ToolTestQtRoundedEditRectItem.exe


