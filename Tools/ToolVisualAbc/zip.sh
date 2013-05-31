#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppQtAboutDialog
#   * Tools
#    * ToolVisualAbc
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolVisualAbc

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Tools/ToolVisualAbc/*.* temp_zip/Tools/ToolVisualAbc

echo "Compressing files"
cd temp_zip

zip -r ToolVisualAbcSource_1_0 Classes
zip -r ToolVisualAbcSource_1_0 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolVisualAbcSource_1_0.zip ToolVisualAbcSource_1_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes
#Tools
rm temp_zip/Tools/ToolVisualAbc/*.*
rmdir temp_zip/Tools/ToolVisualAbc
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
