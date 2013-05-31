#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Libraries
mkdir temp_zip/Tools

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppMatrix
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppQtModel
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Libraries/fparser4.4.3
mkdir temp_zip/Libraries/fparser4.4.3/extrasrc
mkdir temp_zip/Libraries/fparser4.5.1
mkdir temp_zip/Libraries/fparser4.5.1/extrasrc
mkdir temp_zip/Tools/Classes
mkdir temp_zip/Tools/ToolTestQtModels

echo "Copying files"

cp ../../Classes/CppAbout/Licence.txt temp_zip/Classes/CppAbout/Licence.txt
cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppMatrix/Licence.txt temp_zip/Classes/CppMatrix/Licence.txt
cp ../../Classes/CppMatrix/matrix.cpp temp_zip/Classes/CppMatrix/matrix.cpp
cp ../../Classes/CppMatrix/matrix.h temp_zip/Classes/CppMatrix/matrix.h
cp ../../Classes/CppQtAboutDialog/Licence.txt temp_zip/Classes/CppQtAboutDialog/Licence.txt
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtModel/Licence.txt temp_zip/Classes/CppQtModel/Licence.txt
cp ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp temp_zip/Classes/CppQtModel/qtstdvectorfunctionmodel.cpp
cp ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h temp_zip/Classes/CppQtModel/qtstdvectorfunctionmodel.h
cp ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp temp_zip/Classes/CppQtModel/qtstdvectorstringmodel.cpp
cp ../../Classes/CppQtModel/qtstdvectorstringmodel.h temp_zip/Classes/CppQtModel/qtstdvectorstringmodel.h
cp ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp temp_zip/Classes/CppQtModel/qtublasmatrixdoublemodel.cpp
cp ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h temp_zip/Classes/CppQtModel/qtublasmatrixdoublemodel.h
cp ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp temp_zip/Classes/CppQtModel/qtublasvectordoublemodel.cpp
cp ../../Classes/CppQtModel/qtublasvectordoublemodel.h temp_zip/Classes/CppQtModel/qtublasvectordoublemodel.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Libraries/fparser4.4.3/extrasrc/fp_identifier_parser.inc temp_zip/Libraries/fparser4.4.3/extrasrc/fp_identifier_parser.inc
cp ../../Libraries/fparser4.4.3/extrasrc/fp_opcode_add.inc temp_zip/Libraries/fparser4.4.3/extrasrc/fp_opcode_add.inc
cp ../../Libraries/fparser4.4.3/extrasrc/fpaux.hh temp_zip/Libraries/fparser4.4.3/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.4.3/extrasrc/fptypes.hh temp_zip/Libraries/fparser4.4.3/extrasrc/fptypes.hh
cp ../../Libraries/fparser4.4.3/fparser.cc temp_zip/Libraries/fparser4.4.3/fparser.cc
cp ../../Libraries/fparser4.4.3/fparser.hh temp_zip/Libraries/fparser4.4.3/fparser.hh
cp ../../Libraries/fparser4.4.3/fpconfig.hh temp_zip/Libraries/fparser4.4.3/fpconfig.hh
cp ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc temp_zip/Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc
cp ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc temp_zip/Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc
cp ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh temp_zip/Libraries/fparser4.5.1/extrasrc/fpaux.hh
cp ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh temp_zip/Libraries/fparser4.5.1/extrasrc/fptypes.hh
cp ../../Libraries/fparser4.5.1/fparser.cc temp_zip/Libraries/fparser4.5.1/fparser.cc
cp ../../Libraries/fparser4.5.1/fparser.hh temp_zip/Libraries/fparser4.5.1/fparser.hh
cp ../../Libraries/fparser4.5.1/fpconfig.hh temp_zip/Libraries/fparser4.5.1/fpconfig.hh
cp ../../Tools/Classes/CppAbout temp_zip/Tools/Classes/CppAbout
cp ../../Tools/Classes/CppMatrix temp_zip/Tools/Classes/CppMatrix
cp ../../Tools/Classes/CppQtAboutDialog temp_zip/Tools/Classes/CppQtAboutDialog
cp ../../Tools/Classes/CppQtHideAndShowDialog temp_zip/Tools/Classes/CppQtHideAndShowDialog
cp ../../Tools/Classes/CppQtModel temp_zip/Tools/Classes/CppQtModel
cp ../../Tools/Classes/CppTrace temp_zip/Tools/Classes/CppTrace
cp ../../Tools/ToolTestQtModels/INCLUDEPATH+= temp_zip/Tools/ToolTestQtModels/INCLUDEPATH+=
cp ../../Tools/ToolTestQtModels/Licence.txt temp_zip/Tools/ToolTestQtModels/Licence.txt
cp ../../Tools/ToolTestQtModels/SOURCES+= temp_zip/Tools/ToolTestQtModels/SOURCES+=
cp ../../Tools/ToolTestQtModels/ToolTestQtModels.pro temp_zip/Tools/ToolTestQtModels/ToolTestQtModels.pro
cp ../../Tools/ToolTestQtModels/qtmain.cpp temp_zip/Tools/ToolTestQtModels/qtmain.cpp
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.cpp temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.cpp
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.h temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.h
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.ui temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.ui
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.cpp temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.cpp
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.h temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.h
cp ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.ui temp_zip/Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.ui
cp ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.cpp temp_zip/Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.cpp
cp ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.h temp_zip/Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.h
cp ../../Tools/ToolTestQtModels/zip.sh temp_zip/Tools/ToolTestQtModels/zip.sh

FILENAME="ToolTestQtModelsSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Libraries
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppMatrix/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppQtModel/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Libraries/fparser4.4.3/*.*
rm temp_zip/Libraries/fparser4.4.3/extrasrc/*.*
rm temp_zip/Libraries/fparser4.5.1/*.*
rm temp_zip/Libraries/fparser4.5.1/extrasrc/*.*
rm temp_zip/Tools/Classes/*.*
rm temp_zip/Tools/ToolTestQtModels/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppMatrix
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtModel
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Libraries/fparser4.4.3/extrasrc
rmdir temp_zip/Libraries/fparser4.4.3
rmdir temp_zip/Libraries/fparser4.5.1/extrasrc
rmdir temp_zip/Libraries/fparser4.5.1
rmdir temp_zip/Tools/Classes
rmdir temp_zip/Tools/ToolTestQtModels

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Libraries
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
