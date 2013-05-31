#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppDial
#     * CppDialWidget
#     * CppLed
#     * CppLedWidget
#     * CppQtAboutDialog
#     * CppQtLedWidget
#     * CppRainbow
#     * CppRectangle
#     * CppTrace
#     * CppWidget
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtDialWidget
#     * CppWtLedWidget
#   * Tools
#    * ToolTestLed

echo "Converting DIA to PNG"
dia --filter=png ToolTestLedArchitecture.dia

echo "Removing previous user's information"
rm *.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppDial
mkdir temp_zip/Classes/CppDialWidget
mkdir temp_zip/Classes/CppLed
mkdir temp_zip/Classes/CppLedWidget
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtLedWidget
mkdir temp_zip/Classes/CppRainbow
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtDialWidget
mkdir temp_zip/Classes/CppWtLedWidget
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestLed

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppDial/*.* temp_zip/Classes/CppDial
cp ../../Classes/CppDialWidget/*.* temp_zip/Classes/CppDialWidget
cp ../../Classes/CppLed/*.* temp_zip/Classes/CppLed
cp ../../Classes/CppLedWidget/*.* temp_zip/Classes/CppLedWidget
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtLedWidget/*.* temp_zip/Classes/CppQtLedWidget
cp ../../Classes/CppRainbow/*.* temp_zip/Classes/CppRainbow
cp ../../Classes/CppRectangle/*.* temp_zip/Classes/CppRectangle
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWidget/*.* temp_zip/Classes/CppWidget
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtDialWidget/*.* temp_zip/Classes/CppWtDialWidget
cp ../../Classes/CppWtLedWidget/*.* temp_zip/Classes/CppWtLedWidget
cp ../../Tools/ToolTestLed/*.* temp_zip/Tools/ToolTestLed

FILENAME=ToolTestLedSource_1_3
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
rm temp_zip/Classes/CppDial/*.*
rm temp_zip/Classes/CppDialWidget/*.*
rm temp_zip/Classes/CppLed/*.*
rm temp_zip/Classes/CppLedWidget/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtLedWidget/*.*
rm temp_zip/Classes/CppRainbow/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtDialWidget/*.*
rm temp_zip/Classes/CppWtLedWidget/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppDial
rmdir temp_zip/Classes/CppDialWidget
rmdir temp_zip/Classes/CppLed
rmdir temp_zip/Classes/CppLedWidget
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtLedWidget
rmdir temp_zip/Classes/CppRainbow
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtDialWidget
rmdir temp_zip/Classes/CppWtLedWidget
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestLed/*.*
rmdir temp_zip/Tools/ToolTestLed
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
