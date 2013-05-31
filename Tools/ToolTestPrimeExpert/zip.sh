#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppPrimeExpert
#     * CppQtAboutDialog
#   * Tools
#    * ToolTestPrimeExpert
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppPrimeExpert
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestPrimeExpert

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppPrimeExpert/*.* temp_zip/Classes/CppPrimeExpert
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Tools/ToolTestPrimeExpert/*.* temp_zip/Tools/ToolTestPrimeExpert

echo "Compressing files"
cd temp_zip

zip -r ToolTestPrimeExpertSource_2_0 Classes
zip -r ToolTestPrimeExpertSource_2_0 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTestPrimeExpertSource_2_0.zip ToolTestPrimeExpertSource_2_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppPrimeExpert/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppPrimeExpert
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes
#Tools
rm temp_zip/Tools/ToolTestPrimeExpert/*.*
rmdir temp_zip/Tools/ToolTestPrimeExpert
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
