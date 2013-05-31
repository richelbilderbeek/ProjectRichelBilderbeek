#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppQtAboutDialog
#    * CppQtTicTacToeWidget
#    * CppTicTacToe
#    * CppWtAboutDialog
#    * CppWtAutoConfig
#    * CppWtTicTacToeWidget
#  * Games
#    * GameTicTacToe
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtTicTacToeWidget
mkdir temp_zip/Classes/CppTicTacToe
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtTicTacToeWidget
mkdir temp_zip/Games
mkdir temp_zip/Games/GameTicTacToe

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppQtAboutDialog/*.* temp_zip/Classes/CppQtAboutDialog
cp ../../Classes/CppQtTicTacToeWidget/*.* temp_zip/Classes/CppQtTicTacToeWidget
cp ../../Classes/CppTicTacToe/*.* temp_zip/Classes/CppTicTacToe
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtTicTacToeWidget/*.* temp_zip/Classes/CppWtTicTacToeWidget
cp ../../Games/GameTicTacToe/*.* temp_zip/Games/GameTicTacToe

echo "Compressing files"
cd temp_zip
zip -r GameTicTacToeSource_1_5 Classes
zip -r GameTicTacToeSource_1_5 Games
cd ..
cp temp_zip/GameTicTacToeSource_1_5.zip GameTicTacToeSource_1_5.zip

echo "Cleaning up"

#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtTicTacToeWidget/*.*
rm temp_zip/Classes/CppTicTacToe/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtTicTacToeWidget/*.*

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtTicTacToeWidget
rmdir temp_zip/Classes/CppTicTacToe
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtTicTacToeWidget
rmdir temp_zip/Classes

#Games
rm temp_zip/Games/GameTicTacToe/*.*
rmdir temp_zip/Games/GameTicTacToe
rmdir temp_zip/Games
rm temp_zip/*.*
rmdir temp_zip
echo "Done"
