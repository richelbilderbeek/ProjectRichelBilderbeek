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
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppRandomCode
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Tools/ToolRandomCode

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppRandomCode/randomcode.cpp temp_zip/Classes/CppRandomCode/randomcode.cpp
cp ../../Classes/CppRandomCode/randomcode.h temp_zip/Classes/CppRandomCode/randomcode.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Tools/ToolRandomCode/Licence.txt temp_zip/Tools/ToolRandomCode/Licence.txt
cp ../../Tools/ToolRandomCode/R.png temp_zip/Tools/ToolRandomCode/R.png
cp ../../Tools/ToolRandomCode/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolRandomCode/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolRandomCode/ToolRandomCode.png temp_zip/Tools/ToolRandomCode/ToolRandomCode.png
cp ../../Tools/ToolRandomCode/ToolRandomCode.qrc temp_zip/Tools/ToolRandomCode/ToolRandomCode.qrc
cp ../../Tools/ToolRandomCode/ToolRandomCodeDesktop.pro temp_zip/Tools/ToolRandomCode/ToolRandomCodeDesktop.pro
cp ../../Tools/ToolRandomCode/ToolRandomCodeDesktopConsole.pro temp_zip/Tools/ToolRandomCode/ToolRandomCodeDesktopConsole.pro
cp ../../Tools/ToolRandomCode/ToolRandomCodeIcon14x14.png temp_zip/Tools/ToolRandomCode/ToolRandomCodeIcon14x14.png
cp ../../Tools/ToolRandomCode/ToolRandomCodeWebsite.pro temp_zip/Tools/ToolRandomCode/ToolRandomCodeWebsite.pro
cp ../../Tools/ToolRandomCode/ToolRandomCodeWelcome.png temp_zip/Tools/ToolRandomCode/ToolRandomCodeWelcome.png
cp ../../Tools/ToolRandomCode/main temp_zip/Tools/ToolRandomCode/main
cp ../../Tools/ToolRandomCode/main.cpp temp_zip/Tools/ToolRandomCode/main.cpp
cp ../../Tools/ToolRandomCode/qtmain.cpp temp_zip/Tools/ToolRandomCode/qtmain.cpp
cp ../../Tools/ToolRandomCode/qtrandomcodemaindialog.cpp temp_zip/Tools/ToolRandomCode/qtrandomcodemaindialog.cpp
cp ../../Tools/ToolRandomCode/qtrandomcodemaindialog.h temp_zip/Tools/ToolRandomCode/qtrandomcodemaindialog.h
cp ../../Tools/ToolRandomCode/qtrandomcodemaindialog.ui temp_zip/Tools/ToolRandomCode/qtrandomcodemaindialog.ui
cp ../../Tools/ToolRandomCode/qtrandomcodemenudialog.cpp temp_zip/Tools/ToolRandomCode/qtrandomcodemenudialog.cpp
cp ../../Tools/ToolRandomCode/qtrandomcodemenudialog.h temp_zip/Tools/ToolRandomCode/qtrandomcodemenudialog.h
cp ../../Tools/ToolRandomCode/qtrandomcodemenudialog.ui temp_zip/Tools/ToolRandomCode/qtrandomcodemenudialog.ui
cp ../../Tools/ToolRandomCode/randomcodemenudialog.cpp temp_zip/Tools/ToolRandomCode/randomcodemenudialog.cpp
cp ../../Tools/ToolRandomCode/randomcodemenudialog.h temp_zip/Tools/ToolRandomCode/randomcodemenudialog.h
cp ../../Tools/ToolRandomCode/wt.css temp_zip/Tools/ToolRandomCode/wt.css
cp ../../Tools/ToolRandomCode/wtmain.cpp temp_zip/Tools/ToolRandomCode/wtmain.cpp
cp ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.cpp temp_zip/Tools/ToolRandomCode/wtrandomcodegeneratedialog.cpp
cp ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.h temp_zip/Tools/ToolRandomCode/wtrandomcodegeneratedialog.h
cp ../../Tools/ToolRandomCode/wtrandomcodemenudialog.cpp temp_zip/Tools/ToolRandomCode/wtrandomcodemenudialog.cpp
cp ../../Tools/ToolRandomCode/wtrandomcodemenudialog.h temp_zip/Tools/ToolRandomCode/wtrandomcodemenudialog.h
cp ../../Tools/ToolRandomCode/zip.sh temp_zip/Tools/ToolRandomCode/zip.sh

FILENAME="ToolRandomCodeSource"
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
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppRandomCode/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Tools/ToolRandomCode/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppRandomCode
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Tools/ToolRandomCode

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
