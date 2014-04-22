#!/bin/sh
# Created from file '../../Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pri'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Classes/CppHelp
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppFileIo
mkdir Projects/Classes/CppQrcFile
mkdir Projects/Classes/CppMenuDialog
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppQtCreatorProFile
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Tools/ToolCreateQtProjectZipFile
mkdir Projects/Classes/CppRichelBilderbeekProgram
mkdir Projects/Tools/ToolCreateQtProjectZipFile/..
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../..
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Tools
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Libraries
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppHelp
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppAbout
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppTrace
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppFileIo
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQrcFile
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppMenuDialog
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtAboutDialog
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtCreatorProFile
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtHideAndShowDialog
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile
mkdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppRichelBilderbeekProgram

echo "Copying files"

cp ../../Classes/CppHelp/help.h Projects/Classes/CppHelp/help.h
cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppHelp/help.cpp Projects/Classes/CppHelp/help.cpp
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Classes/CppFileIo/fileio.h Projects/Classes/CppFileIo/fileio.h
cp ../../Classes/CppHelp/Licence.txt Projects/Classes/CppHelp/Licence.txt
cp ../../Classes/CppAbout/Licence.txt Projects/Classes/CppAbout/Licence.txt
cp ../../Classes/CppFileIo/fileio.cpp Projects/Classes/CppFileIo/fileio.cpp
cp ../../Classes/CppFileIo/filename.h Projects/Classes/CppFileIo/filename.h
cp ../../Classes/CppQrcFile/qrcfile.h Projects/Classes/CppQrcFile/qrcfile.h
cp ../../Classes/CppTrace/Licence.txt Projects/Classes/CppTrace/Licence.txt
cp ../../Classes/CppFileIo/Licence.txt Projects/Classes/CppFileIo/Licence.txt
cp ../../Classes/CppFileIo/filename.cpp Projects/Classes/CppFileIo/filename.cpp
cp ../../Classes/CppQrcFile/Licence.txt Projects/Classes/CppQrcFile/Licence.txt
cp ../../Classes/CppQrcFile/qrcfile.cpp Projects/Classes/CppQrcFile/qrcfile.cpp
cp ../../Classes/CppMenuDialog/Licence.txt Projects/Classes/CppMenuDialog/Licence.txt
cp ../../Classes/CppMenuDialog/menudialog.h Projects/Classes/CppMenuDialog/menudialog.h
cp ../../Classes/CppMenuDialog/menudialog.cpp Projects/Classes/CppMenuDialog/menudialog.cpp
cp ../../Classes/CppQtAboutDialog/Licence.txt Projects/Classes/CppQtAboutDialog/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/R.png Projects/Tools/ToolCreateQtProjectZipFile/R.png
cp ../../Classes/CppQtCreatorProFile/Licence.txt Projects/Classes/CppQtCreatorProFile/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/main.cpp Projects/Tools/ToolCreateQtProjectZipFile/main.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/qtmain.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtmain.cpp
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.h
cp ../../Classes/CppRichelBilderbeekProgram/Licence.txt Projects/Classes/CppRichelBilderbeekProgram/Licence.txt
cp ../../Tools/ToolCreateQtProjectZipFile/PicTo14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicTo14x14.png
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/PicZip14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicZip14x14.png
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/PicQtCreator14x14.png Projects/Tools/ToolCreateQtProjectZipFile/PicQtCreator14x14.png
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/../../Libraries/Boost.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Libraries/Boost.pri
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h
cp ../../Tools/ToolCreateQtProjectZipFile/../../ConsoleApplication.pri Projects/Tools/ToolCreateQtProjectZipFile/../../ConsoleApplication.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../DesktopApplication.pri Projects/Tools/ToolCreateQtProjectZipFile/../../DesktopApplication.pri
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFile.qrc Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFile.qrc
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppHelp/CppHelp.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppHelp/CppHelp.pri
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemaindialog.h Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemaindialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h
cp ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp Projects/Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppAbout/CppAbout.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppAbout/CppAbout.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppTrace/CppTrace.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppTrace/CppTrace.pri
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemaindialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemaindialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.h Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.h Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.h
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppFileIo/CppFileIo.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppFileIo/CppFileIo.pri
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pri Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pri
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pro Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pro
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pri Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pri
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileDesktop.pro
cp ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileWebsite.pri Projects/Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileWebsite.pri
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.ui Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.ui Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.ui
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.cpp Projects/Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.cpp
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppQrcFile/CppQrcFile.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQrcFile/CppQrcFile.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppMenuDialog/CppMenuDialog.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppMenuDialog/CppMenuDialog.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtAboutDialog/CppQtAboutDialog.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtCreatorProFile/CppQtCreatorProFile.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri
cp ../../Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pri Projects/Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFileConsole.pri

FILENAME="../../Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFileSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppRichelBilderbeekProgram/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtHideAndShowDialog/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtCreatorProFile/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtAboutDialog/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppMenuDialog/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQrcFile/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppFileIo/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppTrace/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppAbout/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppHelp/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Libraries/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../Tools/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../../*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/../*.*
rm Projects/Classes/CppRichelBilderbeekProgram/*.*
rm Projects/Tools/ToolCreateQtProjectZipFile/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Classes/CppQtCreatorProFile/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Classes/CppMenuDialog/*.*
rm Projects/Classes/CppQrcFile/*.*
rm Projects/Classes/CppFileIo/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Classes/CppHelp/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppRichelBilderbeekProgram
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Tools/ToolCreateQtProjectZipFile
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtHideAndShowDialog
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtCreatorProFile
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQtAboutDialog
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppMenuDialog
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppQrcFile
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppFileIo
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppTrace
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppAbout
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes/CppHelp
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Libraries
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Classes
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../../Tools
rmdir Projects/Tools/ToolCreateQtProjectZipFile/../..
rmdir Projects/Tools/ToolCreateQtProjectZipFile/..
rmdir Projects/Classes/CppRichelBilderbeekProgram
rmdir Projects/Tools/ToolCreateQtProjectZipFile
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Classes/CppQtCreatorProFile
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Classes/CppMenuDialog
rmdir Projects/Classes/CppQrcFile
rmdir Projects/Classes/CppFileIo
rmdir Projects/Classes/CppTrace
rmdir Projects/Classes/CppAbout
rmdir Projects/Classes/CppHelp
rmdir Projects/Classes
rmdir Projects/Tools
rmdir Projects

echo "Done"

# QtCreatorProFileZipScript, version 1.2
# Copyright (C) 2013-2014 Richel Bilderbeek
# Programmed on the 19th of May 2013
# by Richel Bilderbeek
#
# QtCreatorProFileZipScript can be downloaded from http://www.richelbilderbeek.nl/CppQtCreatorProFileZipScript.htm
# Licenced under GPL 3.0
