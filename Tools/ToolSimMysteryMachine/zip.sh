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
mkdir temp_zip/Classes/CppDial
mkdir temp_zip/Classes/CppDialWidget
mkdir temp_zip/Classes/CppLed
mkdir temp_zip/Classes/CppLedWidget
mkdir temp_zip/Classes/CppMysteryMachine
mkdir temp_zip/Classes/CppMysteryMachineWidget
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtDialWidget
mkdir temp_zip/Classes/CppQtLedDisplayWidget
mkdir temp_zip/Classes/CppQtLedWidget
mkdir temp_zip/Classes/CppQtMysteryMachineWidget
mkdir temp_zip/Classes/CppQtToggleButtonWidget
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppToggleButton
mkdir temp_zip/Classes/CppToggleButtonWidget
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtDialWidget
mkdir temp_zip/Classes/CppWtLedWidget
mkdir temp_zip/Classes/CppWtMysteryMachineWidget
mkdir temp_zip/Classes/CppWtToggleButtonWidget
mkdir temp_zip/Tools/ToolSimMysteryMachine

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppDial/dial.cpp temp_zip/Classes/CppDial/dial.cpp
cp ../../Classes/CppDial/dial.h temp_zip/Classes/CppDial/dial.h
cp ../../Classes/CppDialWidget/dialwidget.cpp temp_zip/Classes/CppDialWidget/dialwidget.cpp
cp ../../Classes/CppDialWidget/dialwidget.h temp_zip/Classes/CppDialWidget/dialwidget.h
cp ../../Classes/CppLed/led.cpp temp_zip/Classes/CppLed/led.cpp
cp ../../Classes/CppLed/led.h temp_zip/Classes/CppLed/led.h
cp ../../Classes/CppLedWidget/ledwidget.cpp temp_zip/Classes/CppLedWidget/ledwidget.cpp
cp ../../Classes/CppLedWidget/ledwidget.h temp_zip/Classes/CppLedWidget/ledwidget.h
cp ../../Classes/CppMysteryMachine/mysterymachine.cpp temp_zip/Classes/CppMysteryMachine/mysterymachine.cpp
cp ../../Classes/CppMysteryMachine/mysterymachine.h temp_zip/Classes/CppMysteryMachine/mysterymachine.h
cp ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp temp_zip/Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp
cp ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h temp_zip/Classes/CppMysteryMachineWidget/mysterymachinewidget.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtDialWidget/qtdialwidget.cpp temp_zip/Classes/CppQtDialWidget/qtdialwidget.cpp
cp ../../Classes/CppQtDialWidget/qtdialwidget.h temp_zip/Classes/CppQtDialWidget/qtdialwidget.h
cp ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.cpp temp_zip/Classes/CppQtLedDisplayWidget/qtleddisplaywidget.cpp
cp ../../Classes/CppQtLedDisplayWidget/qtleddisplaywidget.h temp_zip/Classes/CppQtLedDisplayWidget/qtleddisplaywidget.h
cp ../../Classes/CppQtLedWidget/qtledwidget.cpp temp_zip/Classes/CppQtLedWidget/qtledwidget.cpp
cp ../../Classes/CppQtLedWidget/qtledwidget.h temp_zip/Classes/CppQtLedWidget/qtledwidget.h
cp ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.cpp temp_zip/Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.cpp
cp ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.h temp_zip/Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.h
cp ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp temp_zip/Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp
cp ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h temp_zip/Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h
cp ../../Classes/CppRectangle/rectangle.cpp temp_zip/Classes/CppRectangle/rectangle.cpp
cp ../../Classes/CppRectangle/rectangle.h temp_zip/Classes/CppRectangle/rectangle.h
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
cp ../../Classes/CppWtLedWidget/wtledwidget.cpp temp_zip/Classes/CppWtLedWidget/wtledwidget.cpp
cp ../../Classes/CppWtLedWidget/wtledwidget.h temp_zip/Classes/CppWtLedWidget/wtledwidget.h
cp ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.cpp temp_zip/Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.cpp
cp ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h temp_zip/Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h
cp ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp temp_zip/Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp
cp ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h temp_zip/Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h
cp ../../Tools/ToolSimMysteryMachine/R.png temp_zip/Tools/ToolSimMysteryMachine/R.png
cp ../../Tools/ToolSimMysteryMachine/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolSimMysteryMachine/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.dia~ temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.dia~
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.png temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.png
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.qrc temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.qrc
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia~ temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia~
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.png temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.png
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineDesktop.pro temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineDesktop.pro
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachinePrototype.png temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachinePrototype.png
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWebsite.pro temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWebsite.pro
cp ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWelcome.png temp_zip/Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWelcome.png
cp ../../Tools/ToolSimMysteryMachine/crosscompiletowindows.sh temp_zip/Tools/ToolSimMysteryMachine/crosscompiletowindows.sh
cp ../../Tools/ToolSimMysteryMachine/qtmain.cpp temp_zip/Tools/ToolSimMysteryMachine/qtmain.cpp
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.cpp temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.cpp
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.h temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.h
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.ui temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.ui
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.cpp temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.cpp
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.h temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.h
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.ui temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.ui
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.cpp temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.cpp
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.h temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.h
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.ui temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.ui
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.cpp temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.cpp
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.h temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.h
cp ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.ui temp_zip/Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.ui
cp ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp temp_zip/Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp
cp ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h temp_zip/Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h
cp ../../Tools/ToolSimMysteryMachine/wt.css temp_zip/Tools/ToolSimMysteryMachine/wt.css
cp ../../Tools/ToolSimMysteryMachine/wtmain.cpp temp_zip/Tools/ToolSimMysteryMachine/wtmain.cpp
cp ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.cpp temp_zip/Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.cpp
cp ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.h temp_zip/Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.h
cp ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.cpp temp_zip/Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.cpp
cp ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.h temp_zip/Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.h
cp ../../Tools/ToolSimMysteryMachine/zip.sh temp_zip/Tools/ToolSimMysteryMachine/zip.sh

