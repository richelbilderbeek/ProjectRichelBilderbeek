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
mkdir temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/Licence.txt temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/Licence.txt
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/PicR14x14.png temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/PicR14x14.png
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/PicSitemap14x14.png temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/PicSitemap14x14.png
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/PicTo14x14.png temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/PicTo14x14.png
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/ToolRichelbilderbeekNlSitemapGenerator.pro temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/ToolRichelbilderbeekNlSitemapGenerator.pro
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/ToolRichelbilderbeekNlSitemapGenerator.qrc temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/ToolRichelbilderbeekNlSitemapGenerator.qrc
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtmain.cpp temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtmain.cpp
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtmain.cpp\ temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtmain.cpp\
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.cpp temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.cpp
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.h temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.h
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.ui temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.ui
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.cpp temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.cpp
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.h temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.h
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.ui temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.ui
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemap_gen.py temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemap_gen.py
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.cpp temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.cpp
cp ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.h temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.h

FILENAME="ToolRichelbilderbeekNlSitemapGeneratorSource"
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
rm temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Tools/ToolRichelbilderbeekNlSitemapGenerator

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
