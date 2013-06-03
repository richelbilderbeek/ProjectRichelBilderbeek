#!/bin/sh
# Created from file '../../Tools/ToolTestFunctionParser/ToolTestFunctionParserDesktop.pro'

echo "Creating of all folders"

mkdir Projects
mkdir Projects/Tools
mkdir Projects/Classes
mkdir Projects/Libraries
mkdir Projects/Classes/CppAbout
mkdir Projects/Libraries/fparser4.4.3
mkdir Projects/Libraries/fparser4.5.1
mkdir Projects/Classes/CppWtAutoConfig
mkdir Projects/Classes/CppQtAboutDialog
mkdir Projects/Classes/CppWtAboutDialog
mkdir Projects/Tools/ToolTestFunctionParser
mkdir Projects/Classes/CppQtHideAndShowDialog
mkdir Projects/Libraries/fparser4.5.1/extrasrc

echo "Copying files"

cp ../../Classes/CppAbout/about.h Projects/Classes/CppAbout/about.h
cp ../../Classes/CppAbout/about.cpp Projects/Classes/CppAbout/about.cpp
cp ../../Libraries/fparser4.4.3/fparser.cc Projects/Libraries/fparser4.4.3/fparser.cc
cp ../../Libraries/fparser4.4.3/fparser.hh Projects/Libraries/fparser4.4.3/fparser.hh
cp ../../Libraries/fparser4.5.1/fparser.cc Projects/Libraries/fparser4.5.1/fparser.cc
cp ../../Libraries/fparser4.5.1/fparser.hh Projects/Libraries/fparser4.5.1/fparser.hh
cp ../../Libraries/fparser4.5.1/fpconfig.hh Projects/Libraries/fparser4.5.1/fpconfig.hh
cp ../../Libraries/fparser4.5.1/fpoptimizer.cc Projects/Libraries/fparser4.5.1/fpoptimizer.cc
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h Projects/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Libraries/fparser4.5.1/fparser_mpfr.hh Projects/Libraries/fparser4.5.1/fparser_mpfr.hh
cp ../../Tools/ToolTestFunctionParser/qtmain.cpp Projects/Tools/ToolTestFunctionParser/qtmain.cpp
cp ../../Tools/ToolTestFunctionParser/wtmain.cpp Projects/Tools/ToolTestFunctionParser/wtmain.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h Projects/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h Projects/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp Projects/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh Projects/Libraries/fparser4.5.1/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.5.1/fparser_gmpint.hh Projects/Libraries/fparser4.5.1/fparser_gmpint.hh
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui Projects/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp Projects/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt Projects/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp Projects/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh Projects/Libraries/fparser4.5.1/extrasrc/fptypes.hh
cp ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp Projects/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Tools/ToolTestFunctionParser/ToolTestFunctionParser.qrc Projects/Tools/ToolTestFunctionParser/ToolTestFunctionParser.qrc
cp ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc Projects/Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc
cp ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h Projects/Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.h Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.h
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.h Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.h
cp ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp Projects/Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp
cp ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.h Projects/Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.h
cp ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.h Projects/Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.h
cp ../../Tools/ToolTestFunctionParser/ToolTestFunctionParserDesktop.pro Projects/Tools/ToolTestFunctionParser/ToolTestFunctionParserDesktop.pro
cp ../../Tools/ToolTestFunctionParser/ToolTestFunctionParserWebsite.pro Projects/Tools/ToolTestFunctionParser/ToolTestFunctionParserWebsite.pro
cp ../../Tools/ToolTestFunctionParser/ToolTestFunctionParserWelcome.png Projects/Tools/ToolTestFunctionParser/ToolTestFunctionParserWelcome.png
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.ui Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.ui
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.ui Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.ui
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.cpp Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.cpp
cp ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.cpp Projects/Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.cpp
cp ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.cpp Projects/Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.cpp
cp ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.cpp Projects/Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.cpp

FILENAME="../../Tools/ToolTestFunctionParserSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

zip -r $FILENAME Projects

echo "Cleaning up"

echo "Emptying subfolders"

rm Projects/Libraries/fparser4.5.1/extrasrc/*.*
rm Projects/Classes/CppQtHideAndShowDialog/*.*
rm Projects/Tools/ToolTestFunctionParser/*.*
rm Projects/Classes/CppWtAboutDialog/*.*
rm Projects/Classes/CppQtAboutDialog/*.*
rm Projects/Classes/CppWtAutoConfig/*.*
rm Projects/Libraries/fparser4.5.1/*.*
rm Projects/Libraries/fparser4.4.3/*.*
rm Projects/Classes/CppAbout/*.*
rm Projects/Libraries/*.*
rm Projects/Classes/*.*
rm Projects/Tools/*.*
rm Projects/*.*
rmdir Projects/Libraries/fparser4.5.1/extrasrc
rmdir Projects/Classes/CppQtHideAndShowDialog
rmdir Projects/Tools/ToolTestFunctionParser
rmdir Projects/Classes/CppWtAboutDialog
rmdir Projects/Classes/CppQtAboutDialog
rmdir Projects/Classes/CppWtAutoConfig
rmdir Projects/Libraries/fparser4.5.1
rmdir Projects/Libraries/fparser4.4.3
rmdir Projects/Classes/CppAbout
rmdir Projects/Libraries
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

