#!/bin/sh
# Created from file '../../Tools/ToolRegexTester/ToolRegexTesterConsole.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Tools/ToolRegexTester
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppQtHideAndShowDialog

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppTrace/Licence.txt Projects/Classes/CppTrace/Licence.txt
cp ../../Tools/ToolRegexTester/zip.sh Projects/Tools/ToolRegexTester/zip.sh
cp ../../Tools/ToolRegexTester/PicR.png Projects/Tools/ToolRegexTester/PicR.png
cp ../../Tools/ToolRegexTester/main.cpp Projects/Tools/ToolRegexTester/main.cpp
cp ../../Tools/ToolRegexTester/PicQt.png Projects/Tools/ToolRegexTester/PicQt.png
cp ../../Tools/ToolRegexTester/qtmain.cpp Projects/Tools/ToolRegexTester/qtmain.cpp
cp ../../Tools/ToolRegexTester/Licence.txt Projects/Tools/ToolRegexTester/Licence.txt
cp ../../Tools/ToolRegexTester/PicBoost.png Projects/Tools/ToolRegexTester/PicBoost.png
cp ../../Tools/ToolRegexTester/PicCpp11.png Projects/Tools/ToolRegexTester/PicCpp11.png
cp ../../Tools/ToolRegexTester/PicCppTr1.png Projects/Tools/ToolRegexTester/PicCppTr1.png
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Tools/ToolRegexTester/ToolRegexTester.qrc Projects/Tools/ToolRegexTester/ToolRegexTester.qrc
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Tools/ToolRegexTester/regextestermaindialog.h Projects/Tools/ToolRegexTester/regextestermaindialog.h
cp ../../Tools/ToolRegexTester/regextestermenudialog.h Projects/Tools/ToolRegexTester/regextestermenudialog.h
cp ../../Tools/ToolRegexTester/crosscompiletowindows.sh Projects/Tools/ToolRegexTester/crosscompiletowindows.sh
cp ../../Tools/ToolRegexTester/qtregextestermaindialog.h Projects/Tools/ToolRegexTester/qtregextestermaindialog.h
cp ../../Tools/ToolRegexTester/qtregextestermenudialog.h Projects/Tools/ToolRegexTester/qtregextestermenudialog.h
cp ../../Tools/ToolRegexTester/regextestermaindialog.cpp Projects/Tools/ToolRegexTester/regextestermaindialog.cpp
cp ../../Tools/ToolRegexTester/regextestermenudialog.cpp Projects/Tools/ToolRegexTester/regextestermenudialog.cpp
cp ../../Tools/ToolRegexTester/regextesterqtmaindialog.h Projects/Tools/ToolRegexTester/regextesterqtmaindialog.h
cp ../../Tools/ToolRegexTester/ToolRegexTesterConsole.pro Projects/Tools/ToolRegexTester/ToolRegexTesterConsole.pro
cp ../../Tools/ToolRegexTester/ToolRegexTesterDesktop.pro Projects/Tools/ToolRegexTester/ToolRegexTesterDesktop.pro
cp ../../Tools/ToolRegexTester/qtregextestermaindialog.ui Projects/Tools/ToolRegexTester/qtregextestermaindialog.ui
cp ../../Tools/ToolRegexTester/qtregextestermenudialog.ui Projects/Tools/ToolRegexTester/qtregextestermenudialog.ui
cp ../../Tools/ToolRegexTester/regextestertr1maindialog.h Projects/Tools/ToolRegexTester/regextestertr1maindialog.h
cp ../../Tools/ToolRegexTester/qtregextestermaindialog.cpp Projects/Tools/ToolRegexTester/qtregextestermaindialog.cpp
cp ../../Tools/ToolRegexTester/qtregextestermenudialog.cpp Projects/Tools/ToolRegexTester/qtregextestermenudialog.cpp
cp ../../Tools/ToolRegexTester/regextesterqtmaindialog.cpp Projects/Tools/ToolRegexTester/regextesterqtmaindialog.cpp
cp ../../Tools/ToolRegexTester/regextesterboostmaindialog.h Projects/Tools/ToolRegexTester/regextesterboostmaindialog.h
cp ../../Tools/ToolRegexTester/regextestercpp11maindialog.h Projects/Tools/ToolRegexTester/regextestercpp11maindialog.h
cp ../../Tools/ToolRegexTester/regextestertr1maindialog.cpp Projects/Tools/ToolRegexTester/regextestertr1maindialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Tools/ToolRegexTester/regextesterboostmaindialog.cpp Projects/Tools/ToolRegexTester/regextesterboostmaindialog.cpp
cp ../../Tools/ToolRegexTester/regextestercpp11maindialog.cpp Projects/Tools/ToolRegexTester/regextestercpp11maindialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

FILENAME="../../Tools/ToolRegexTesterSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Tools/ToolRegexTester/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Tools/ToolRegexTester
rmdir Projects/Classes/CppTrace
rmdir Projects/Classes/CppAbout
rmdir Projects/Classes
rmdir Projects/Tools
rmdir Projects

echo "Done"

# QtCreatorProFileZipScript, version 1.0
# Copyright (C) 2013 Richel Bilderbeek
# Programmed on the 19th of May 2013
# by Richel Bilderbeek
# 
# QtCreatorProFileZipScript can be downloaded from http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm
# Licenced under GPL 3.0

