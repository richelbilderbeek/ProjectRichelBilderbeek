#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

echo "Cross compiling to Windows"

echo "1/2: Creating Windows makefile"
i686-pc-mingw32-qmake ToolTestQtKeyboardFriendlyGraphicsView.pro

echo "2/2: making makefile"

make

echo "Done"
