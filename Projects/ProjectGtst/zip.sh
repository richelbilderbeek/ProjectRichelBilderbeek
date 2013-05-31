#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#    * CppCopy_if
#    * CppCounter
#    * CppFuzzy_equal_to
#    * CppIpAddress
#    * CppLed
#    * CppLedWidget
#    * CppMultipleChoiceQuestion
#    * CppMultipleChoiceQuestionDialog
#    * CppOpenQuestion
#    * CppOpenQuestionDialog
#    * CppQuestion
#    * CppQuestionDialog
#    * CppRainbow
#    * CppRectangle
#    * CppShape
#    * CppShapeWidget
#    * CppStopwatch
#    * CppSurvey
#    * CppTrace
#    * CppWidget
#    * CppWtAboutDialog
#    * CppWtAutoConfig
#    * CppWtGroupWidget
#    * CppWtLedWidget
#    * CppWtMultipleChoiceQuestionDialog
#    * CppWtOpenQuestionDialog
#    * CppWtQuestionDialog
#    * CppWtSelectFileDialog
#    * CppWtServerPusher
#    * CppWtShapeGroupWidget
#    * CppWtShapeWidget
#    * CppWtTimedServerPusher
#  * Libraries
#    * fparser4.4.3
#      * extrasrc
#  * Projects
#    * ProjectGtst
echo "Creating a sloccount file"
sloccount ../ProjectGtst > ProjectGtstSloccount.txt

echo "Creating documentation"
doxygen doxygen_config.txt

echo "Converting DIA to PNG"
dia --filter=png ProjectGtstArchitectureServer.dia
dia --filter=png ProjectGtstArchitectureMenuDialog.dia

echo "Converting ProjectGtstToDo.odt to ProjectGtstToDo.pdf (for Windows users)"
unoconv -f pdf ProjectGtstToDo.odt

echo "Removing user information"
rm ProjectGtst.pro.user

echo "Removing old log files"
rm log*.txt

echo "Removing old parameter files"
rm parameters*.txt

echo "Removing old temporary"
rm tmp.txt

echo "Removing old output trace file"
rm trace_out.txt

echo "Removing XML files"
rm *.xml

