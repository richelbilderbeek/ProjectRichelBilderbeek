#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppConnectThree
#    * CppWtAboutDialog
#    * CppWtConnectThreeWidget
#  * Games
#    * GameConnectThree
#    * GameK3OpEenRij
echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppConnectThree
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtConnectThreeWidget
mkdir temp_zip/Games
mkdir temp_zip/Games/GameConnectThree
mkdir temp_zip/Games/GameK3OpEenRij

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppConnectThree/*.* temp_zip/Classes/CppConnectThree
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtConnectThreeWidget/*.* temp_zip/Classes/CppWtConnectThreeWidget
cp ../../Games/GameConnectThree/*.* temp_zip/Games/GameConnectThree
cp ../../Games/GameK3OpEenRij/*.* temp_zip/Games/GameK3OpEenRij

echo "Compressing files"
cd temp_zip
#Zip the folders recursively in the zip file
zip -r GameK3OpEenRij_5_0 Classes
zip -r GameK3OpEenRij_5_0 Games
cd ..
cp temp_zip/GameK3OpEenRij_5_0.zip GameK3OpEenRij_5_0.zip

echo "Cleaning up"

echo "Cleaning up Classes"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppConnectThree/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtConnectThreeWidget/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppConnectThree
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtConnectThreeWidget
rmdir temp_zip/Classes

echo "Cleaning up Games"
rm temp_zip/Games/GameK3OpEenRij/*.*
rm temp_zip/Games/GameConnectThree/*.*
rmdir temp_zip/Games/GameConnectThree
rmdir temp_zip/Games/GameK3OpEenRij
rmdir temp_zip/Games

rm temp_zip/*.*
rmdir temp_zip
echo "Done"
