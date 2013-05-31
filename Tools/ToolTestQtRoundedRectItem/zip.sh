#!/bin/sh
# Created from file '../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppQtRoundedRectItem
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Tools/ToolTestQtRoundedRectItem
mkdir Projects/Classes/CppQtKeyboardFriendlyGraphicsView

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/Licence.txt Projects/Classes/CppAbout/Licence.txt
cp ../../Classes/CppTrace/Licence.txt Projects/Classes/CppTrace/Licence.txt
cp ../../Classes/CppQtAboutDialog/Licence.txt Projects/Classes/CppQtAboutDialog/Licence.txt
cp ../../Tools/ToolTestQtRoundedRectItem/R.png Projects/Tools/ToolTestQtRoundedRectItem/R.png
cp ../../Tools/ToolTestQtRoundedRectItem/zip.sh Projects/Tools/ToolTestQtRoundedRectItem/zip.sh
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtRoundedRectItem/Licence.txt Projects/Classes/CppQtRoundedRectItem/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Tools/ToolTestQtRoundedRectItem/qtmain.cpp Projects/Tools/ToolTestQtRoundedRectItem/qtmain.cpp
cp ../../Tools/ToolTestQtRoundedRectItem/Licence.txt Projects/Tools/ToolTestQtRoundedRectItem/Licence.txt
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h Projects/Classes/CppQtRoundedRectItem/qtroundedrectitem.h
cp ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp Projects/Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt Projects/Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.pro Projects/Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.pro
cp ../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.qrc Projects/Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.qrc
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.h Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.h
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.cpp Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.cpp
cp ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.h Projects/Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.h Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.h
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.h Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.h
cp ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.cpp Projects/Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.cpp
cp ../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItemWelcome.png Projects/Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItemWelcome.png
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.ui Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.ui
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.ui Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.ui
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.cpp Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.cpp
cp ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.cpp Projects/Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.cpp
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h Projects/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h
cp ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp Projects/Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp

FILENAME="../../Tools/ToolTestQtRoundedRectItemSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Classes/CppQtKeyboardFriendlyGraphicsView/*.*
rm Projects/Tools/ToolTestQtRoundedRectItem/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Classes/CppQtRoundedRectItem/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Classes/CppQtKeyboardFriendlyGraphicsView
rmdir Projects/Tools/ToolTestQtRoundedRectItem
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Classes/CppQtRoundedRectItem
rmdir Projects/Classes/CppQtAboutDialog
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

