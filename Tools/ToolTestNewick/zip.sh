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
#     * CppLoopReader
#     * CppManyDigitNewick
#     * CppMultiVector
#     * CppNewick
#     * CppNewickRavindran
#     * CppNewickVector
#     * CppQtAboutDialog
#     * CppSortedBinaryNewickVector
#     * CppTrace
#     * CppTwoDigitNewick
#     * CppWtAboutDialog
#   * Libraries
#     * bigint-2010.04.30
#   * Tools
#    * ToolTestNewick
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppAssert
mkdir temp_zip/Classes/CppBinaryNewickVector
mkdir temp_zip/Classes/CppEncranger
mkdir temp_zip/Classes/CppLoopReader
mkdir temp_zip/Classes/CppManyDigitNewick
mkdir temp_zip/Classes/CppMultiVector
mkdir temp_zip/Classes/CppNewick
mkdir temp_zip/Classes/CppNewickRavindran
mkdir temp_zip/Classes/CppNewickVector
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppSortedBinaryNewickVector
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppTwoDigitNewick
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestNewick

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppAssert/*.* temp_zip/Classes/CppAssert
cp ../../Classes/CppBinaryNewickVector/*.* temp_zip/Classes/CppBinaryNewickVector
cp ../../Classes/CppEncranger/*.* temp_zip/Classes/CppEncranger
cp ../../Classes/CppLoopReader/*.* temp_zip/Classes/CppLoopReader
cp ../../Classes/CppManyDigitNewick/*.* temp_zip/Classes/CppManyDigitNewick
cp ../../Classes/CppMultiVector/*.* temp_zip/Classes/CppMultiVector
cp ../../Classes/CppNewick/*.* temp_zip/Classes/CppNewick
cp ../../Classes/CppNewickRavindran/*.* temp_zip/Classes/CppNewickRavindran
cp ../../Classes/CppNewickVector/*.* temp_zip/Classes/CppNewickVector
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppSortedBinaryNewickVector/*.* temp_zip/Classes/CppSortedBinaryNewickVector
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppTwoDigitNewick/*.* temp_zip/Classes/CppTwoDigitNewick
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp ../../Tools/ToolTestNewick/*.* temp_zip/Tools/ToolTestNewick

echo "Compressing files"
cd temp_zip

zip -r ToolTestNewickSource_1_0 Classes
zip -r ToolTestNewickSource_1_0 Libraries
zip -r ToolTestNewickSource_1_0 Tools

echo "Copying zipped file from temp folder to this folder"

cd ..
cp temp_zip/ToolTestNewickSource_1_0.zip ToolTestNewickSource_1_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppAssert/*.*
rm temp_zip/Classes/CppBinaryNewickVector/*.*
rm temp_zip/Classes/CppEncranger/*.*
rm temp_zip/Classes/CppLoopReader/*.*
rm temp_zip/Classes/CppManyDigitNewick/*.*
rm temp_zip/Classes/CppMultiVector/*.*
rm temp_zip/Classes/CppNewick/*.*
rm temp_zip/Classes/CppNewickRavindran/*.*
rm temp_zip/Classes/CppNewickVector/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppSortedBinaryNewickVector/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppTwoDigitNewick/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppAssert
rmdir temp_zip/Classes/CppBinaryNewickVector
rmdir temp_zip/Classes/CppEncranger
rmdir temp_zip/Classes/CppLoopReader
rmdir temp_zip/Classes/CppManyDigitNewick
rmdir temp_zip/Classes/CppMultiVector
rmdir temp_zip/Classes/CppNewick
rmdir temp_zip/Classes/CppNewickRavindran
rmdir temp_zip/Classes/CppNewickVector
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppSortedBinaryNewickVector
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppTwoDigitNewick
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes
#Libraries
rm temp_zip/Libraries/bigint-2010.04.30/*.*
rmdir temp_zip/Libraries/bigint-2010.04.30
rmdir temp_zip/Libraries
#Tools
rm temp_zip/Tools/ToolTestNewick/*.*
rmdir temp_zip/Tools/ToolTestNewick
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