FILENAME="ToolSimMysteryMachineSource"
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
rm temp_zip/Classes/CppDial/*.*
rm temp_zip/Classes/CppDialWidget/*.*
rm temp_zip/Classes/CppLed/*.*
rm temp_zip/Classes/CppLedWidget/*.*
rm temp_zip/Classes/CppMysteryMachine/*.*
rm temp_zip/Classes/CppMysteryMachineWidget/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtDialWidget/*.*
rm temp_zip/Classes/CppQtLedDisplayWidget/*.*
rm temp_zip/Classes/CppQtLedWidget/*.*
rm temp_zip/Classes/CppQtMysteryMachineWidget/*.*
rm temp_zip/Classes/CppQtToggleButtonWidget/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppToggleButton/*.*
rm temp_zip/Classes/CppToggleButtonWidget/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtDialWidget/*.*
rm temp_zip/Classes/CppWtLedWidget/*.*
rm temp_zip/Classes/CppWtMysteryMachineWidget/*.*
rm temp_zip/Classes/CppWtToggleButtonWidget/*.*
rm temp_zip/Tools/ToolSimMysteryMachine/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppDial
rmdir temp_zip/Classes/CppDialWidget
rmdir temp_zip/Classes/CppLed
rmdir temp_zip/Classes/CppLedWidget
rmdir temp_zip/Classes/CppMysteryMachine
rmdir temp_zip/Classes/CppMysteryMachineWidget
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtDialWidget
rmdir temp_zip/Classes/CppQtLedDisplayWidget
rmdir temp_zip/Classes/CppQtLedWidget
rmdir temp_zip/Classes/CppQtMysteryMachineWidget
rmdir temp_zip/Classes/CppQtToggleButtonWidget
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppToggleButton
rmdir temp_zip/Classes/CppToggleButtonWidget
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtDialWidget
rmdir temp_zip/Classes/CppWtLedWidget
rmdir temp_zip/Classes/CppWtMysteryMachineWidget
rmdir temp_zip/Classes/CppWtToggleButtonWidget
rmdir temp_zip/Tools/ToolSimMysteryMachine

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
