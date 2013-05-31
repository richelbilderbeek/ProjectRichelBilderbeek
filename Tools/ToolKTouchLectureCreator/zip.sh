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

mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Tools/ToolKTouchLectureCreator

echo "Copying files"

cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Tools/ToolKTouchLectureCreator/Licence.txt temp_zip/Tools/ToolKTouchLectureCreator/Licence.txt
cp ../../Tools/ToolKTouchLectureCreator/ToolKTouchLectureCreator.pro temp_zip/Tools/ToolKTouchLectureCreator/ToolKTouchLectureCreator.pro
cp ../../Tools/ToolKTouchLectureCreator/ktouchlecture.cpp temp_zip/Tools/ToolKTouchLectureCreator/ktouchlecture.cpp
cp ../../Tools/ToolKTouchLectureCreator/ktouchlecture.h temp_zip/Tools/ToolKTouchLectureCreator/ktouchlecture.h
cp ../../Tools/ToolKTouchLectureCreator/ktouchlevel.cpp temp_zip/Tools/ToolKTouchLectureCreator/ktouchlevel.cpp
cp ../../Tools/ToolKTouchLectureCreator/ktouchlevel.h temp_zip/Tools/ToolKTouchLectureCreator/ktouchlevel.h
cp ../../Tools/ToolKTouchLectureCreator/ktouchlevels.cpp temp_zip/Tools/ToolKTouchLectureCreator/ktouchlevels.cpp
cp ../../Tools/ToolKTouchLectureCreator/ktouchlevels.h temp_zip/Tools/ToolKTouchLectureCreator/ktouchlevels.h
cp ../../Tools/ToolKTouchLectureCreator/main.cpp temp_zip/Tools/ToolKTouchLectureCreator/main.cpp
cp ../../Tools/ToolKTouchLectureCreator/zip.sh temp_zip/Tools/ToolKTouchLectureCreator/zip.sh

FILENAME="ToolKTouchLectureCreatorSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Tools/ToolKTouchLectureCreator/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Tools/ToolKTouchLectureCreator

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
