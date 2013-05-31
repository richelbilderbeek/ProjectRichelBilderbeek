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
mkdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
mkdir temp_zip/Classes/CppQtRoundedRectItem
mkdir temp_zip/Classes/CppQtRoundedTextRectItem
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Tools/ToolTestQtRoundedTextRectItem

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h
cp ../../Classes/CppQtRoundedRectItem/Licence.txt temp_zip/Classes/CppQtRoundedRectItem/Licence.txt
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.h
cp ../../Classes/CppQtRoundedTextRectItem/Licence.txt temp_zip/Classes/CppQtRoundedTextRectItem/Licence.txt
cp ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp temp_zip/Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp
cp ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h temp_zip/Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/Licence.txt temp_zip/Tools/ToolTestQtRoundedTextRectItem/Licence.txt
cp ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.pro temp_zip/Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.pro
cp ../../Tools/ToolTestQtRoundedTextRectItem/crosscompiletowindows.sh temp_zip/Tools/ToolTestQtRoundedTextRectItem/crosscompiletowindows.sh
cp ../../Tools/ToolTestQtRoundedTextRectItem/qtmain.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/qtmain.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp temp_zip/Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h temp_zip/Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedTextRectItem/zip.sh temp_zip/Tools/ToolTestQtRoundedTextRectItem/zip.sh

FILENAME="ToolTestQtRoundedTextRectItemSource"
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
rm temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/*.*
rm temp_zip/Classes/CppQtRoundedRectItem/*.*
rm temp_zip/Classes/CppQtRoundedTextRectItem/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Tools/ToolTestQtRoundedTextRectItem/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
rmdir temp_zip/Classes/CppQtRoundedRectItem
rmdir temp_zip/Classes/CppQtRoundedTextRectItem
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Tools/ToolTestQtRoundedTextRectItem

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
