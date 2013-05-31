#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppMultiVector
#   * Tools
#    * ToolTestMultiVector
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppMultiVector
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestMultiVector

echo "Copying files"
cp ../../Classes/CppMultiVector/*.* temp_zip/Classes/CppMultiVector
cp ../../Tools/ToolTestMultiVector/*.* temp_zip/Tools/ToolTestMultiVector

echo "Compressing files"
cd temp_zip

zip -r ToolTestMultiVectorSource_1_0 Classes
zip -r ToolTestMultiVectorSource_1_0 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTestMultiVectorSource_1_0.zip ToolTestMultiVectorSource_1_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppMultiVector/*.*
rmdir temp_zip/Classes/CppMultiVector
rmdir temp_zip/Classes
#Tools
rm temp_zip/Tools/ToolTestMultiVector/*.*
rmdir temp_zip/Tools/ToolTestMultiVector
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
