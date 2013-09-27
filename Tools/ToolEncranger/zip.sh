#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppEncranger
#     * CppLoopReader
#     * CppQtAboutDialog
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#   * Tools
#    * ToolTestEncranger

rm *.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppEncranger
mkdir temp_zip/Classes/CppLoopReader
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestEncranger

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppEncranger/*.* temp_zip/Classes/CppEncranger
cp ../../Classes/CppLoopReader/*.* temp_zip/Classes/CppLoopReader
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Tools/ToolTestEncranger/*.* temp_zip/Tools/ToolTestEncranger

FILENAME=ToolTestEncrangerSource_2_4
ZIP_FILENAME=$FILENAME".zip"

echo "Remove previous zip"
rm $ZIP_FILENAME

#echo "Compressing files"
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
rm temp_zip/Classes/CppEncranger/*.*
rm temp_zip/Classes/CppLoopReader/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppEncranger
rmdir temp_zip/Classes/CppLoopReader
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes
#Tools
rm temp_zip/Tools/ToolTestEncranger/*.*
rmdir temp_zip/Tools/ToolTestEncranger
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
