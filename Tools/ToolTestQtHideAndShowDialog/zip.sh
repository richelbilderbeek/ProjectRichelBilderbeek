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

mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Tools/ToolTestQtHideAndShowDialog

echo "Copying files"

cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Tools/ToolTestQtHideAndShowDialog/Licence.txt temp_zip/Tools/ToolTestQtHideAndShowDialog/Licence.txt
cp ../../Tools/ToolTestQtHideAndShowDialog/ToolTestQtHideAndShowDialog.pro temp_zip/Tools/ToolTestQtHideAndShowDialog/ToolTestQtHideAndShowDialog.pro
cp ../../Tools/ToolTestQtHideAndShowDialog/cnr.sh temp_zip/Tools/ToolTestQtHideAndShowDialog/cnr.sh
cp ../../Tools/ToolTestQtHideAndShowDialog/crosscompiletowindows.sh temp_zip/Tools/ToolTestQtHideAndShowDialog/crosscompiletowindows.sh
cp ../../Tools/ToolTestQtHideAndShowDialog/qtmain.cpp temp_zip/Tools/ToolTestQtHideAndShowDialog/qtmain.cpp
cp ../../Tools/ToolTestQtHideAndShowDialog/zip.sh temp_zip/Tools/ToolTestQtHideAndShowDialog/zip.sh

FILENAME="ToolTestQtHideAndShowDialogSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Tools/ToolTestQtHideAndShowDialog/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Tools/ToolTestQtHideAndShowDialog

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