echo "Removing some temp files from other tools"
rm copy.txt
rm tmp.txt

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppCopy_if
mkdir temp_zip/Classes/CppCounter
mkdir temp_zip/Classes/CppFuzzy_equal_to
mkdir temp_zip/Classes/CppIpAddress
mkdir temp_zip/Classes/CppLed
mkdir temp_zip/Classes/CppLedWidget
mkdir temp_zip/Classes/CppMultipleChoiceQuestion
mkdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppOpenQuestion
mkdir temp_zip/Classes/CppOpenQuestionDialog
mkdir temp_zip/Classes/CppQuestion
mkdir temp_zip/Classes/CppQuestionDialog
mkdir temp_zip/Classes/CppRainbow
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppShape
mkdir temp_zip/Classes/CppShapeWidget
mkdir temp_zip/Classes/CppStopwatch
mkdir temp_zip/Classes/CppSurvey
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtGroupWidget
mkdir temp_zip/Classes/CppWtLedWidget
mkdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppWtOpenQuestionDialog
mkdir temp_zip/Classes/CppWtQuestionDialog
mkdir temp_zip/Classes/CppWtSelectFileDialog
mkdir temp_zip/Classes/CppWtServerPusher
mkdir temp_zip/Classes/CppWtShapeGroupWidget
mkdir temp_zip/Classes/CppWtShapeWidget
mkdir temp_zip/Classes/CppWtTimedServerPusher
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/fparser4.4.3
mkdir temp_zip/Libraries/fparser4.4.3/extrasrc
mkdir temp_zip/Projects
mkdir temp_zip/Projects/ProjectGtst

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppCopy_if/*.* temp_zip/Classes/CppCopy_if
cp ../../Classes/CppCounter/*.* temp_zip/Classes/CppCounter
cp ../../Classes/CppFuzzy_equal_to/*.* temp_zip/Classes/CppFuzzy_equal_to
cp ../../Classes/CppIpAddress/*.* temp_zip/Classes/CppIpAddress
cp ../../Classes/CppLed/*.* temp_zip/Classes/CppLed
cp ../../Classes/CppLedWidget/*.* temp_zip/Classes/CppLedWidget
cp ../../Classes/CppMultipleChoiceQuestion/*.* temp_zip/Classes/CppMultipleChoiceQuestion
cp ../../Classes/CppMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppMultipleChoiceQuestionDialog
cp ../../Classes/CppOpenQuestion/*.* temp_zip/Classes/CppOpenQuestion
cp ../../Classes/CppOpenQuestionDialog/*.* temp_zip/Classes/CppOpenQuestionDialog
cp ../../Classes/CppQuestion/*.* temp_zip/Classes/CppQuestion
cp ../../Classes/CppQuestionDialog/*.* temp_zip/Classes/CppQuestionDialog
cp ../../Classes/CppRainbow/*.* temp_zip/Classes/CppRainbow
cp ../../Classes/CppRectangle/*.* temp_zip/Classes/CppRectangle
cp ../../Classes/CppShape/*.* temp_zip/Classes/CppShape
cp ../../Classes/CppShapeWidget/*.* temp_zip/Classes/CppShapeWidget
cp ../../Classes/CppStopwatch/*.* temp_zip/Classes/CppStopwatch
cp ../../Classes/CppSurvey/*.* temp_zip/Classes/CppSurvey
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWidget/*.* temp_zip/Classes/CppWidget
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtGroupWidget/*.* temp_zip/Classes/CppWtGroupWidget
cp ../../Classes/CppWtLedWidget/*.* temp_zip/Classes/CppWtLedWidget
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
cp ../../Classes/CppWtOpenQuestionDialog/*.* temp_zip/Classes/CppWtOpenQuestionDialog
cp ../../Classes/CppWtQuestionDialog/*.* temp_zip/Classes/CppWtQuestionDialog
cp ../../Classes/CppWtSelectFileDialog/*.* temp_zip/Classes/CppWtSelectFileDialog
cp ../../Classes/CppWtServerPusher/*.* temp_zip/Classes/CppWtServerPusher
cp ../../Classes/CppWtShapeGroupWidget/*.* temp_zip/Classes/CppWtShapeGroupWidget
cp ../../Classes/CppWtShapeWidget/*.* temp_zip/Classes/CppWtShapeWidget
cp ../../Classes/CppWtTimedServerPusher/*.* temp_zip/Classes/CppWtTimedServerPusher

cp ../../Libraries/fparser4.4.3/*.* temp_zip/Libraries/fparser4.4.3
cp ../../Libraries/fparser4.4.3/extrasrc/*.* temp_zip/Libraries/fparser4.4.3/extrasrc

cp ../../Projects/ProjectGtst/*.* temp_zip/Projects/ProjectGtst

FILENAME=ProjectGtstSource_1_2
ZIP_FILENAME=$FILENAME".zip"

echo "Remove previous zip"
rm $ZIP_FILENAME

#echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Libraries
zip -r $FILENAME Projects
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppCopy_if/*.*
rm temp_zip/Classes/CppCounter/*.*
rm temp_zip/Classes/CppFuzzy_equal_to/*.*
rm temp_zip/Classes/CppIpAddress/*.*
rm temp_zip/Classes/CppLed/*.*
rm temp_zip/Classes/CppLedWidget/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestion/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppOpenQuestion/*.*
rm temp_zip/Classes/CppOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQuestion/*.*
rm temp_zip/Classes/CppQuestionDialog/*.*
rm temp_zip/Classes/CppRainbow/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppShape/*.*
rm temp_zip/Classes/CppShapeWidget/*.*
rm temp_zip/Classes/CppStopwatch/*.*
rm temp_zip/Classes/CppSurvey/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtGroupWidget/*.*
rm temp_zip/Classes/CppWtLedWidget/*.*
rm temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppWtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppWtQuestionDialog/*.*
rm temp_zip/Classes/CppWtSelectFileDialog/*.*
rm temp_zip/Classes/CppWtServerPusher/*.*
rm temp_zip/Classes/CppWtShapeGroupWidget/*.*
rm temp_zip/Classes/CppWtShapeWidget/*.*
rm temp_zip/Classes/CppWtTimedServerPusher/*.*
rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppCopy_if
rmdir temp_zip/Classes/CppCounter
rmdir temp_zip/Classes/CppFuzzy_equal_to
rmdir temp_zip/Classes/CppIpAddress
rmdir temp_zip/Classes/CppLed
rmdir temp_zip/Classes/CppLedWidget
rmdir temp_zip/Classes/CppMultipleChoiceQuestion
rmdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppOpenQuestion
rmdir temp_zip/Classes/CppOpenQuestionDialog
rmdir temp_zip/Classes/CppQuestion
rmdir temp_zip/Classes/CppQuestionDialog
rmdir temp_zip/Classes/CppRainbow
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppShape
rmdir temp_zip/Classes/CppShapeWidget
rmdir temp_zip/Classes/CppStopwatch
rmdir temp_zip/Classes/CppSurvey
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtGroupWidget
rmdir temp_zip/Classes/CppWtLedWidget
rmdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppWtOpenQuestionDialog
rmdir temp_zip/Classes/CppWtQuestionDialog
rmdir temp_zip/Classes/CppWtSelectFileDialog
rmdir temp_zip/Classes/CppWtServerPusher
rmdir temp_zip/Classes/CppWtShapeGroupWidget
rmdir temp_zip/Classes/CppWtShapeWidget
rmdir temp_zip/Classes/CppWtTimedServerPusher
rmdir temp_zip/Classes

rm temp_zip/Libraries/fparser4.4.3/extrasrc/*.*
rm temp_zip/Libraries/fparser4.4.3/*.*
rmdir temp_zip/Libraries/fparser4.4.3/extrasrc
rmdir temp_zip/Libraries/fparser4.4.3
rmdir temp_zip/Libraries

rm temp_zip/Projects/ProjectGtst/*.*
rmdir temp_zip/Projects/ProjectGtst
rmdir temp_zip/Projects

rm temp_zip/*.*
rmdir temp_zip
echo "Done"
