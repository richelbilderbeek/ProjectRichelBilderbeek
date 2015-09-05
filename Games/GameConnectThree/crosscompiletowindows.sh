#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm
myqmake="i686-w64-mingw32.static-qmake-qt5"

$myqmake GameConnectThreeConsole.pro
make

$myqmake GameConnectThreeDesktop.pro
make

$myqmake GameConnectThreeWebsite.pro
make
