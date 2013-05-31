#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtBroadcastServer
#   * Tools
#    * ToolTestBroadcastServer

echo "Removing old user information"
rm copy.txt
rm tmp.txt
rm ToolTestBroadcastServer.pro.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtBroadcastServer

mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestBroadcastServer

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtBroadcastServer/*.* temp_zip/Classes/CppWtBroadcastServer

cp ../../Tools/ToolTestBroadcastServer/*.* temp_zip/Tools/ToolTestBroadcastServer



FILENAME=ToolTestBroadcastServerSource_1_2
ZIP_FILENAME=$FILENAME".zip"

echo "Remove previous zip"
rm $ZIP_FILENAME

#echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
#zip -r $FILENAME Games
#zip -r $FILENAME Libraries
#zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtBroadcastServer/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtBroadcastServer
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestBroadcastServer/*.*
rmdir temp_zip/Tools/ToolTestBroadcastServer
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
