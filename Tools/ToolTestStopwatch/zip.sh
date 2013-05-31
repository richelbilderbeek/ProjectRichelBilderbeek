#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppStopwatch      <-- pack *.*
#  * Tools
#    * ToolTestStopwatch <-- pack *.*
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppStopwatch
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestStopwatch

echo "Copying files"
cp ../../Tools/ToolTestStopwatch/*.* temp_zip/Tools/ToolTestStopwatch
cp ../../Classes/CppStopwatch/*.* temp_zip/Classes/CppStopwatch

echo "Compressing files"
cd temp_zip

zip -r ToolTestStopwatchSource_1_1 Classes
zip -r ToolTestStopwatchSource_1_1 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTestStopwatchSource_1_1.zip ToolTestStopwatchSource_1_1.zip

echo "Cleaning up"
rm temp_zip/Classes/CppStopwatch/*.*
rmdir temp_zip/Classes/CppStopwatch
rmdir temp_zip/Classes
rm temp_zip/Tools/ToolTestStopwatch/*.*
rmdir temp_zip/Tools/ToolTestStopwatch
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"

