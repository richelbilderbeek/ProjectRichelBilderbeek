#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppQtAboutDialog
#    * CppQtSprites
#    * CppWtAboutDialog
#    * CppWtAutoConfig
#  * Tools
#    * ToolPicToCode

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtSprites
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolPicToCode

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtSprites/*.* temp_zip/Classes/CppQtSprites
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Tools/ToolPicToCode/*.* temp_zip/Tools/ToolPicToCode

echo "Compressing files"
cd temp_zip
zip -r ToolPicToCodeSource_1_3 Classes
zip -r ToolPicToCodeSource_1_3 Tools
cd ..
cp temp_zip/ToolPicToCodeSource_1_3.zip ToolPicToCodeSource_1_3.zip

echo "Cleaning up"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtSprites/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtSprites
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes

rm temp_zip/Tools/ToolPicToCode/*.*
rmdir temp_zip/Tools/ToolPicToCode
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
