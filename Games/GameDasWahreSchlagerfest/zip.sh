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
mkdir temp_zip/Games/GameDasWahreSchlagerfest

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfest.qrc temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfest.qrc
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestBeer.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestBeer.png
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestBratwurst.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestBratwurst.png
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestDesktop.pro temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestDesktop.pro
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestRichel.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestRichel.png
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestSecretMessage.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestSecretMessage.png
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestSmiley.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfestSmiley.png
cp ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfest_1_0.png temp_zip/Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfest_1_0.png
cp ../../Games/GameDasWahreSchlagerfest/R.png temp_zip/Games/GameDasWahreSchlagerfest/R.png
cp ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.cpp temp_zip/Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.cpp
cp ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.h temp_zip/Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.h
cp ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp temp_zip/Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp
cp ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h temp_zip/Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.cpp temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.cpp
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.h temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.h
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.ui temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.ui
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.cpp temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.cpp
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.h temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.h
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.ui temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.ui
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.cpp temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.cpp
cp ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.h temp_zip/Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.h
cp ../../Games/GameDasWahreSchlagerfest/qtmain.cpp temp_zip/Games/GameDasWahreSchlagerfest/qtmain.cpp

FILENAME="GameDasWahreSchlagerfestSource"
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
rm temp_zip/Games/GameDasWahreSchlagerfest/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Games/GameDasWahreSchlagerfest

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
