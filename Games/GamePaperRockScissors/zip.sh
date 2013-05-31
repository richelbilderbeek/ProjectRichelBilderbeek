#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppWtAboutDialog
#   * Tools
#    * ToolTimePoll
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTimePoll

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Tools/ToolTimePoll/*.* temp_zip/Tools/ToolTimePoll

echo "Compressing files"
cd temp_zip

zip -r ToolTimePollSource_1_1 Classes
zip -r ToolTimePollSource_1_1 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTimePollSource_1_1.zip ToolTimePollSource_1_1.zip

echo "Cleaning up"

#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTimePoll/*.*
rmdir temp_zip/Tools/ToolTimePoll
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
