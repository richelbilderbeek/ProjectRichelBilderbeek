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
mkdir temp_zip/Classes/CppHtmlPage
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Tools/ToolCreateGlossary

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppHtmlPage/htmlpage.cpp temp_zip/Classes/CppHtmlPage/htmlpage.cpp
cp ../../Classes/CppHtmlPage/htmlpage.h temp_zip/Classes/CppHtmlPage/htmlpage.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Tools/ToolCreateGlossary/Licence.txt temp_zip/Tools/ToolCreateGlossary/Licence.txt
cp ../../Tools/ToolCreateGlossary/R.png temp_zip/Tools/ToolCreateGlossary/R.png
cp ../../Tools/ToolCreateGlossary/ToolCreateGlossary.qrc temp_zip/Tools/ToolCreateGlossary/ToolCreateGlossary.qrc
cp ../../Tools/ToolCreateGlossary/ToolCreateGlossaryConsole.pro temp_zip/Tools/ToolCreateGlossary/ToolCreateGlossaryConsole.pro
cp ../../Tools/ToolCreateGlossary/ToolCreateGlossaryDesktop.pro temp_zip/Tools/ToolCreateGlossary/ToolCreateGlossaryDesktop.pro
cp ../../Tools/ToolCreateGlossary/createglossarymaindialog.cpp temp_zip/Tools/ToolCreateGlossary/createglossarymaindialog.cpp
cp ../../Tools/ToolCreateGlossary/createglossarymaindialog.h temp_zip/Tools/ToolCreateGlossary/createglossarymaindialog.h
cp ../../Tools/ToolCreateGlossary/createglossarymenudialog.cpp temp_zip/Tools/ToolCreateGlossary/createglossarymenudialog.cpp
cp ../../Tools/ToolCreateGlossary/createglossarymenudialog.h temp_zip/Tools/ToolCreateGlossary/createglossarymenudialog.h
cp ../../Tools/ToolCreateGlossary/main.cpp temp_zip/Tools/ToolCreateGlossary/main.cpp
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.cpp temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymaindialog.cpp
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.h temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymaindialog.h
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.ui temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymaindialog.ui
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.cpp temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymenudialog.cpp
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.h temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymenudialog.h
cp ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.ui temp_zip/Tools/ToolCreateGlossary/qtcreateglossarymenudialog.ui
cp ../../Tools/ToolCreateGlossary/qtmain.cpp temp_zip/Tools/ToolCreateGlossary/qtmain.cpp
cp ../../Tools/ToolCreateGlossary/zip.sh temp_zip/Tools/ToolCreateGlossary/zip.sh

FILENAME="ToolCreateGlossarySource"
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
rm temp_zip/Classes/CppHtmlPage/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Tools/ToolCreateGlossary/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppHtmlPage
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Tools/ToolCreateGlossary

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
