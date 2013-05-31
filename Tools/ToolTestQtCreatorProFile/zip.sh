#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/..
mkdir temp_zip/Classes
mkdir temp_zip/Website

echo "Creating of all subfolders"

mkdir temp_zip/../ToolRichelBilderbeekGallery
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppCodeToHtml
mkdir temp_zip/Classes/CppProFile
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtRichelBilderbeekGalleryDialog
mkdir temp_zip/Classes/CppRichelBilderbeekProgram
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtRichelBilderbeekGalleryDialog
mkdir temp_zip/Website

echo "Copying files"

cp ../../../ToolRichelBilderbeekGallery/*.* temp_zip/../ToolRichelBilderbeekGallery
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppCodeToHtml/*.* temp_zip/Classes/CppCodeToHtml
cp ../../Classes/CppProFile/*.* temp_zip/Classes/CppProFile
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtRichelBilderbeekGalleryDialog/*.* temp_zip/Classes/CppQtRichelBilderbeekGalleryDialog
cp ../../Classes/CppRichelBilderbeekProgram/*.* temp_zip/Classes/CppRichelBilderbeekProgram
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtRichelBilderbeekGalleryDialog/*.* temp_zip/Classes/CppWtRichelBilderbeekGalleryDialog
cp ../../Website/*.* temp_zip/Website

FILENAME="ToolRichelBilderbeekGallerySource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME ..
zip -r $FILENAME Classes
zip -r $FILENAME Website
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/../ToolRichelBilderbeekGallery/*.*
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppCodeToHtml/*.*
rm temp_zip/Classes/CppProFile/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtRichelBilderbeekGalleryDialog/*.*
rm temp_zip/Classes/CppRichelBilderbeekProgram/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtRichelBilderbeekGalleryDialog/*.*
rm temp_zip/Website/*.*

echo "Removing subfolders"

rmdir temp_zip/../ToolRichelBilderbeekGallery
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppCodeToHtml
rmdir temp_zip/Classes/CppProFile
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtRichelBilderbeekGalleryDialog
rmdir temp_zip/Classes/CppRichelBilderbeekProgram
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtRichelBilderbeekGalleryDialog
rmdir temp_zip/Website

echo "Removing main folders"

rmdir temp_zip/..
rmdir temp_zip/Classes
rmdir temp_zip/Website

echo "Removing temporary folder"

rm temp_zip/*.*
rmdir temp_zip

echo "Done"

# CreateQtProjectZipFile, version 1.0
# Copyright (C) 2012 Richel Bilderbeek
# Programmed on the 25th February 2012
# by Richel Bilderbeek
# 
# CreateQtProjectZipFile can be downloaded from http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
# Licenced under GPL 3.0
