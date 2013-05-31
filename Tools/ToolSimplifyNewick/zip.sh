#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppNewick
#     * CppNewickVector
#     * CppQtAboutDialog
#     * CppTrace
#   * Libraries
#     * bigint-2010.04.30
#   * Tools
#    * ToolSimplifyNewick
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppNewick
mkdir temp_zip/Classes/CppNewickVector
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolSimplifyNewick

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppNewick/*.* temp_zip/Classes/CppNewick
cp ../../Classes/CppNewickVector/*.* temp_zip/Classes/CppNewickVector
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp ../../Tools/ToolSimplifyNewick/*.* temp_zip/Tools/ToolSimplifyNewick

echo "Compressing files"
cd temp_zip

zip -r ToolSimplifyNewickSource_2_0 Classes
zip -r ToolSimplifyNewickSource_2_0 Libraries
zip -r ToolSimplifyNewickSource_2_0 Tools
cd ..
cp temp_zip/ToolSimplifyNewickSource_2_0.zip ToolSimplifyNewickSource_2_0.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppNewick/*.*
rm temp_zip/Classes/CppNewickVector/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppNewick
rmdir temp_zip/Classes/CppNewickVector
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes
#Libraries
rm temp_zip/Libraries/bigint-2010.04.30/*.*
rmdir temp_zip/Libraries/bigint-2010.04.30
rmdir temp_zip/Libraries
#Tools
rm temp_zip/Tools/ToolSimplifyNewick/*.*
rmdir temp_zip/Tools/ToolSimplifyNewick
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
