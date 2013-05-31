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
mkdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
mkdir temp_zip/Classes/CppQtQuadBezierArrowItem
mkdir temp_zip/Classes/CppQtRoundedRectItem
mkdir temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView

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
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h
cp ../../Classes/CppQtQuadBezierArrowItem/Licence.txt temp_zip/Classes/CppQtQuadBezierArrowItem/Licence.txt
cp ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp temp_zip/Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp
cp ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h temp_zip/Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h
cp ../../Classes/CppQtRoundedRectItem/Licence.txt temp_zip/Classes/CppQtRoundedRectItem/Licence.txt
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h temp_zip/Classes/CppQtRoundedRectItem/qtroundedrectitem.h
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/Licence.txt temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/Licence.txt
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/PicR14x14_opaque.png temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/PicR14x14_opaque.png
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/ToolTestKeyboardFriendlyGraphicsView.pro temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/ToolTestKeyboardFriendlyGraphicsView.pro
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/ToolTestKeyboardFriendlyGraphicsView.qrc temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/ToolTestKeyboardFriendlyGraphicsView.qrc
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/crosscompiletowindows.sh temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/crosscompiletowindows.sh
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qtmain.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qtmain.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.h temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.h
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.ui temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewmenudialog.ui
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewrectitem.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewrectitem.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewrectitem.h temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewrectitem.h
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewtextitem.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewtextitem.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewtextitem.h temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewtextitem.h
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewwidget.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewwidget.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewwidget.h temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/qttestkeyboardfriendlygraphicsviewwidget.h
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/testkeyboardfriendlygraphicsviewmenudialog.cpp temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/testkeyboardfriendlygraphicsviewmenudialog.cpp
cp ../../Tools/ToolTestKeyboardFriendlyGraphicsView/testkeyboardfriendlygraphicsviewmenudialog.h temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/testkeyboardfriendlygraphicsviewmenudialog.h

FILENAME="ToolTestKeyboardFriendlyGraphicsViewSource"
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
rm temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView/*.*
rm temp_zip/Classes/CppQtQuadBezierArrowItem/*.*
rm temp_zip/Classes/CppQtRoundedRectItem/*.*
rm temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtKeyboardFriendlyGraphicsView
rmdir temp_zip/Classes/CppQtQuadBezierArrowItem
rmdir temp_zip/Classes/CppQtRoundedRectItem
rmdir temp_zip/Tools/ToolTestKeyboardFriendlyGraphicsView

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
