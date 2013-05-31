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
mkdir temp_zip/Classes/CppDial
mkdir temp_zip/Classes/CppDialWidget
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtDialWidget
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppQtRubiksClockWidget
mkdir temp_zip/Classes/CppQtToggleButtonWidget
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppRubiksClock
mkdir temp_zip/Classes/CppRubiksClockWidget
mkdir temp_zip/Classes/CppToggleButton
mkdir temp_zip/Classes/CppToggleButtonWidget
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtDialWidget
mkdir temp_zip/Classes/CppWtRubiksClockWidget
mkdir temp_zip/Classes/CppWtToggleButtonWidget
mkdir temp_zip/Games/GameRubiksClock

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppDial/dial.cpp temp_zip/Classes/CppDial/dial.cpp
cp ../../Classes/CppDial/dial.h temp_zip/Classes/CppDial/dial.h
cp ../../Classes/CppDialWidget/dialwidget.cpp temp_zip/Classes/CppDialWidget/dialwidget.cpp
cp ../../Classes/CppDialWidget/dialwidget.h temp_zip/Classes/CppDialWidget/dialwidget.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtDialWidget/Licence.txt temp_zip/Classes/CppQtDialWidget/Licence.txt
cp ../../Classes/CppQtDialWidget/qtdialwidget.cpp temp_zip/Classes/CppQtDialWidget/qtdialwidget.cpp
cp ../../Classes/CppQtDialWidget/qtdialwidget.h temp_zip/Classes/CppQtDialWidget/qtdialwidget.h
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.cpp temp_zip/Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.cpp
cp ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.h temp_zip/Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.h
cp ../../Classes/CppQtToggleButtonWidget/Licence.txt temp_zip/Classes/CppQtToggleButtonWidget/Licence.txt
cp ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp temp_zip/Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp
cp ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h temp_zip/Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h
cp ../../Classes/CppRectangle/rectangle.cpp temp_zip/Classes/CppRectangle/rectangle.cpp
cp ../../Classes/CppRectangle/rectangle.h temp_zip/Classes/CppRectangle/rectangle.h
cp ../../Classes/CppRubiksClock/rubiksclock.cpp temp_zip/Classes/CppRubiksClock/rubiksclock.cpp
cp ../../Classes/CppRubiksClock/rubiksclock.h temp_zip/Classes/CppRubiksClock/rubiksclock.h
cp ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp temp_zip/Classes/CppRubiksClockWidget/rubiksclockdial.cpp
cp ../../Classes/CppRubiksClockWidget/rubiksclockdial.h temp_zip/Classes/CppRubiksClockWidget/rubiksclockdial.h
cp ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp temp_zip/Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp
cp ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h temp_zip/Classes/CppRubiksClockWidget/rubiksclockdialwidget.h
cp ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp temp_zip/Classes/CppRubiksClockWidget/rubiksclockwidget.cpp
cp ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h temp_zip/Classes/CppRubiksClockWidget/rubiksclockwidget.h
cp ../../Classes/CppToggleButton/togglebutton.cpp temp_zip/Classes/CppToggleButton/togglebutton.cpp
cp ../../Classes/CppToggleButton/togglebutton.h temp_zip/Classes/CppToggleButton/togglebutton.h
cp ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp temp_zip/Classes/CppToggleButtonWidget/togglebuttonwidget.cpp
cp ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h temp_zip/Classes/CppToggleButtonWidget/togglebuttonwidget.h
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Classes/CppWidget/widget.cpp temp_zip/Classes/CppWidget/widget.cpp
cp ../../Classes/CppWidget/widget.h temp_zip/Classes/CppWidget/widget.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Classes/CppWtDialWidget/wtdialwidget.cpp temp_zip/Classes/CppWtDialWidget/wtdialwidget.cpp
cp ../../Classes/CppWtDialWidget/wtdialwidget.h temp_zip/Classes/CppWtDialWidget/wtdialwidget.h
cp ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.cpp temp_zip/Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.cpp
cp ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.h temp_zip/Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.h
cp ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp temp_zip/Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp
cp ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h temp_zip/Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h
cp ../../Games/GameRubiksClock/GameRubiksClock.png temp_zip/Games/GameRubiksClock/GameRubiksClock.png
cp ../../Games/GameRubiksClock/GameRubiksClock.qrc temp_zip/Games/GameRubiksClock/GameRubiksClock.qrc
cp ../../Games/GameRubiksClock/GameRubiksClockDesktop.pro temp_zip/Games/GameRubiksClock/GameRubiksClockDesktop.pro
cp ../../Games/GameRubiksClock/GameRubiksClockIcon14x14.png temp_zip/Games/GameRubiksClock/GameRubiksClockIcon14x14.png
cp ../../Games/GameRubiksClock/GameRubiksClockTransparent.png temp_zip/Games/GameRubiksClock/GameRubiksClockTransparent.png
cp ../../Games/GameRubiksClock/GameRubiksClockWebsite.pro temp_zip/Games/GameRubiksClock/GameRubiksClockWebsite.pro
cp ../../Games/GameRubiksClock/GameRubiksClockWelcome.png temp_zip/Games/GameRubiksClock/GameRubiksClockWelcome.png
cp ../../Games/GameRubiksClock/GameRubiksClockWelcomeNoLegend.png temp_zip/Games/GameRubiksClock/GameRubiksClockWelcomeNoLegend.png
cp ../../Games/GameRubiksClock/GameRubiksClockWelcome_2_1.png temp_zip/Games/GameRubiksClock/GameRubiksClockWelcome_2_1.png
cp ../../Games/GameRubiksClock/Licence.txt temp_zip/Games/GameRubiksClock/Licence.txt
cp ../../Games/GameRubiksClock/crosscompiletowindows.sh temp_zip/Games/GameRubiksClock/crosscompiletowindows.sh
cp ../../Games/GameRubiksClock/qtmain.cpp temp_zip/Games/GameRubiksClock/qtmain.cpp
cp ../../Games/GameRubiksClock/qtrubiksclockmaindialog.cpp temp_zip/Games/GameRubiksClock/qtrubiksclockmaindialog.cpp
cp ../../Games/GameRubiksClock/qtrubiksclockmaindialog.h temp_zip/Games/GameRubiksClock/qtrubiksclockmaindialog.h
cp ../../Games/GameRubiksClock/qtrubiksclockmaindialog.ui temp_zip/Games/GameRubiksClock/qtrubiksclockmaindialog.ui
cp ../../Games/GameRubiksClock/qtrubiksclockmenudialog.cpp temp_zip/Games/GameRubiksClock/qtrubiksclockmenudialog.cpp
cp ../../Games/GameRubiksClock/qtrubiksclockmenudialog.h temp_zip/Games/GameRubiksClock/qtrubiksclockmenudialog.h
cp ../../Games/GameRubiksClock/qtrubiksclockmenudialog.ui temp_zip/Games/GameRubiksClock/qtrubiksclockmenudialog.ui
cp ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp temp_zip/Games/GameRubiksClock/rubiksclockmenudialog.cpp
cp ../../Games/GameRubiksClock/rubiksclockmenudialog.h temp_zip/Games/GameRubiksClock/rubiksclockmenudialog.h
cp ../../Games/GameRubiksClock/trace_out.txt temp_zip/Games/GameRubiksClock/trace_out.txt
cp ../../Games/GameRubiksClock/wtmain.cpp temp_zip/Games/GameRubiksClock/wtmain.cpp
cp ../../Games/GameRubiksClock/wtrubiksclockmaindialog.cpp temp_zip/Games/GameRubiksClock/wtrubiksclockmaindialog.cpp
cp ../../Games/GameRubiksClock/wtrubiksclockmaindialog.h temp_zip/Games/GameRubiksClock/wtrubiksclockmaindialog.h
cp ../../Games/GameRubiksClock/wtrubiksclockmenudialog.cpp temp_zip/Games/GameRubiksClock/wtrubiksclockmenudialog.cpp
cp ../../Games/GameRubiksClock/wtrubiksclockmenudialog.h temp_zip/Games/GameRubiksClock/wtrubiksclockmenudialog.h
cp ../../Games/GameRubiksClock/zip.sh temp_zip/Games/GameRubiksClock/zip.sh

