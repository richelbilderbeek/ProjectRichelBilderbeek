#!/bin/sh
#From http://richelbilderbeek.nl/CppQtCrosscompileToWindowsExample15.htm

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*
rm *.o
rm *_plugin_import.cpp

../../Libraries/mxe/usr/i686-pc-mingw32/qt5/bin/qmake ProjectRichelBilderbeekWebsite.pro

make

cp release/ProjectRichelBilderbeekWebsite.exe ~/bin

#Cleaning up
rm Makefile
rm Makefile.*
rm -r release
rm -r debug
rm ui_*.h
rm qrc_*.cpp
rm moc_*.cpp
rm object_script*.*
rm *.o
rm *_plugin_import.cpp

