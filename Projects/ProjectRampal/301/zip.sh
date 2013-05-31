#!/bin/sh
#pack2port packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppStopwatch
#   * Libraries
#     * bigint-2010.04.30
#   * Projects
#     * ProjectRampal
#       * 300                    
#   * Tools
#     * ToolTestNewickVector    
#     * ToolTestTwoDigitNewick
echo "Removing old zip archive"
rm 300.zip
rm *.o
rm ProjectRampalTest.pro.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppStopwatch
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Projects
mkdir temp_zip/Projects/ProjectRampal
mkdir temp_zip/Projects/ProjectRampal/300
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestNewickVector
mkdir temp_zip/Tools/ToolTestTwoDigitNewick

echo "Copying files"
cp ../../../Classes/CppStopwatch/*.* temp_zip/Classes/CppStopwatch
cp ../../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp *.* temp_zip/Projects/ProjectRampal/300
cp ../../../Tools/ToolTestNewickVector/*.* temp_zip/Tools/ToolTestNewickVector
cp ../../../Tools/ToolTestTwoDigitNewick/*.* temp_zip/Tools/ToolTestTwoDigitNewick

echo "Compressing files"
cd temp_zip
zip -r 300 Classes
zip -r 300 Libraries
zip -r 300 Projects
zip -r 300 Tools
cd ..
cp temp_zip/300.zip 300.zip

echo "Cleaning up"
#Classes
rm temp_zip/Classes/CppStopwatch/*.*
rmdir temp_zip/Classes/CppStopwatch
rmdir temp_zip/Classes
#Libraries
rm temp_zip/Libraries/bigint-2010.04.30/*.*
rmdir temp_zip/Libraries/bigint-2010.04.30
rmdir temp_zip/Libraries
#Projects
rm temp_zip/Projects/ProjectRampal/300/*.*
rmdir temp_zip/Projects/ProjectRampal/300
rmdir temp_zip/Projects/ProjectRampal
rmdir temp_zip/Projects
#Tools
rm temp_zip/Tools/ToolTestNewickVector/*.*
rm temp_zip/Tools/ToolTestTwoDigitNewick/*.*
rmdir temp_zip/Tools/ToolTestNewickVector
rmdir temp_zip/Tools/ToolTestTwoDigitNewick
rmdir temp_zip/Tools
#temp_zip
rm temp_zip/*.*
rmdir temp_zip

echo "Done"
