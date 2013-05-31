#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Tools

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppMusic
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Tools/ToolMusicTheory

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppMusic/Licence.txt temp_zip/Classes/CppMusic/Licence.txt
cp ../../Classes/CppMusic/musicchord.cpp temp_zip/Classes/CppMusic/musicchord.cpp
cp ../../Classes/CppMusic/musicchord.h temp_zip/Classes/CppMusic/musicchord.h
cp ../../Classes/CppMusic/musicnote.cpp temp_zip/Classes/CppMusic/musicnote.cpp
cp ../../Classes/CppMusic/musicnote.h temp_zip/Classes/CppMusic/musicnote.h
cp ../../Classes/CppMusic/musicscale.cpp temp_zip/Classes/CppMusic/musicscale.cpp
cp ../../Classes/CppMusic/musicscale.h temp_zip/Classes/CppMusic/musicscale.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Tools/ToolMusicTheory/PicGreen.png temp_zip/Tools/ToolMusicTheory/PicGreen.png
cp ../../Tools/ToolMusicTheory/PicRed.png temp_zip/Tools/ToolMusicTheory/PicRed.png
cp ../../Tools/ToolMusicTheory/R.png temp_zip/Tools/ToolMusicTheory/R.png
cp ../../Tools/ToolMusicTheory/ToolMusicTheory.png temp_zip/Tools/ToolMusicTheory/ToolMusicTheory.png
cp ../../Tools/ToolMusicTheory/ToolMusicTheory.qrc temp_zip/Tools/ToolMusicTheory/ToolMusicTheory.qrc
cp ../../Tools/ToolMusicTheory/ToolMusicTheoryDesktop.pro temp_zip/Tools/ToolMusicTheory/ToolMusicTheoryDesktop.pro
cp ../../Tools/ToolMusicTheory/crosscompiletowindows.sh temp_zip/Tools/ToolMusicTheory/crosscompiletowindows.sh
cp ../../Tools/ToolMusicTheory/musictheorymenudialog.cpp temp_zip/Tools/ToolMusicTheory/musictheorymenudialog.cpp
cp ../../Tools/ToolMusicTheory/musictheorymenudialog.h temp_zip/Tools/ToolMusicTheory/musictheorymenudialog.h
cp ../../Tools/ToolMusicTheory/qtchordedge.cpp temp_zip/Tools/ToolMusicTheory/qtchordedge.cpp
cp ../../Tools/ToolMusicTheory/qtchordedge.h temp_zip/Tools/ToolMusicTheory/qtchordedge.h
cp ../../Tools/ToolMusicTheory/qtchordrelationswidget.cpp temp_zip/Tools/ToolMusicTheory/qtchordrelationswidget.cpp
cp ../../Tools/ToolMusicTheory/qtchordrelationswidget.h temp_zip/Tools/ToolMusicTheory/qtchordrelationswidget.h
cp ../../Tools/ToolMusicTheory/qtchordvertex.cpp temp_zip/Tools/ToolMusicTheory/qtchordvertex.cpp
cp ../../Tools/ToolMusicTheory/qtchordvertex.h temp_zip/Tools/ToolMusicTheory/qtchordvertex.h
cp ../../Tools/ToolMusicTheory/qtmain.cpp temp_zip/Tools/ToolMusicTheory/qtmain.cpp
cp ../../Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.cpp temp_zip/Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.cpp
cp ../../Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.h temp_zip/Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.h
cp ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.cpp temp_zip/Tools/ToolMusicTheory/qtmusictheorymenudialog.cpp
cp ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.h temp_zip/Tools/ToolMusicTheory/qtmusictheorymenudialog.h
cp ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.ui temp_zip/Tools/ToolMusicTheory/qtmusictheorymenudialog.ui
cp ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.cpp temp_zip/Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.cpp
cp ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.h temp_zip/Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.h
cp ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.ui temp_zip/Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.ui
cp ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.cpp temp_zip/Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.cpp
cp ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.h temp_zip/Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.h
cp ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.ui temp_zip/Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.ui

FILENAME="ToolMusicTheorySource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppMusic/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Tools/ToolMusicTheory/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppMusic
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Tools/ToolMusicTheory

echo "Removing main folders"

rmdir temp_zip/Classes
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
