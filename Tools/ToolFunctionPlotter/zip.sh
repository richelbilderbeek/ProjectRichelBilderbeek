#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Libraries
mkdir temp_zip/Tools

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtSurfacePlotWidget
mkdir temp_zip/Libraries/fparser4.4.3
mkdir temp_zip/Libraries/fparser4.4.3/extrasrc
mkdir temp_zip/Tools/ToolSurfacePlotter

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtSurfacePlotWidget/Licence.txt temp_zip/Classes/CppQtSurfacePlotWidget/Licence.txt
cp ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp temp_zip/Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp
cp ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h temp_zip/Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h
cp ../../Libraries/fparser4.4.3/extrasrc/fp_identifier_parser.inc temp_zip/Libraries/fparser4.4.3/extrasrc/fp_identifier_parser.inc
cp ../../Libraries/fparser4.4.3/extrasrc/fp_opcode_add.inc temp_zip/Libraries/fparser4.4.3/extrasrc/fp_opcode_add.inc
cp ../../Libraries/fparser4.4.3/extrasrc/fpaux.hh temp_zip/Libraries/fparser4.4.3/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.4.3/extrasrc/fptypes.hh temp_zip/Libraries/fparser4.4.3/extrasrc/fptypes.hh
cp ../../Libraries/fparser4.4.3/fparser.cc temp_zip/Libraries/fparser4.4.3/fparser.cc
cp ../../Libraries/fparser4.4.3/fparser.hh temp_zip/Libraries/fparser4.4.3/fparser.hh
cp ../../Libraries/fparser4.4.3/fparser_gmpint.hh temp_zip/Libraries/fparser4.4.3/fparser_gmpint.hh
cp ../../Libraries/fparser4.4.3/fparser_mpfr.hh temp_zip/Libraries/fparser4.4.3/fparser_mpfr.hh
cp ../../Libraries/fparser4.4.3/fpconfig.hh temp_zip/Libraries/fparser4.4.3/fpconfig.hh
cp ../../Libraries/fparser4.4.3/fpoptimizer.cc temp_zip/Libraries/fparser4.4.3/fpoptimizer.cc
cp ../../Tools/ToolSurfacePlotter/Licence.txt temp_zip/Tools/ToolSurfacePlotter/Licence.txt
cp ../../Tools/ToolSurfacePlotter/R.png temp_zip/Tools/ToolSurfacePlotter/R.png
cp ../../Tools/ToolSurfacePlotter/ToolSurfacePlotter.qrc temp_zip/Tools/ToolSurfacePlotter/ToolSurfacePlotter.qrc
cp ../../Tools/ToolSurfacePlotter/ToolSurfacePlotterDesktop.pro temp_zip/Tools/ToolSurfacePlotter/ToolSurfacePlotterDesktop.pro
cp ../../Tools/ToolSurfacePlotter/ToolSurfacePlotterMenuImage.png temp_zip/Tools/ToolSurfacePlotter/ToolSurfacePlotterMenuImage.png
cp ../../Tools/ToolSurfacePlotter/qtmain.cpp temp_zip/Tools/ToolSurfacePlotter/qtmain.cpp
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.cpp temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.cpp
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.h temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.h
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.ui temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermaindialog.ui
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.cpp temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.cpp
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.h temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.h
cp ../../Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.ui temp_zip/Tools/ToolSurfacePlotter/qttoolsurfaceplottermenudialog.ui
cp ../../Tools/ToolSurfacePlotter/toolsurfaceplottermenudialog.cpp temp_zip/Tools/ToolSurfacePlotter/toolsurfaceplottermenudialog.cpp
cp ../../Tools/ToolSurfacePlotter/toolsurfaceplottermenudialog.h temp_zip/Tools/ToolSurfacePlotter/toolsurfaceplottermenudialog.h

FILENAME="ToolSurfacePlotterSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Libraries
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtSurfacePlotWidget/*.*
rm temp_zip/Libraries/fparser4.4.3/*.*
rm temp_zip/Libraries/fparser4.4.3/extrasrc/*.*
rm temp_zip/Tools/ToolSurfacePlotter/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtSurfacePlotWidget
rmdir temp_zip/Libraries/fparser4.4.3/extrasrc
rmdir temp_zip/Libraries/fparser4.4.3
rmdir temp_zip/Tools/ToolSurfacePlotter

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Libraries
rmdir temp_zip/Tools

echo "Removing temporary folder"

rm temp_zip/*.*
rmdir temp_zip

echo "Done"

# CreateQtProjectZipFile, version 1.3
# Copyright (C) 2012 Richel Bilderbeek
# Programmed on the 10th of June 2012
# by Richel Bilderbeek
# 
# CreateQtProjectZipFile can be downloaded from http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
# Licenced under GPL 3.0
