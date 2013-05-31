#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppQtAboutDialog
#     * CppQtShapeWidget
#     * CppRectangle
#     * CppShape
#     * CppShapeWidget
#     * CppTrace
#     * CppWidget
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtMultipleChoiceShapeWidget
#     * CppWtOpenShapeWidget
#     * CppWtShapeWidget
#   * Tools
#    * ToolTestShape

echo "Converting DIA to PNG"
dia --filter=png ToolTestShapeArchitecture.dia

echo "Removing previous user's information"
rm ToolTestShapeDesktop.pro.user
rm ToolTestShapeWebsite.pro.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtShapeWidget
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppShape
mkdir temp_zip/Classes/CppShapeWidget
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtShapeWidget
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestShape

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtShapeWidget/*.* temp_zip/Classes/CppQtShapeWidget
cp ../../Classes/CppRectangle/*.* temp_zip/Classes/CppRectangle
cp ../../Classes/CppShape/*.* temp_zip/Classes/CppShape
cp ../../Classes/CppShapeWidget/*.* temp_zip/Classes/CppShapeWidget
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWidget/*.* temp_zip/Classes/CppWidget
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtShapeWidget/*.* temp_zip/Classes/CppWtShapeWidget
cp ../../Tools/ToolTestShape/*.* temp_zip/Tools/ToolTestShape

FILENAME=ToolTestShapeSource_2_0
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
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtShapeWidget/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppShape/*.*
rm temp_zip/Classes/CppShapeWidget/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtShapeWidget/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtShapeWidget
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppShape
rmdir temp_zip/Classes/CppShapeWidget
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtShapeWidget
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestShape/*.*
rmdir temp_zip/Tools/ToolTestShape
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
