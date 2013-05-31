#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppCopy_if
#     * CppTrace
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtSelectFileDialog
#   * Tools
#    * ToolTestSelectFileDialog

echo "Converting DIA to PNG"
dia --filter=png ToolTestSelectFileDialogArchitecture.dia

echo "Removing previous user's information"
rm ToolTestSelectFileDialogDesktop.pro.user
rm ToolTestSelectFileDialogWebsite.pro.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppCopy_if
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtSelectFileDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestSelectFileDialog

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppCopy_if/*.* temp_zip/Classes/CppCopy_if
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtSelectFileDialog/*.* temp_zip/Classes/CppWtSelectFileDialog
cp ../../Tools/ToolTestSelectFileDialog/*.* temp_zip/Tools/ToolTestSelectFileDialog

FILENAME=ToolTestSelectFileDialogSource_1_1
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
rm temp_zip/Classes/CppCopy_if/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtSelectFileDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppCopy_if
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtSelectFileDialog
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestSelectFileDialog/*.*
rmdir temp_zip/Tools/ToolTestSelectFileDialog
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
