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
mkdir temp_zip/Classes/CppMultipleChoiceQuestion
mkdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppOpenQuestion
mkdir temp_zip/Classes/CppOpenQuestionDialog
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppQtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppQtOpenQuestionDialog
mkdir temp_zip/Classes/CppQtQuestionDialog
mkdir temp_zip/Classes/CppQuestion
mkdir temp_zip/Classes/CppQuestionDialog
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppWtOpenQuestionDialog
mkdir temp_zip/Classes/CppWtQuestionDialog
mkdir temp_zip/Tools/ToolTestQuestion

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp temp_zip/Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp
cp ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h temp_zip/Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h
cp ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp temp_zip/Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp
cp ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h temp_zip/Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h
cp ../../Classes/CppOpenQuestion/openquestion.cpp temp_zip/Classes/CppOpenQuestion/openquestion.cpp
cp ../../Classes/CppOpenQuestion/openquestion.h temp_zip/Classes/CppOpenQuestion/openquestion.h
cp ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp temp_zip/Classes/CppOpenQuestionDialog/openquestiondialog.cpp
cp ../../Classes/CppOpenQuestionDialog/openquestiondialog.h temp_zip/Classes/CppOpenQuestionDialog/openquestiondialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui
cp ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp temp_zip/Classes/CppQtQuestionDialog/qtquestiondialog.cpp
cp ../../Classes/CppQtQuestionDialog/qtquestiondialog.h temp_zip/Classes/CppQtQuestionDialog/qtquestiondialog.h
cp ../../Classes/CppQuestion/question.cpp temp_zip/Classes/CppQuestion/question.cpp
cp ../../Classes/CppQuestion/question.h temp_zip/Classes/CppQuestion/question.h
cp ../../Classes/CppQuestionDialog/questiondialog.cpp temp_zip/Classes/CppQuestionDialog/questiondialog.cpp
cp ../../Classes/CppQuestionDialog/questiondialog.h temp_zip/Classes/CppQuestionDialog/questiondialog.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h
cp ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp temp_zip/Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp
cp ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h temp_zip/Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h
cp ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp temp_zip/Classes/CppWtQuestionDialog/wtquestiondialog.cpp
cp ../../Classes/CppWtQuestionDialog/wtquestiondialog.h temp_zip/Classes/CppWtQuestionDialog/wtquestiondialog.h
cp ../../Tools/ToolTestQuestion/Questionmark.png temp_zip/Tools/ToolTestQuestion/Questionmark.png
cp ../../Tools/ToolTestQuestion/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolTestQuestion/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolTestQuestion/ToolTestDialArchitecture.dia~ temp_zip/Tools/ToolTestQuestion/ToolTestDialArchitecture.dia~
cp ../../Tools/ToolTestQuestion/ToolTestDialArchitecture_1_0.dia~ temp_zip/Tools/ToolTestQuestion/ToolTestDialArchitecture_1_0.dia~
cp ../../Tools/ToolTestQuestion/ToolTestQuestion.qrc temp_zip/Tools/ToolTestQuestion/ToolTestQuestion.qrc
cp ../../Tools/ToolTestQuestion/ToolTestQuestionArchitecture.dia temp_zip/Tools/ToolTestQuestion/ToolTestQuestionArchitecture.dia
cp ../../Tools/ToolTestQuestion/ToolTestQuestionArchitecture.dia~ temp_zip/Tools/ToolTestQuestion/ToolTestQuestionArchitecture.dia~
cp ../../Tools/ToolTestQuestion/ToolTestQuestionArchitecture.png temp_zip/Tools/ToolTestQuestion/ToolTestQuestionArchitecture.png
cp ../../Tools/ToolTestQuestion/ToolTestQuestionDesktop.pro temp_zip/Tools/ToolTestQuestion/ToolTestQuestionDesktop.pro
cp ../../Tools/ToolTestQuestion/ToolTestQuestionIcon14x14.png temp_zip/Tools/ToolTestQuestion/ToolTestQuestionIcon14x14.png
cp ../../Tools/ToolTestQuestion/ToolTestQuestionWebsite.pro temp_zip/Tools/ToolTestQuestion/ToolTestQuestionWebsite.pro
cp ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome.png temp_zip/Tools/ToolTestQuestion/ToolTestQuestionWelcome.png
cp ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome1.png temp_zip/Tools/ToolTestQuestion/ToolTestQuestionWelcome1.png
cp ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome2.png temp_zip/Tools/ToolTestQuestion/ToolTestQuestionWelcome2.png
cp ../../Tools/ToolTestQuestion/crosscompiletowindows.sh temp_zip/Tools/ToolTestQuestion/crosscompiletowindows.sh
cp ../../Tools/ToolTestQuestion/qtmain.cpp temp_zip/Tools/ToolTestQuestion/qtmain.cpp
cp ../../Tools/ToolTestQuestion/qttestquestionmaindialog.cpp temp_zip/Tools/ToolTestQuestion/qttestquestionmaindialog.cpp
cp ../../Tools/ToolTestQuestion/qttestquestionmaindialog.h temp_zip/Tools/ToolTestQuestion/qttestquestionmaindialog.h
cp ../../Tools/ToolTestQuestion/qttestquestionmaindialog.ui temp_zip/Tools/ToolTestQuestion/qttestquestionmaindialog.ui
cp ../../Tools/ToolTestQuestion/qttestquestionmenudialog.cpp temp_zip/Tools/ToolTestQuestion/qttestquestionmenudialog.cpp
cp ../../Tools/ToolTestQuestion/qttestquestionmenudialog.h temp_zip/Tools/ToolTestQuestion/qttestquestionmenudialog.h
cp ../../Tools/ToolTestQuestion/qttestquestionmenudialog.ui temp_zip/Tools/ToolTestQuestion/qttestquestionmenudialog.ui
cp ../../Tools/ToolTestQuestion/question.png temp_zip/Tools/ToolTestQuestion/question.png
cp ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp temp_zip/Tools/ToolTestQuestion/testquestionmaindialog.cpp
cp ../../Tools/ToolTestQuestion/testquestionmaindialog.h temp_zip/Tools/ToolTestQuestion/testquestionmaindialog.h
cp ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp temp_zip/Tools/ToolTestQuestion/testquestionmenudialog.cpp
cp ../../Tools/ToolTestQuestion/testquestionmenudialog.h temp_zip/Tools/ToolTestQuestion/testquestionmenudialog.h
cp ../../Tools/ToolTestQuestion/tmp.txt temp_zip/Tools/ToolTestQuestion/tmp.txt
cp ../../Tools/ToolTestQuestion/trace_out.txt temp_zip/Tools/ToolTestQuestion/trace_out.txt
cp ../../Tools/ToolTestQuestion/wt.css temp_zip/Tools/ToolTestQuestion/wt.css
cp ../../Tools/ToolTestQuestion/wtmain.cpp temp_zip/Tools/ToolTestQuestion/wtmain.cpp
cp ../../Tools/ToolTestQuestion/wttestquestionmaindialog.cpp temp_zip/Tools/ToolTestQuestion/wttestquestionmaindialog.cpp
cp ../../Tools/ToolTestQuestion/wttestquestionmaindialog.h temp_zip/Tools/ToolTestQuestion/wttestquestionmaindialog.h
cp ../../Tools/ToolTestQuestion/wttestquestionmenudialog.cpp temp_zip/Tools/ToolTestQuestion/wttestquestionmenudialog.cpp
cp ../../Tools/ToolTestQuestion/wttestquestionmenudialog.h temp_zip/Tools/ToolTestQuestion/wttestquestionmenudialog.h
cp ../../Tools/ToolTestQuestion/zip.sh temp_zip/Tools/ToolTestQuestion/zip.sh

FILENAME="ToolTestQuestionSource"
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
rm temp_zip/Classes/CppMultipleChoiceQuestion/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppOpenQuestion/*.*
rm temp_zip/Classes/CppOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppQtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQtQuestionDialog/*.*
rm temp_zip/Classes/CppQuestion/*.*
rm temp_zip/Classes/CppQuestionDialog/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppWtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppWtQuestionDialog/*.*
rm temp_zip/Tools/ToolTestQuestion/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppMultipleChoiceQuestion
rmdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppOpenQuestion
rmdir temp_zip/Classes/CppOpenQuestionDialog
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppQtOpenQuestionDialog
rmdir temp_zip/Classes/CppQtQuestionDialog
rmdir temp_zip/Classes/CppQuestion
rmdir temp_zip/Classes/CppQuestionDialog
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppWtOpenQuestionDialog
rmdir temp_zip/Classes/CppWtQuestionDialog
rmdir temp_zip/Tools/ToolTestQuestion

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
