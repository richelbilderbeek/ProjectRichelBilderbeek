#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppEncranger
#    * CppLoopReader
#  * Tools
#    * ToolMultiEncranger

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppRandomCode
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolRandomCode

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppRandomCode/*.* temp_zip/Classes/CppRandomCode
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Tools/ToolRandomCode/*.* temp_zip/Tools/ToolRandomCode

echo "Compressing files"
cd temp_zip
#Zip the folder Classes recursively in ToolRandomCodeSource_3_0.zip
zip -r ToolRandomCodeSource_3_0 Classes
#Zip the folder Tools recursively in ToolRandomCodeSource_3_0.zip
zip -r ToolRandomCodeSource_3_0 Tools
cd ..
cp temp_zip/ToolRandomCodeSource_3_0.zip ToolRandomCodeSource_3_0.zip

echo "Cleaning up"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppRandomCode/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppRandomCode
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes
rm temp_zip/Tools/ToolRandomCode/*.*
rmdir temp_zip/Tools/ToolRandomCode
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
