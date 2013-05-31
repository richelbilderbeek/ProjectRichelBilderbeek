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
mkdir temp_zip/Classes/CppPylos
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtPylos
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Tools/ToolTestPylos

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppPylos/Licence.txt temp_zip/Classes/CppPylos/Licence.txt
cp ../../Classes/CppPylos/pylosboard.cpp temp_zip/Classes/CppPylos/pylosboard.cpp
cp ../../Classes/CppPylos/pylosboard.h temp_zip/Classes/CppPylos/pylosboard.h
cp ../../Classes/CppPylos/pyloscoordinat.cpp temp_zip/Classes/CppPylos/pyloscoordinat.cpp
cp ../../Classes/CppPylos/pyloscoordinat.h temp_zip/Classes/CppPylos/pyloscoordinat.h
cp ../../Classes/CppPylos/pyloscurrentmovestate.cpp temp_zip/Classes/CppPylos/pyloscurrentmovestate.cpp
cp ../../Classes/CppPylos/pyloscurrentmovestate.h temp_zip/Classes/CppPylos/pyloscurrentmovestate.h
cp ../../Classes/CppPylos/pylosfwd.h temp_zip/Classes/CppPylos/pylosfwd.h
cp ../../Classes/CppPylos/pylosgame.cpp temp_zip/Classes/CppPylos/pylosgame.cpp
cp ../../Classes/CppPylos/pylosgame.h temp_zip/Classes/CppPylos/pylosgame.h
cp ../../Classes/CppPylos/pylosmove.cpp temp_zip/Classes/CppPylos/pylosmove.cpp
cp ../../Classes/CppPylos/pylosmove.h temp_zip/Classes/CppPylos/pylosmove.h
cp ../../Classes/CppPylos/pylosmustremovestate.cpp temp_zip/Classes/CppPylos/pylosmustremovestate.cpp
cp ../../Classes/CppPylos/pylosmustremovestate.h temp_zip/Classes/CppPylos/pylosmustremovestate.h
cp ../../Classes/CppPylos/pylosplayer.cpp temp_zip/Classes/CppPylos/pylosplayer.cpp
cp ../../Classes/CppPylos/pylosplayer.h temp_zip/Classes/CppPylos/pylosplayer.h
cp ../../Classes/CppPylos/pylospositionstate.cpp temp_zip/Classes/CppPylos/pylospositionstate.cpp
cp ../../Classes/CppPylos/pylospositionstate.h temp_zip/Classes/CppPylos/pylospositionstate.h
cp ../../Classes/CppPylos/pyloswinner.cpp temp_zip/Classes/CppPylos/pyloswinner.cpp
cp ../../Classes/CppPylos/pyloswinner.h temp_zip/Classes/CppPylos/pyloswinner.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtPylos/Licence.txt temp_zip/Classes/CppQtPylos/Licence.txt
cp ../../Classes/CppQtPylos/qtpylosboardwidget.cpp temp_zip/Classes/CppQtPylos/qtpylosboardwidget.cpp
cp ../../Classes/CppQtPylos/qtpylosboardwidget.h temp_zip/Classes/CppQtPylos/qtpylosboardwidget.h
cp ../../Classes/CppQtPylos/qtpylosgamewidget.cpp temp_zip/Classes/CppQtPylos/qtpylosgamewidget.cpp
cp ../../Classes/CppQtPylos/qtpylosgamewidget.h temp_zip/Classes/CppQtPylos/qtpylosgamewidget.h
cp ../../Classes/CppQtPylos/qtpylossprites.cpp temp_zip/Classes/CppQtPylos/qtpylossprites.cpp
cp ../../Classes/CppQtPylos/qtpylossprites.h temp_zip/Classes/CppQtPylos/qtpylossprites.h
cp ../../Classes/CppQtPylos/qtpyloswidget.cpp temp_zip/Classes/CppQtPylos/qtpyloswidget.cpp
cp ../../Classes/CppQtPylos/qtpyloswidget.h temp_zip/Classes/CppQtPylos/qtpyloswidget.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Tools/ToolTestPylos/Licence.txt temp_zip/Tools/ToolTestPylos/Licence.txt
cp ../../Tools/ToolTestPylos/R.png temp_zip/Tools/ToolTestPylos/R.png
cp ../../Tools/ToolTestPylos/ToolTestPylos.pro temp_zip/Tools/ToolTestPylos/ToolTestPylos.pro
cp ../../Tools/ToolTestPylos/ToolTestPylos.qrc temp_zip/Tools/ToolTestPylos/ToolTestPylos.qrc
cp ../../Tools/ToolTestPylos/ToolTestPylosCanMove.png temp_zip/Tools/ToolTestPylos/ToolTestPylosCanMove.png
cp ../../Tools/ToolTestPylos/ToolTestPylosDoubleRemoveTest.png temp_zip/Tools/ToolTestPylos/ToolTestPylosDoubleRemoveTest.png
cp ../../Tools/ToolTestPylos/ToolTestPylosMoveMustRemove.png temp_zip/Tools/ToolTestPylos/ToolTestPylosMoveMustRemove.png
cp ../../Tools/ToolTestPylos/ToolTestPylosMustRemove.png temp_zip/Tools/ToolTestPylos/ToolTestPylosMustRemove.png
cp ../../Tools/ToolTestPylos/qtmain.cpp temp_zip/Tools/ToolTestPylos/qtmain.cpp
cp ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.cpp temp_zip/Tools/ToolTestPylos/qttestpylosgametestsdialog.cpp
cp ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.h temp_zip/Tools/ToolTestPylos/qttestpylosgametestsdialog.h
cp ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.ui temp_zip/Tools/ToolTestPylos/qttestpylosgametestsdialog.ui
cp ../../Tools/ToolTestPylos/qttestpylosmenudialog.cpp temp_zip/Tools/ToolTestPylos/qttestpylosmenudialog.cpp
cp ../../Tools/ToolTestPylos/qttestpylosmenudialog.h temp_zip/Tools/ToolTestPylos/qttestpylosmenudialog.h
cp ../../Tools/ToolTestPylos/qttestpylosmenudialog.ui temp_zip/Tools/ToolTestPylos/qttestpylosmenudialog.ui
cp ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.cpp temp_zip/Tools/ToolTestPylos/qttestpylosrandomplaydialog.cpp
cp ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.h temp_zip/Tools/ToolTestPylos/qttestpylosrandomplaydialog.h
cp ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.ui temp_zip/Tools/ToolTestPylos/qttestpylosrandomplaydialog.ui
cp ../../Tools/ToolTestPylos/qttestpylostestboarddialog.cpp temp_zip/Tools/ToolTestPylos/qttestpylostestboarddialog.cpp
cp ../../Tools/ToolTestPylos/qttestpylostestboarddialog.h temp_zip/Tools/ToolTestPylos/qttestpylostestboarddialog.h
cp ../../Tools/ToolTestPylos/qttestpylostestboarddialog.ui temp_zip/Tools/ToolTestPylos/qttestpylostestboarddialog.ui
cp ../../Tools/ToolTestPylos/qttestpylostestgamedialog.cpp temp_zip/Tools/ToolTestPylos/qttestpylostestgamedialog.cpp
cp ../../Tools/ToolTestPylos/qttestpylostestgamedialog.h temp_zip/Tools/ToolTestPylos/qttestpylostestgamedialog.h
cp ../../Tools/ToolTestPylos/qttestpylostestgamedialog.ui temp_zip/Tools/ToolTestPylos/qttestpylostestgamedialog.ui
cp ../../Tools/ToolTestPylos/testpylosmenudialog.cpp temp_zip/Tools/ToolTestPylos/testpylosmenudialog.cpp
cp ../../Tools/ToolTestPylos/testpylosmenudialog.h temp_zip/Tools/ToolTestPylos/testpylosmenudialog.h

FILENAME="ToolTestPylosSource"
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
rm temp_zip/Classes/CppPylos/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtPylos/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Tools/ToolTestPylos/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppPylos
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtPylos
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Tools/ToolTestPylos

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Tools

echo "Removing temporary folder"

rm temp_zip/*.*
rmdir temp_zip

echo "Done"

# CreateQtProjectZipFile, version 1.2
# Copyright (C) 2012 Richel Bilderbeek
# Programmed on the 25th February 2012
# by Richel Bilderbeek
# 
# CreateQtProjectZipFile can be downloaded from http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
# Licenced under GPL 3.0
