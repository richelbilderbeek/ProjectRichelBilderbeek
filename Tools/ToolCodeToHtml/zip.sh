#!/bin/sh
# Created from file '../../Tools/ToolCodeToHtml/ToolCodeToHtmlWebsite.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Classes/CppAbout
mkdir Projects/Classes/CppTrace
mkdir Projects/Classes/CppQrcFile
mkdir Projects/Tools/ToolCodeToHtml
mkdir Projects/Classes/CppCodeToHtml
mkdir Projects/Classes/CppWtAutoConfig
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppWtAboutDialog
mkdir Projects/Classes/CppQtCreatorProFile
mkdir Projects/Classes/CppQtHideAndShowDialog

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppTrace/trace.h Projects/Classes/CppTrace/trace.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Tools/ToolCodeToHtml/R.png Projects/Tools/ToolCodeToHtml/R.png
cp ../../Tools/ToolCodeToHtml/zip.sh Projects/Tools/ToolCodeToHtml/zip.sh
cp ../../Classes/CppQrcFile/qrcfile.h Projects/Classes/CppQrcFile/qrcfile.h
cp ../../Tools/ToolCodeToHtml/main.cpp Projects/Tools/ToolCodeToHtml/main.cpp
cp ../../Classes/CppQrcFile/Licence.txt Projects/Classes/CppQrcFile/Licence.txt
cp ../../Classes/CppQrcFile/qrcfile.cpp Projects/Classes/CppQrcFile/qrcfile.cpp
cp ../../Tools/ToolCodeToHtml/qtmain.cpp Projects/Tools/ToolCodeToHtml/qtmain.cpp
cp ../../Tools/ToolCodeToHtml/wtmain.cpp Projects/Tools/ToolCodeToHtml/wtmain.cpp
cp ../../Classes/CppCodeToHtml/codetohtml.h Projects/Classes/CppCodeToHtml/codetohtml.h
cp ../../Classes/CppCodeToHtml/codetohtml.cpp Projects/Classes/CppCodeToHtml/codetohtml.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlinfo.h Projects/Classes/CppCodeToHtml/codetohtmlinfo.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h Projects/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Classes/CppQtCreatorProFile/Licence.txt Projects/Classes/CppQtCreatorProFile/Licence.txt
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtml.qrc Projects/Tools/ToolCodeToHtml/ToolCodeToHtml.qrc
cp ../../Classes/CppCodeToHtml/codetohtmldialog.h Projects/Classes/CppCodeToHtml/codetohtmldialog.h
cp ../../Classes/CppCodeToHtml/codetohtmlfooter.h Projects/Classes/CppCodeToHtml/codetohtmlfooter.h
cp ../../Classes/CppCodeToHtml/codetohtmlheader.h Projects/Classes/CppCodeToHtml/codetohtmlheader.h
cp ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp Projects/Classes/CppCodeToHtml/codetohtmlinfo.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h Projects/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp Projects/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlcontent.h Projects/Classes/CppCodeToHtml/codetohtmlcontent.h
cp ../../Classes/CppCodeToHtml/codetohtmlversion.h Projects/Classes/CppCodeToHtml/codetohtmlversion.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.h Projects/Tools/ToolCodeToHtml/wtcodetohtmldialog.h
cp ../../Classes/CppCodeToHtml/codetohtmldialog.cpp Projects/Classes/CppCodeToHtml/codetohtmldialog.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp Projects/Classes/CppCodeToHtml/codetohtmlfooter.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlheader.cpp Projects/Classes/CppCodeToHtml/codetohtmlheader.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlpagetype.h Projects/Classes/CppCodeToHtml/codetohtmlpagetype.h
cp ../../Classes/CppCodeToHtml/codetohtmltechinfo.h Projects/Classes/CppCodeToHtml/codetohtmltechinfo.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp Projects/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp Projects/Classes/CppCodeToHtml/codetohtmlcontent.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlversion.cpp Projects/Classes/CppCodeToHtml/codetohtmlversion.cpp
cp ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h Projects/Tools/ToolCodeToHtml/codetohtmlmenudialog.h
cp ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.cpp Projects/Tools/ToolCodeToHtml/wtcodetohtmldialog.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlpagetype.cpp Projects/Classes/CppCodeToHtml/codetohtmlpagetype.cpp
cp ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp Projects/Classes/CppCodeToHtml/codetohtmltechinfo.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h Projects/Classes/CppCodeToHtml/codetohtmlcontenttype.h
cp ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp Projects/Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp
cp ../../Tools/ToolCodeToHtml/crosscompiletowindows.sh Projects/Tools/ToolCodeToHtml/crosscompiletowindows.sh
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.h Projects/Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.h
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.h Projects/Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.h
cp ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.h Projects/Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.h
cp ../../Classes/CppCodeToHtml/codetohtmlreplacements.h Projects/Classes/CppCodeToHtml/codetohtmlreplacements.h
cp ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h Projects/Classes/CppCodeToHtml/codetohtmltechinfotype.h
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.h
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtmlConsole.pro Projects/Tools/ToolCodeToHtml/ToolCodeToHtmlConsole.pro
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtmlDesktop.pro Projects/Tools/ToolCodeToHtml/ToolCodeToHtmlDesktop.pro
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtmlWebsite.pro Projects/Tools/ToolCodeToHtml/ToolCodeToHtmlWebsite.pro
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtmlWelcome.png Projects/Tools/ToolCodeToHtml/ToolCodeToHtmlWelcome.png
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.ui Projects/Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.ui
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.ui Projects/Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.ui
cp ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp Projects/Classes/CppCodeToHtml/codetohtmlcontenttype.cpp
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.cpp Projects/Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.cpp
cp ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.cpp Projects/Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.cpp
cp ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.cpp Projects/Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp Projects/Classes/CppCodeToHtml/codetohtmlreplacements.cpp
cp ../../Classes/CppCodeToHtml/codetohtmltechinfotype.cpp Projects/Classes/CppCodeToHtml/codetohtmltechinfotype.cpp
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofile.cpp
cp ../../Tools/ToolCodeToHtml/ToolCodeToHtmlHelloWorld.png Projects/Tools/ToolCodeToHtml/ToolCodeToHtmlHelloWorld.png
cp ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp Projects/Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp Projects/Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h Projects/Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h
cp ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp Projects/Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp

FILENAME="../../Tools/ToolCodeToHtmlSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Classes/CppQtCreatorProFile/*.*
rm Projects/Classes/CppWtAboutDialog/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Classes/CppWtAutoConfig/*.*
rm Projects/Classes/CppCodeToHtml/*.*
rm Projects/Tools/ToolCodeToHtml/*.*
rm Projects/Classes/CppQrcFile/*.*
rm Projects/Classes/CppTrace/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Classes/CppQtCreatorProFile
rmdir Projects/Classes/CppWtAboutDialog
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Classes/CppWtAutoConfig
rmdir Projects/Classes/CppCodeToHtml
rmdir Projects/Tools/ToolCodeToHtml
rmdir Projects/Classes/CppQrcFile
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

