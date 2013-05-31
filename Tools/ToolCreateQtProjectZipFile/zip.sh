#!/bin/sh
# Created from file '../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppProFile
mkdir Projects/Classes/CppQrcFile
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppQtCreatorProFile
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Tools/ToolCreateQtProjectZipFile

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/Licence.txt Projects/Classes/CppAbout/Licence.txt
cp ../../Classes/CppQrcFile/qrcfile.h Projects/Classes/CppQrcFile/qrcfile.h
cp ../../Classes/CppProFile/Licence.txt Projects/Classes/CppProFile/Licence.txt
cp ../../Classes/CppQrcFile/Licence.txt Projects/Classes/CppQrcFile/Licence.txt
cp ../../Classes/CppQrcFile/qrcfile.cpp Projects/Classes/CppQrcFile/qrcfile.cpp
cp ../../Classes/CppQtAboutDialog/Licence.txt Projects/Classes/CppQtAboutDialog/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/R.png Projects/Tools/ToolCreateQtProjectZipFile/R.png
cp ../../Classes/CppQtCreatorProFile/Licence.txt Projects/Classes/CppQtCreatorProFile/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/zip.sh Projects/Tools/ToolCreateQtProjectZipFile/zip.sh
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/main.cpp Projects/Tools/ToolCreateQtProjectZipFile/main.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/qtmain.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtmain.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/Licence.txt Projects/Tools/ToolCreateQtProjectZipFile/Licence.txt
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.h
cp ../../Tools/ToolCreateQtProjectZipFile/PicTo14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicTo14x14.png
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/PicZip14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicZip14x14.png
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/PicQtCreator14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicQtCreator14x14.png
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFile.qrc Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFile.qrc
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.h Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.h Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pro Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pro
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.ui Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.ui Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.cpp

FILENAME="../../Tools/ToolCreateQtProjectZipFileSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Tools/ToolCreateQtProjectZipFile/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Classes/CppQtCreatorProFile/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Classes/CppQrcFile/*.*
rm Projects/Classes/CppProFile/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Tools/ToolCreateQtProjectZipFile
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Classes/CppQtCreatorProFile
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Classes/CppQrcFile
rmdir Projects/Classes/CppProFile
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

