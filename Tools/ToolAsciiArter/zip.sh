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
mkdir temp_zip/Classes/CppAsciiArter
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Tools/ToolAsciiArter

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppAsciiArter/Licence.txt temp_zip/Classes/CppAsciiArter/Licence.txt
cp ../../Classes/CppAsciiArter/asciiarter.cpp temp_zip/Classes/CppAsciiArter/asciiarter.cpp
cp ../../Classes/CppAsciiArter/asciiarter.h temp_zip/Classes/CppAsciiArter/asciiarter.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Tools/ToolAsciiArter/AsciiArter.png temp_zip/Tools/ToolAsciiArter/AsciiArter.png
cp ../../Tools/ToolAsciiArter/Licence.txt temp_zip/Tools/ToolAsciiArter/Licence.txt
cp ../../Tools/ToolAsciiArter/R.png temp_zip/Tools/ToolAsciiArter/R.png
cp ../../Tools/ToolAsciiArter/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolAsciiArter/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolAsciiArter/ToolAsciiArter.qrc temp_zip/Tools/ToolAsciiArter/ToolAsciiArter.qrc
cp ../../Tools/ToolAsciiArter/ToolAsciiArterDesktop.pro temp_zip/Tools/ToolAsciiArter/ToolAsciiArterDesktop.pro
cp ../../Tools/ToolAsciiArter/ToolAsciiArterWebsite.pro temp_zip/Tools/ToolAsciiArter/ToolAsciiArterWebsite.pro
cp ../../Tools/ToolAsciiArter/ToolAsciiArterWelcome.png temp_zip/Tools/ToolAsciiArter/ToolAsciiArterWelcome.png
cp ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp temp_zip/Tools/ToolAsciiArter/asciiartermaindialog.cpp
cp ../../Tools/ToolAsciiArter/asciiartermaindialog.h temp_zip/Tools/ToolAsciiArter/asciiartermaindialog.h
cp ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp temp_zip/Tools/ToolAsciiArter/asciiartermenudialog.cpp
cp ../../Tools/ToolAsciiArter/asciiartermenudialog.h temp_zip/Tools/ToolAsciiArter/asciiartermenudialog.h
cp ../../Tools/ToolAsciiArter/crosscompiletowindows.sh temp_zip/Tools/ToolAsciiArter/crosscompiletowindows.sh
cp ../../Tools/ToolAsciiArter/qtasciiartermaindialog.cpp temp_zip/Tools/ToolAsciiArter/qtasciiartermaindialog.cpp
cp ../../Tools/ToolAsciiArter/qtasciiartermaindialog.h temp_zip/Tools/ToolAsciiArter/qtasciiartermaindialog.h
cp ../../Tools/ToolAsciiArter/qtasciiartermaindialog.ui temp_zip/Tools/ToolAsciiArter/qtasciiartermaindialog.ui
cp ../../Tools/ToolAsciiArter/qtasciiartermenudialog.cpp temp_zip/Tools/ToolAsciiArter/qtasciiartermenudialog.cpp
cp ../../Tools/ToolAsciiArter/qtasciiartermenudialog.h temp_zip/Tools/ToolAsciiArter/qtasciiartermenudialog.h
cp ../../Tools/ToolAsciiArter/qtasciiartermenudialog.ui temp_zip/Tools/ToolAsciiArter/qtasciiartermenudialog.ui
cp ../../Tools/ToolAsciiArter/qtmain.cpp temp_zip/Tools/ToolAsciiArter/qtmain.cpp
cp ../../Tools/ToolAsciiArter/wt.css temp_zip/Tools/ToolAsciiArter/wt.css
cp ../../Tools/ToolAsciiArter/wtasciiartermaindialog.cpp temp_zip/Tools/ToolAsciiArter/wtasciiartermaindialog.cpp
cp ../../Tools/ToolAsciiArter/wtasciiartermaindialog.h temp_zip/Tools/ToolAsciiArter/wtasciiartermaindialog.h
cp ../../Tools/ToolAsciiArter/wtmain.cpp temp_zip/Tools/ToolAsciiArter/wtmain.cpp
cp ../../Tools/ToolAsciiArter/zip.sh temp_zip/Tools/ToolAsciiArter/zip.sh

FILENAME="ToolAsciiArterSource"
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
rm temp_zip/Classes/CppAsciiArter/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Tools/ToolAsciiArter/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppAsciiArter
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Tools/ToolAsciiArter

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