FILENAME="GameRubiksClockSource"
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
rm temp_zip/Classes/CppDial/*.*
rm temp_zip/Classes/CppDialWidget/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtDialWidget/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppQtRubiksClockWidget/*.*
rm temp_zip/Classes/CppQtToggleButtonWidget/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppRubiksClock/*.*
rm temp_zip/Classes/CppRubiksClockWidget/*.*
rm temp_zip/Classes/CppToggleButton/*.*
rm temp_zip/Classes/CppToggleButtonWidget/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtDialWidget/*.*
rm temp_zip/Classes/CppWtRubiksClockWidget/*.*
rm temp_zip/Classes/CppWtToggleButtonWidget/*.*
rm temp_zip/Games/GameRubiksClock/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppDial
rmdir temp_zip/Classes/CppDialWidget
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtDialWidget
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtRubiksClockWidget
rmdir temp_zip/Classes/CppQtToggleButtonWidget
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppRubiksClock
rmdir temp_zip/Classes/CppRubiksClockWidget
rmdir temp_zip/Classes/CppToggleButton
rmdir temp_zip/Classes/CppToggleButtonWidget
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtDialWidget
rmdir temp_zip/Classes/CppWtRubiksClockWidget
rmdir temp_zip/Classes/CppWtToggleButtonWidget
rmdir temp_zip/Games/GameRubiksClock

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Games

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
