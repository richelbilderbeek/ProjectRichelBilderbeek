#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppQtAboutDialog
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#   * Libraries
#     * fparser4.4.3
#   * Tools
#    * ToolTestFunctionParser

echo "Removing user files"
rm *.user

rm copy.txt
rm tmp.txt

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/fparser4.4.3
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestFunctionParser

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Libraries/fparser4.4.3/*.* temp_zip/Libraries/fparser4.4.3
cp ../../Tools/ToolTestFunctionParser/*.* temp_zip/Tools/ToolTestFunctionParser

echo "Compressing files"
cd temp_zip


FILENAME=ToolTestFunctionParserSource_2_2
ZIP_FILENAME=$FILENAME".zip"

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
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes
#Libraries
rm temp_zip/Libraries/fparser4.4.3/*.*
rmdir temp_zip/Libraries/fparser4.4.3
rmdir temp_zip/Libraries
#Tools
rm temp_zip/Tools/ToolTestFunctionParser/*.*
rmdir temp_zip/Tools/ToolTestFunctionParser
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
