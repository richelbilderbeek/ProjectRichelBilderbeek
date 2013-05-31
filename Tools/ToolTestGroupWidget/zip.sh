#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppRainbow
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtGroupWidget
#     * ???
#   * Tools
#    * ToolTestGroupWidget

rm ToolTestGroupWidgetWebsite.pro.user
rm copy.txt
rm tmp.txt

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppRainbow
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtGroupWidget
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestGroupWidget

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppRainbow/*.* temp_zip/Classes/CppRainbow
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtGroupWidget/*.* temp_zip/Classes/CppWtGroupWidget
cp ../../Tools/ToolTestGroupWidget/*.* temp_zip/Tools/ToolTestGroupWidget



FILENAME=ToolTestGroupWidgetSource_1_3
ZIP_FILENAME=$FILENAME".zip"

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
rm temp_zip/Classes/CppRainbow/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtGroupWidget/*.*

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppRainbow
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtGroupWidget
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestGroupWidget/*.*
rmdir temp_zip/Tools/ToolTestGroupWidget
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
