#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppConnectThree
#    * CppConnectThreeWidget
#    * CppQtAboutDialog
#    * CppQtConnectThreeWidget
#    * CppTrace
#    * CppWtAboutDialog
#    * CppWtAutoConfig
#    * CppWtConnectThreeWidget
#  * Games
#    * GameConnectThree
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppConnectThree
mkdir temp_zip/Classes/CppConnectThreeWidget
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtConnectThreeWidget
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtConnectThreeWidget
mkdir temp_zip/Games
mkdir temp_zip/Games/GameConnectThree

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppConnectThree/*.* temp_zip/Classes/CppConnectThree
cp ../../Classes/CppConnectThreeWidget/*.* temp_zip/Classes/CppConnectThreeWidget
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtConnectThreeWidget/*.* temp_zip/Classes/CppQtConnectThreeWidget
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtConnectThreeWidget/*.* temp_zip/Classes/CppWtConnectThreeWidget
cp ../../Games/GameConnectThree/*.* temp_zip/Games/GameConnectThree

echo "Compressing files"
cd temp_zip
#Zip the folders recursively in the zip file
zip -r GameConnectThreeSource_6_2 Classes
zip -r GameConnectThreeSource_6_2 Games
cd ..
cp temp_zip/GameConnectThreeSource_6_2.zip GameConnectThreeSource_6_2.zip

echo "Cleaning up"

echo "Cleaning up Classes"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppConnectThree/*.*
rm temp_zip/Classes/CppConnectThreeWidget/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtConnectThreeWidget/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtConnectThreeWidget/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppConnectThree
rmdir temp_zip/Classes/CppConnectThreeWidget
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtConnectThreeWidget
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtConnectThreeWidget
rmdir temp_zip/Classes

echo "Cleaning up Games"
rm temp_zip/Games/GameConnectThree/*.*
rmdir temp_zip/Games/GameConnectThree
rmdir temp_zip/Games

rm temp_zip/*.*
rmdir temp_zip
echo "Done"
