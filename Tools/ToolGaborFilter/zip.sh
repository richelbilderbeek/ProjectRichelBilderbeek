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
mkdir temp_zip/Classes/CppGaborFilter
mkdir temp_zip/Classes/CppGaborFilterWidget
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtGaborFilterWidget
mkdir temp_zip/Classes/CppQtSurfacePlotWidget
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Tools/ToolGaborFilter

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppGaborFilter/Licence.txt temp_zip/Classes/CppGaborFilter/Licence.txt
cp ../../Classes/CppGaborFilter/gaborfilter.cpp temp_zip/Classes/CppGaborFilter/gaborfilter.cpp
cp ../../Classes/CppGaborFilter/gaborfilter.h temp_zip/Classes/CppGaborFilter/gaborfilter.h
cp ../../Classes/CppGaborFilterWidget/Licence.txt temp_zip/Classes/CppGaborFilterWidget/Licence.txt
cp ../../Classes/CppGaborFilterWidget/gaborfilterwidget.cpp temp_zip/Classes/CppGaborFilterWidget/gaborfilterwidget.cpp
cp ../../Classes/CppGaborFilterWidget/gaborfilterwidget.h temp_zip/Classes/CppGaborFilterWidget/gaborfilterwidget.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtGaborFilterWidget/Licence.txt temp_zip/Classes/CppQtGaborFilterWidget/Licence.txt
cp ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.cpp temp_zip/Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.cpp
cp ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.h temp_zip/Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.h
cp ../../Classes/CppQtSurfacePlotWidget/Licence.txt temp_zip/Classes/CppQtSurfacePlotWidget/Licence.txt
cp ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp temp_zip/Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.cpp
cp ../../Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h temp_zip/Classes/CppQtSurfacePlotWidget/qtsurfaceplotwidget.h
cp ../../Classes/CppRectangle/Licence.txt temp_zip/Classes/CppRectangle/Licence.txt
cp ../../Classes/CppRectangle/rectangle.cpp temp_zip/Classes/CppRectangle/rectangle.cpp
cp ../../Classes/CppRectangle/rectangle.h temp_zip/Classes/CppRectangle/rectangle.h
cp ../../Classes/CppWidget/Licence.txt temp_zip/Classes/CppWidget/Licence.txt
cp ../../Classes/CppWidget/widget.cpp temp_zip/Classes/CppWidget/widget.cpp
cp ../../Classes/CppWidget/widget.h temp_zip/Classes/CppWidget/widget.h
cp ../../Tools/ToolGaborFilter/R.png temp_zip/Tools/ToolGaborFilter/R.png
cp ../../Tools/ToolGaborFilter/ToolGaborFilter.png temp_zip/Tools/ToolGaborFilter/ToolGaborFilter.png
cp ../../Tools/ToolGaborFilter/ToolGaborFilter.qrc temp_zip/Tools/ToolGaborFilter/ToolGaborFilter.qrc
cp ../../Tools/ToolGaborFilter/ToolGaborFilterDesktop.pro temp_zip/Tools/ToolGaborFilter/ToolGaborFilterDesktop.pro
cp ../../Tools/ToolGaborFilter/qtmain.cpp temp_zip/Tools/ToolGaborFilter/qtmain.cpp
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.cpp temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.cpp
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.h temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.h
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.ui temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.ui
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.cpp temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.cpp
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.h temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.h
cp ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.ui temp_zip/Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.ui
cp ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.cpp temp_zip/Tools/ToolGaborFilter/toolgaborfiltermenudialog.cpp
cp ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.h temp_zip/Tools/ToolGaborFilter/toolgaborfiltermenudialog.h
cp ../../Tools/ToolGaborFilter/zip.sh temp_zip/Tools/ToolGaborFilter/zip.sh

FILENAME="ToolGaborFilterSource"
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
rm temp_zip/Classes/CppGaborFilter/*.*
rm temp_zip/Classes/CppGaborFilterWidget/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtGaborFilterWidget/*.*
rm temp_zip/Classes/CppQtSurfacePlotWidget/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Tools/ToolGaborFilter/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppGaborFilter
rmdir temp_zip/Classes/CppGaborFilterWidget
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtGaborFilterWidget
rmdir temp_zip/Classes/CppQtSurfacePlotWidget
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Tools/ToolGaborFilter

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
