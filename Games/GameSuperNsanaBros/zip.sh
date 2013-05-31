#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppWtAboutDialog
#    * CppQtAboutDialog
#  * Games
#    * GameSuperNsanaBros
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Games
mkdir temp_zip/Games/GameSuperNsanaBros

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Games/GameSuperNsanaBros/*.* temp_zip/Games/GameSuperNsanaBros

echo "Compressing files"
cd temp_zip
#Zip the folder Classes recursively
zip -r GameSuperNsanaBrosSource_0_1 Classes
zip -r GameSuperNsanaBrosSource_0_1 Games
cd ..
cp temp_zip/GameSuperNsanaBrosSource_0_1.zip GameSuperNsanaBrosSource_0_1.zip

echo "Cleaning up"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes
rm temp_zip/Games/GameSuperNsanaBros/*.*
rmdir temp_zip/Games/GameSuperNsanaBros
rmdir temp_zip/Games
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
