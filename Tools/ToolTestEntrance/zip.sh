#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppIpAddress
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtEntrance
#   * Tools
#    * ToolTestEntrance

echo "Removing old user information"
FOLDERNAME=ToolTestEntrance
FILENAME=$FOLDERNAME"Source_1_0"
ZIP_FILENAME=$FILENAME".zip"
HTM_FILENAME=$FILENAME".htm"

rm *.user
rm $ZIP_FILENAME
rm $HTM_FILENAME

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppIpAddress
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtEntrance

mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestEntrance

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppIpAddress/*.* temp_zip/Classes/CppIpAddress
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtEntrance/*.* temp_zip/Classes/CppWtEntrance

cp ../../Tools/ToolTestEntrance/*.* temp_zip/Tools/ToolTestEntrance

echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
#zip -r $FILENAME Libraries
#zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppIpAddress/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtEntrance/*.*

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppIpAddress
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtEntrance
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestEntrance/*.*
rmdir temp_zip/Tools/ToolTestEntrance
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"

../../Tools/ToolCodeToHtmlConsole-build-desktop/codetohtml --source "../"$FOLDERNAME
cp $FOLDERNAME".htm" $HTM_FILENAME
rm $FOLDERNAME".htm"
