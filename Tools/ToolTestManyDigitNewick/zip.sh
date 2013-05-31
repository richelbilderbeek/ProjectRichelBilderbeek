#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppBinaryNewickVector
#     * CppNewick
#     * CppQtAboutDialog
#     * CppTwoDigitNewick
#   * Libraries
#     * bigint-2010.04.30
#   * Tools
#    * ToolTestTwoDigitNewick
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppBinaryNewickVector
mkdir temp_zip/Classes/CppNewick
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppTwoDigitNewick
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestTwoDigitNewick

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppBinaryNewickVector/*.* temp_zip/Classes/CppBinaryNewickVector
cp ../../Classes/CppNewick/*.* temp_zip/Classes/CppNewick
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppTwoDigitNewick/*.* temp_zip/Classes/CppTwoDigitNewick
cp ../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp ../../Tools/ToolTestTwoDigitNewick/*.* temp_zip/Tools/ToolTestTwoDigitNewick

echo "Compressing files"
cd temp_zip

zip -r ToolTestTwoDigitNewickSource_2_0 Classes
zip -r ToolTestTwoDigitNewickSource_2_0 Libraries
zip -r ToolTestTwoDigitNewickSource_2_0 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTestTwoDigitNewickSource_2_0.zip ToolTestTwoDigitNewickSource_2_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppBinaryNewickVector/*.*
rm temp_zip/Classes/CppNewick/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppTwoDigitNewick/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppBinaryNewickVector
rmdir temp_zip/Classes/CppNewick
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppTwoDigitNewick
rmdir temp_zip/Classes
#Libraries
rm temp_zip/Libraries/bigint-2010.04.30/*.*
rmdir temp_zip/Libraries/bigint-2010.04.30
rmdir temp_zip/Libraries
#Tools
rm temp_zip/Tools/ToolTestTwoDigitNewick/*.*
rmdir temp_zip/Tools/ToolTestTwoDigitNewick
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
