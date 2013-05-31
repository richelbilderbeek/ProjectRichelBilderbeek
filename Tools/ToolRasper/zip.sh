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
mkdir temp_zip/Classes/CppRaspberryPi
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Tools/ToolRasper

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppRaspberryPi/raspberrypifwd.h temp_zip/Classes/CppRaspberryPi/raspberrypifwd.h
cp ../../Classes/CppRaspberryPi/raspberrypigpiopin.cpp temp_zip/Classes/CppRaspberryPi/raspberrypigpiopin.cpp
cp ../../Classes/CppRaspberryPi/raspberrypigpiopin.h temp_zip/Classes/CppRaspberryPi/raspberrypigpiopin.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Tools/ToolRasper/Licence.txt temp_zip/Tools/ToolRasper/Licence.txt
cp ../../Tools/ToolRasper/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolRasper/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolRasper/ToolRasper.pro temp_zip/Tools/ToolRasper/ToolRasper.pro
cp ../../Tools/ToolRasper/ToolRasper.qrc temp_zip/Tools/ToolRasper/ToolRasper.qrc
cp ../../Tools/ToolRasper/ToolRasperGpioLayout.png temp_zip/Tools/ToolRasper/ToolRasperGpioLayout.png
cp ../../Tools/ToolRasper/ToolRasperRaspberryPiDiagonally.jpg temp_zip/Tools/ToolRasper/ToolRasperRaspberryPiDiagonally.jpg
cp ../../Tools/ToolRasper/ToolRasperRaspberryPiTop.jpg temp_zip/Tools/ToolRasper/ToolRasperRaspberryPiTop.jpg
cp ../../Tools/ToolRasper/rasper_start_and_auto_update.sh temp_zip/Tools/ToolRasper/rasper_start_and_auto_update.sh
cp ../../Tools/ToolRasper/raspermenudialog.cpp temp_zip/Tools/ToolRasper/raspermenudialog.cpp
cp ../../Tools/ToolRasper/raspermenudialog.h temp_zip/Tools/ToolRasper/raspermenudialog.h
cp ../../Tools/ToolRasper/wtmain.cpp temp_zip/Tools/ToolRasper/wtmain.cpp
cp ../../Tools/ToolRasper/wtraspermaindialog.cpp temp_zip/Tools/ToolRasper/wtraspermaindialog.cpp
cp ../../Tools/ToolRasper/wtraspermaindialog.h temp_zip/Tools/ToolRasper/wtraspermaindialog.h
cp ../../Tools/ToolRasper/wtraspermenudialog.cpp temp_zip/Tools/ToolRasper/wtraspermenudialog.cpp
cp ../../Tools/ToolRasper/wtraspermenudialog.h temp_zip/Tools/ToolRasper/wtraspermenudialog.h
cp ../../Tools/ToolRasper/wtrasperresources.cpp temp_zip/Tools/ToolRasper/wtrasperresources.cpp
cp ../../Tools/ToolRasper/wtrasperresources.h temp_zip/Tools/ToolRasper/wtrasperresources.h
cp ../../Tools/ToolRasper/zip.sh temp_zip/Tools/ToolRasper/zip.sh

FILENAME="ToolRasperSource"
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
rm temp_zip/Classes/CppRaspberryPi/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Tools/ToolRasper/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppRaspberryPi
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Tools/ToolRasper

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
