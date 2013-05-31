#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppAssert
#     * CppBinaryNewickVector
#     * CppEncranger
#     * CppFuzzy_equal_to
#     * CppLoopReader
#     * CppNewick
#     * CppQtAboutDialog
#     * CppTrace
#     * CppTwoDigitNewick
#     * CppWtAboutDialog
#   * Libraries
#     * bigint-2010.04.30
#   * Tools
#    * ToolTestTwoDigitNewick

rm ToolTestTwoDigitNewickConsole.pro.user
rm ToolTestTwoDigitNewickConsole64.pro.user
rm ToolTestTwoDigitNewickDesktop.pro.user
rm ToolTestTwoDigitNewickWebsite.pro.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppAssert
mkdir temp_zip/Classes/CppBinaryNewickVector
mkdir temp_zip/Classes/CppEncranger
mkdir temp_zip/Classes/CppFuzzy_equal_to
mkdir temp_zip/Classes/CppLoopReader
mkdir temp_zip/Classes/CppNewick
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppTwoDigitNewick
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestTwoDigitNewick

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppAssert/*.* temp_zip/Classes/CppAssert
cp ../../Classes/CppBinaryNewickVector/*.* temp_zip/Classes/CppBinaryNewickVector
cp ../../Classes/CppEncranger/*.* temp_zip/Classes/CppEncranger
cp ../../Classes/CppFuzzy_equal_to/*.* temp_zip/Classes/CppFuzzy_equal_to
cp ../../Classes/CppLoopReader/*.* temp_zip/Classes/CppLoopReader
cp ../../Classes/CppNewick/*.* temp_zip/Classes/CppNewick
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppTwoDigitNewick/*.* temp_zip/Classes/CppTwoDigitNewick
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp ../../Tools/ToolTestTwoDigitNewick/*.* temp_zip/Tools/ToolTestTwoDigitNewick

FILENAME=ToolTestTwoDigitNewickSource_2_4
ZIP_FILENAME=$FILENAME".zip"

#echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Libraries
#zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME


echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppAssert/*.*
rm temp_zip/Classes/CppBinaryNewickVector/*.*
rm temp_zip/Classes/CppEncranger/*.*
rm temp_zip/Classes/CppFuzzy_equal_to/*.*
rm temp_zip/Classes/CppLoopReader/*.*
rm temp_zip/Classes/CppNewick/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppTwoDigitNewick/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppAssert
rmdir temp_zip/Classes/CppBinaryNewickVector
rmdir temp_zip/Classes/CppEncranger
rmdir temp_zip/Classes/CppFuzzy_equal_to
rmdir temp_zip/Classes/CppLoopReader
rmdir temp_zip/Classes/CppNewick
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppTwoDigitNewick
rmdir temp_zip/Classes/CppWtAboutDialog
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
