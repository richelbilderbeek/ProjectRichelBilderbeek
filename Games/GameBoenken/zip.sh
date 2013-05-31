#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Games

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Games/GameBoenken

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Games/GameBoenken/Computer.png temp_zip/Games/GameBoenken/Computer.png
cp ../../Games/GameBoenken/GameBoenken.pro temp_zip/Games/GameBoenken/GameBoenken.pro
cp ../../Games/GameBoenken/GameBoenken.qrc temp_zip/Games/GameBoenken/GameBoenken.qrc
cp ../../Games/GameBoenken/Green.png temp_zip/Games/GameBoenken/Green.png
cp ../../Games/GameBoenken/Grey.png temp_zip/Games/GameBoenken/Grey.png
cp ../../Games/GameBoenken/Human.png temp_zip/Games/GameBoenken/Human.png
cp ../../Games/GameBoenken/Licence.txt temp_zip/Games/GameBoenken/Licence.txt
cp ../../Games/GameBoenken/PlayerBlue.png temp_zip/Games/GameBoenken/PlayerBlue.png
cp ../../Games/GameBoenken/PlayerRed.png temp_zip/Games/GameBoenken/PlayerRed.png
cp ../../Games/GameBoenken/R.png temp_zip/Games/GameBoenken/R.png
cp ../../Games/GameBoenken/boenkenarenasettings.h temp_zip/Games/GameBoenken/boenkenarenasettings.h
cp ../../Games/GameBoenken/boenkencontrols.h temp_zip/Games/GameBoenken/boenkencontrols.h
cp ../../Games/GameBoenken/boenkengame.cpp temp_zip/Games/GameBoenken/boenkengame.cpp
cp ../../Games/GameBoenken/boenkengame.h temp_zip/Games/GameBoenken/boenkengame.h
cp ../../Games/GameBoenken/boenkenmenudialog.cpp temp_zip/Games/GameBoenken/boenkenmenudialog.cpp
cp ../../Games/GameBoenken/boenkenmenudialog.h temp_zip/Games/GameBoenken/boenkenmenudialog.h
cp ../../Games/GameBoenken/boenkensprite.cpp temp_zip/Games/GameBoenken/boenkensprite.cpp
cp ../../Games/GameBoenken/boenkensprite.h temp_zip/Games/GameBoenken/boenkensprite.h
cp ../../Games/GameBoenken/boenkenspriteball.cpp temp_zip/Games/GameBoenken/boenkenspriteball.cpp
cp ../../Games/GameBoenken/boenkenspriteball.h temp_zip/Games/GameBoenken/boenkenspriteball.h
cp ../../Games/GameBoenken/boenkenspritemoving.cpp temp_zip/Games/GameBoenken/boenkenspritemoving.cpp
cp ../../Games/GameBoenken/boenkenspritemoving.h temp_zip/Games/GameBoenken/boenkenspritemoving.h
cp ../../Games/GameBoenken/boenkenspritenonmoving.cpp temp_zip/Games/GameBoenken/boenkenspritenonmoving.cpp
cp ../../Games/GameBoenken/boenkenspritenonmoving.h temp_zip/Games/GameBoenken/boenkenspritenonmoving.h
cp ../../Games/GameBoenken/boenkenspriteplayer.cpp temp_zip/Games/GameBoenken/boenkenspriteplayer.cpp
cp ../../Games/GameBoenken/boenkenspriteplayer.h temp_zip/Games/GameBoenken/boenkenspriteplayer.h
cp ../../Games/GameBoenken/crosscompiletowindows.sh temp_zip/Games/GameBoenken/crosscompiletowindows.sh
cp ../../Games/GameBoenken/doxygen.txt temp_zip/Games/GameBoenken/doxygen.txt
cp ../../Games/GameBoenken/qtboenkenarenadialog.cpp temp_zip/Games/GameBoenken/qtboenkenarenadialog.cpp
cp ../../Games/GameBoenken/qtboenkenarenadialog.h temp_zip/Games/GameBoenken/qtboenkenarenadialog.h
cp ../../Games/GameBoenken/qtboenkenarenadialog.ui temp_zip/Games/GameBoenken/qtboenkenarenadialog.ui
cp ../../Games/GameBoenken/qtboenkencontrolsdialog.cpp temp_zip/Games/GameBoenken/qtboenkencontrolsdialog.cpp
cp ../../Games/GameBoenken/qtboenkencontrolsdialog.h temp_zip/Games/GameBoenken/qtboenkencontrolsdialog.h
cp ../../Games/GameBoenken/qtboenkencontrolsdialog.ui temp_zip/Games/GameBoenken/qtboenkencontrolsdialog.ui
cp ../../Games/GameBoenken/qtboenkenmaindialog.cpp temp_zip/Games/GameBoenken/qtboenkenmaindialog.cpp
cp ../../Games/GameBoenken/qtboenkenmaindialog.h temp_zip/Games/GameBoenken/qtboenkenmaindialog.h
cp ../../Games/GameBoenken/qtboenkenmaindialog.ui temp_zip/Games/GameBoenken/qtboenkenmaindialog.ui
cp ../../Games/GameBoenken/qtboenkenmenudialog.cpp temp_zip/Games/GameBoenken/qtboenkenmenudialog.cpp
cp ../../Games/GameBoenken/qtboenkenmenudialog.h temp_zip/Games/GameBoenken/qtboenkenmenudialog.h
cp ../../Games/GameBoenken/qtboenkenmenudialog.ui temp_zip/Games/GameBoenken/qtboenkenmenudialog.ui
cp ../../Games/GameBoenken/qtboenkenplayersdialog.cpp temp_zip/Games/GameBoenken/qtboenkenplayersdialog.cpp
cp ../../Games/GameBoenken/qtboenkenplayersdialog.h temp_zip/Games/GameBoenken/qtboenkenplayersdialog.h
cp ../../Games/GameBoenken/qtboenkenplayersdialog.ui temp_zip/Games/GameBoenken/qtboenkenplayersdialog.ui
cp ../../Games/GameBoenken/qtboenkenpresskeydialog.cpp temp_zip/Games/GameBoenken/qtboenkenpresskeydialog.cpp
cp ../../Games/GameBoenken/qtboenkenpresskeydialog.h temp_zip/Games/GameBoenken/qtboenkenpresskeydialog.h
cp ../../Games/GameBoenken/qtboenkenpresskeydialog.ui temp_zip/Games/GameBoenken/qtboenkenpresskeydialog.ui
cp ../../Games/GameBoenken/qtboenkentraindialog.cpp temp_zip/Games/GameBoenken/qtboenkentraindialog.cpp
cp ../../Games/GameBoenken/qtboenkentraindialog.h temp_zip/Games/GameBoenken/qtboenkentraindialog.h
cp ../../Games/GameBoenken/qtboenkentraindialog.ui temp_zip/Games/GameBoenken/qtboenkentraindialog.ui
cp ../../Games/GameBoenken/qtmain.cpp temp_zip/Games/GameBoenken/qtmain.cpp

FILENAME="GameBoenkenSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Games
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Games/GameBoenken/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Games/GameBoenken

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Games

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
