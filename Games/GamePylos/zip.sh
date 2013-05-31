#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Games

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppPylos
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtPylos
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Games/GamePylos

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
cp ../../Games/GamePylos/GamePylos.pro temp_zip/Games/GamePylos/GamePylos.pro
cp ../../Games/GamePylos/GamePylos.qrc temp_zip/Games/GamePylos/GamePylos.qrc
cp ../../Games/GamePylos/Licence.txt temp_zip/Games/GamePylos/Licence.txt
cp ../../Games/GamePylos/PylosGoal1.png temp_zip/Games/GamePylos/PylosGoal1.png
cp ../../Games/GamePylos/PylosGoal2.png temp_zip/Games/GamePylos/PylosGoal2.png
cp ../../Games/GamePylos/PylosLine.png temp_zip/Games/GamePylos/PylosLine.png
cp ../../Games/GamePylos/PylosMove.png temp_zip/Games/GamePylos/PylosMove.png
cp ../../Games/GamePylos/PylosPlace.png temp_zip/Games/GamePylos/PylosPlace.png
cp ../../Games/GamePylos/PylosRemove1.png temp_zip/Games/GamePylos/PylosRemove1.png
cp ../../Games/GamePylos/PylosRemove2.png temp_zip/Games/GamePylos/PylosRemove2.png
cp ../../Games/GamePylos/PylosSquare.png temp_zip/Games/GamePylos/PylosSquare.png
cp ../../Games/GamePylos/R.png temp_zip/Games/GamePylos/R.png
cp ../../Games/GamePylos/pylosmenudialog.cpp temp_zip/Games/GamePylos/pylosmenudialog.cpp
cp ../../Games/GamePylos/pylosmenudialog.h temp_zip/Games/GamePylos/pylosmenudialog.h
cp ../../Games/GamePylos/qtmain.cpp temp_zip/Games/GamePylos/qtmain.cpp
cp ../../Games/GamePylos/qtpylosinstructionsdialog.cpp temp_zip/Games/GamePylos/qtpylosinstructionsdialog.cpp
cp ../../Games/GamePylos/qtpylosinstructionsdialog.h temp_zip/Games/GamePylos/qtpylosinstructionsdialog.h
cp ../../Games/GamePylos/qtpylosinstructionsdialog.ui temp_zip/Games/GamePylos/qtpylosinstructionsdialog.ui
cp ../../Games/GamePylos/qtpylosmaindialog.cpp temp_zip/Games/GamePylos/qtpylosmaindialog.cpp
cp ../../Games/GamePylos/qtpylosmaindialog.h temp_zip/Games/GamePylos/qtpylosmaindialog.h
cp ../../Games/GamePylos/qtpylosmaindialog.ui temp_zip/Games/GamePylos/qtpylosmaindialog.ui
cp ../../Games/GamePylos/qtpylosmenudialog.cpp temp_zip/Games/GamePylos/qtpylosmenudialog.cpp
cp ../../Games/GamePylos/qtpylosmenudialog.h temp_zip/Games/GamePylos/qtpylosmenudialog.h
cp ../../Games/GamePylos/qtpylosmenudialog.ui temp_zip/Games/GamePylos/qtpylosmenudialog.ui
cp ../../Games/GamePylos/qtpyloswondialog.cpp temp_zip/Games/GamePylos/qtpyloswondialog.cpp
cp ../../Games/GamePylos/qtpyloswondialog.h temp_zip/Games/GamePylos/qtpyloswondialog.h
cp ../../Games/GamePylos/qtpyloswondialog.ui temp_zip/Games/GamePylos/qtpyloswondialog.ui
cp ../../Games/GamePylos/sprite_hole.png temp_zip/Games/GamePylos/sprite_hole.png
cp ../../Games/GamePylos/sprite_player1.png temp_zip/Games/GamePylos/sprite_player1.png
cp ../../Games/GamePylos/sprite_player1_remove.png temp_zip/Games/GamePylos/sprite_player1_remove.png
cp ../../Games/GamePylos/sprite_player1_select.png temp_zip/Games/GamePylos/sprite_player1_select.png
cp ../../Games/GamePylos/sprite_player2.png temp_zip/Games/GamePylos/sprite_player2.png
cp ../../Games/GamePylos/sprite_player2_remove.png temp_zip/Games/GamePylos/sprite_player2_remove.png
cp ../../Games/GamePylos/sprite_player2_select.png temp_zip/Games/GamePylos/sprite_player2_select.png

FILENAME="GamePylosSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Games
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppPylos/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtPylos/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Games/GamePylos/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppPylos
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtPylos
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Games/GamePylos

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Games

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
