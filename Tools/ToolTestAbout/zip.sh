#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#  * Classes
#    * CppAbout
#  * Tools
#    * ToolTestAbout

FOLDERNAME=ProjectWtWebsite
FILENAME=$FOLDERNAME"Source_0_38"
ZIP_FILENAME=$FILENAME".zip"
HTM_FILENAME=$FILENAME".htm"

rm *.user
rm $ZIP_FILENAME
rm $HTM_FILENAME

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppAsciiArter
mkdir temp_zip/Classes/CppAssert
mkdir temp_zip/Classes/CppBinaryNewickVector
mkdir temp_zip/Classes/CppConnectThree
mkdir temp_zip/Classes/CppConnectThreeWidget
mkdir temp_zip/Classes/CppCopy_if
mkdir temp_zip/Classes/CppCounter
mkdir temp_zip/Classes/CppDial
mkdir temp_zip/Classes/CppDialWidget
mkdir temp_zip/Classes/CppEncranger
mkdir temp_zip/Classes/CppExercise
mkdir temp_zip/Classes/CppFuzzy_equal_to
mkdir temp_zip/Classes/CppIpAddress
mkdir temp_zip/Classes/CppLed
mkdir temp_zip/Classes/CppLedWidget
mkdir temp_zip/Classes/CppLoopReader
mkdir temp_zip/Classes/CppManyDigitNewick
mkdir temp_zip/Classes/CppMultipleChoiceQuestion
mkdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppMultiVector
mkdir temp_zip/Classes/CppMysteryMachine
mkdir temp_zip/Classes/CppMysteryMachineWidget
mkdir temp_zip/Classes/CppNewick
mkdir temp_zip/Classes/CppNewickVector
mkdir temp_zip/Classes/CppOpenQuestion
mkdir temp_zip/Classes/CppOpenQuestionDialog
mkdir temp_zip/Classes/CppProFile
mkdir temp_zip/Classes/CppQuestion
mkdir temp_zip/Classes/CppQuestionDialog
mkdir temp_zip/Classes/CppRainbow
mkdir temp_zip/Classes/CppRandomCode
mkdir temp_zip/Classes/CppRectangle
mkdir temp_zip/Classes/CppRubiksClock
mkdir temp_zip/Classes/CppRubiksClockWidget
mkdir temp_zip/Classes/CppShape
mkdir temp_zip/Classes/CppShapeWidget
mkdir temp_zip/Classes/CppShinyButton
mkdir temp_zip/Classes/CppShinyButtonWidget
mkdir temp_zip/Classes/CppSortedBinaryNewickVector
mkdir temp_zip/Classes/CppStopwatch
mkdir temp_zip/Classes/CppTicTacToe
mkdir temp_zip/Classes/CppToggleButton
mkdir temp_zip/Classes/CppToggleButtonWidget
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppTwoDigitNewick
mkdir temp_zip/Classes/CppWidget
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtBroadcastServer
mkdir temp_zip/Classes/CppWtConnectThreeWidget
mkdir temp_zip/Classes/CppWtDialWidget
mkdir temp_zip/Classes/CppWtEntrance
mkdir temp_zip/Classes/CppWtExercise
mkdir temp_zip/Classes/CppWtGroupWidget
mkdir temp_zip/Classes/CppWtLedWidget
mkdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppWtMysteryMachineWidget
mkdir temp_zip/Classes/CppWtOpenQuestionDialog
mkdir temp_zip/Classes/CppWtQuestionDialog
mkdir temp_zip/Classes/CppWtRubiksClockWidget
mkdir temp_zip/Classes/CppWtSelectFileDialog
mkdir temp_zip/Classes/CppWtServerPusher
mkdir temp_zip/Classes/CppWtShapeGroupWidget
mkdir temp_zip/Classes/CppWtShapeWidget
mkdir temp_zip/Classes/CppWtShinyButtonWidget
mkdir temp_zip/Classes/CppWtTicTacToeWidget
mkdir temp_zip/Classes/CppWtTimedServerPusher
mkdir temp_zip/Classes/CppWtToggleButtonWidget
mkdir temp_zip/Games
mkdir temp_zip/Games/GameConnectThree
mkdir temp_zip/Games/GameRubiksClock
mkdir temp_zip/Games/GameTicTacToe
mkdir temp_zip/Libraries
mkdir temp_zip/Libraries/bigint-2010.04.30
mkdir temp_zip/Libraries/fparser4.4.3
mkdir temp_zip/Libraries/fparser4.4.3/extrasrc
mkdir temp_zip/Projects
mkdir temp_zip/Projects/ProjectGtst
mkdir temp_zip/Projects/ProjectWtWebsite
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolCodeToHtml
mkdir temp_zip/Tools/ToolHometrainer
mkdir temp_zip/Tools/ToolRandomCode
mkdir temp_zip/Tools/ToolSimMysteryMachine
mkdir temp_zip/Tools/ToolTestAsciiArter
mkdir temp_zip/Tools/ToolTestDial
mkdir temp_zip/Tools/ToolTestEncranger
mkdir temp_zip/Tools/ToolTestEntrance
mkdir temp_zip/Tools/ToolTestExercise
mkdir temp_zip/Tools/ToolTestFunctionParser
mkdir temp_zip/Tools/ToolTestGroupWidget
mkdir temp_zip/Tools/ToolTestLed
mkdir temp_zip/Tools/ToolTestNewickVector
mkdir temp_zip/Tools/ToolTestQuestion
mkdir temp_zip/Tools/ToolTestSelectFileDialog
mkdir temp_zip/Tools/ToolTestServerPusher
mkdir temp_zip/Tools/ToolTestShape
mkdir temp_zip/Tools/ToolTestShinyButton
mkdir temp_zip/Tools/ToolTestTimedServerPusher
mkdir temp_zip/Tools/ToolTestToggleButton
mkdir temp_zip/Tools/ToolTestTwoDigitNewick
mkdir temp_zip/Tools/ToolTimePoll

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppAsciiArter/*.* temp_zip/Classes/CppAsciiArter
cp ../../Classes/CppAssert/*.* temp_zip/Classes/CppAssert
cp ../../Classes/CppBinaryNewickVector/*.* temp_zip/Classes/CppBinaryNewickVector
cp ../../Classes/CppConnectThree/*.* temp_zip/Classes/CppConnectThree
cp ../../Classes/CppConnectThreeWidget/*.* temp_zip/Classes/CppConnectThreeWidget
cp ../../Classes/CppCopy_if/*.* temp_zip/Classes/CppCopy_if
cp ../../Classes/CppCounter/*.* temp_zip/Classes/CppCounter
cp ../../Classes/CppDial/*.* temp_zip/Classes/CppDial
cp ../../Classes/CppDialWidget/*.* temp_zip/Classes/CppDialWidget
cp ../../Classes/CppEncranger/*.* temp_zip/Classes/CppEncranger
cp ../../Classes/CppExercise/*.* temp_zip/Classes/CppExercise
cp ../../Classes/CppFuzzy_equal_to/*.* temp_zip/Classes/CppFuzzy_equal_to
cp ../../Classes/CppIpAddress/*.* temp_zip/Classes/CppIpAddress
cp ../../Classes/CppLed/*.* temp_zip/Classes/CppLed
cp ../../Classes/CppLedWidget/*.* temp_zip/Classes/CppLedWidget
cp ../../Classes/CppLoopReader/*.* temp_zip/Classes/CppLoopReader
cp ../../Classes/CppManyDigitNewick/*.* temp_zip/Classes/CppManyDigitNewick
cp ../../Classes/CppMultipleChoiceQuestion/*.* temp_zip/Classes/CppMultipleChoiceQuestion
cp ../../Classes/CppMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppMultipleChoiceQuestionDialog
cp ../../Classes/CppMultiVector/*.* temp_zip/Classes/CppMultiVector
cp ../../Classes/CppMysteryMachine/*.* temp_zip/Classes/CppMysteryMachine
cp ../../Classes/CppMysteryMachineWidget/*.* temp_zip/Classes/CppMysteryMachineWidget
cp ../../Classes/CppNewick/*.* temp_zip/Classes/CppNewick
cp ../../Classes/CppNewickVector/*.* temp_zip/Classes/CppNewickVector
cp ../../Classes/CppOpenQuestion/*.* temp_zip/Classes/CppOpenQuestion
cp ../../Classes/CppOpenQuestionDialog/*.* temp_zip/Classes/CppOpenQuestionDialog
cp ../../Classes/CppProFile/*.* temp_zip/Classes/CppProFile
cp ../../Classes/CppQuestion/*.* temp_zip/Classes/CppQuestion
cp ../../Classes/CppQuestionDialog/*.* temp_zip/Classes/CppQuestionDialog
cp ../../Classes/CppRainbow/*.* temp_zip/Classes/CppRainbow
cp ../../Classes/CppRandomCode/*.* temp_zip/Classes/CppRandomCode
cp ../../Classes/CppRectangle/*.* temp_zip/Classes/CppRectangle
cp ../../Classes/CppRubiksClock/*.* temp_zip/Classes/CppRubiksClock
cp ../../Classes/CppRubiksClockWidget/*.* temp_zip/Classes/CppRubiksClockWidget
cp ../../Classes/CppShape/*.* temp_zip/Classes/CppShape
cp ../../Classes/CppShapeWidget/*.* temp_zip/Classes/CppShapeWidget
cp ../../Classes/CppShinyButton/*.* temp_zip/Classes/CppShinyButton
cp ../../Classes/CppShinyButtonWidget/*.* temp_zip/Classes/CppShinyButtonWidget
cp ../../Classes/CppSortedBinaryNewickVector/*.* temp_zip/Classes/CppSortedBinaryNewickVector
cp ../../Classes/CppStopwatch/*.* temp_zip/Classes/CppStopwatch
cp ../../Classes/CppTicTacToe/*.* temp_zip/Classes/CppTicTacToe
cp ../../Classes/CppToggleButton/*.* temp_zip/Classes/CppToggleButton
cp ../../Classes/CppToggleButtonWidget/*.* temp_zip/Classes/CppToggleButtonWidget
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppTwoDigitNewick/*.* temp_zip/Classes/CppTwoDigitNewick
cp ../../Classes/CppWidget/*.* temp_zip/Classes/CppWidget
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtBroadcastServer/*.* temp_zip/Classes/CppWtBroadcastServer
cp ../../Classes/CppWtConnectThreeWidget/*.* temp_zip/Classes/CppWtConnectThreeWidget
cp ../../Classes/CppWtDialWidget/*.* temp_zip/Classes/CppWtDialWidget
cp ../../Classes/CppWtEntrance/*.* temp_zip/Classes/CppWtEntrance
cp ../../Classes/CppWtExercise/*.* temp_zip/Classes/CppWtExercise
cp ../../Classes/CppWtGroupWidget/*.* temp_zip/Classes/CppWtGroupWidget
cp ../../Classes/CppWtLedWidget/*.* temp_zip/Classes/CppWtLedWidget
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
cp ../../Classes/CppWtMysteryMachineWidget/*.* temp_zip/Classes/CppWtMysteryMachineWidget
cp ../../Classes/CppWtOpenQuestionDialog/*.* temp_zip/Classes/CppWtOpenQuestionDialog
cp ../../Classes/CppWtQuestionDialog/*.* temp_zip/Classes/CppWtQuestionDialog
cp ../../Classes/CppWtRubiksClockWidget/*.* temp_zip/Classes/CppWtRubiksClockWidget
cp ../../Classes/CppWtSelectFileDialog/*.* temp_zip/Classes/CppWtSelectFileDialog
cp ../../Classes/CppWtServerPusher/*.* temp_zip/Classes/CppWtServerPusher
cp ../../Classes/CppWtShapeGroupWidget/*.* temp_zip/Classes/CppWtShapeGroupWidget
cp ../../Classes/CppWtShapeWidget/*.* temp_zip/Classes/CppWtShapeWidget
cp ../../Classes/CppWtShinyButtonWidget/*.* temp_zip/Classes/CppWtShinyButtonWidget
cp ../../Classes/CppWtTicTacToeWidget/*.* temp_zip/Classes/CppWtTicTacToeWidget
cp ../../Classes/CppWtTimedServerPusher/*.* temp_zip/Classes/CppWtTimedServerPusher
cp ../../Classes/CppWtToggleButtonWidget/*.* temp_zip/Classes/CppWtToggleButtonWidget

cp ../../Games/GameConnectThree/*.* temp_zip/Games/GameConnectThree
cp ../../Games/GameRubiksClock/*.* temp_zip/Games/GameRubiksClock
cp ../../Games/GameTicTacToe/*.* temp_zip/Games/GameTicTacToe

cp ../../Libraries/bigint-2010.04.30/*.* temp_zip/Libraries/bigint-2010.04.30
cp ../../Libraries/fparser4.4.3/*.* temp_zip/Libraries/fparser4.4.3
cp ../../Libraries/fparser4.4.3/extrasrc/*.* temp_zip/Libraries/fparser4.4.3/extrasrc

cp ../../Projects/ProjectGtst/*.* temp_zip/Projects/ProjectGtst
cp ../../Projects/ProjectWtWebsite/*.* temp_zip/Projects/ProjectWtWebsite

cp ../../Tools/ToolCodeToHtml/*.* temp_zip/Tools/ToolCodeToHtml
cp ../../Tools/ToolHometrainer/*.* temp_zip/Tools/ToolHometrainer
cp ../../Tools/ToolRandomCode/*.* temp_zip/Tools/ToolRandomCode
cp ../../Tools/ToolSimMysteryMachine/*.* temp_zip/Tools/ToolSimMysteryMachine
cp ../../Tools/ToolTestAsciiArter/*.* temp_zip/Tools/ToolTestAsciiArter
cp ../../Tools/ToolTestDial/*.* temp_zip/Tools/ToolTestDial
cp ../../Tools/ToolTestEncranger/*.* temp_zip/Tools/ToolTestEncranger
cp ../../Tools/ToolTestEntrance/*.* temp_zip/Tools/ToolTestEntrance
cp ../../Tools/ToolTestExercise/*.* temp_zip/Tools/ToolTestExercise
cp ../../Tools/ToolTestFunctionParser/*.* temp_zip/Tools/ToolTestFunctionParser
cp ../../Tools/ToolTestGroupWidget/*.* temp_zip/Tools/ToolTestGroupWidget
cp ../../Tools/ToolTestLed/*.* temp_zip/Tools/ToolTestLed
cp ../../Tools/ToolTestNewickVector/*.* temp_zip/Tools/ToolTestNewickVector
cp ../../Tools/ToolTestQuestion/*.* temp_zip/Tools/ToolTestQuestion
cp ../../Tools/ToolTestSelectFileDialog/*.* temp_zip/Tools/ToolTestSelectFileDialog
cp ../../Tools/ToolTestServerPusher/*.* temp_zip/Tools/ToolTestServerPusher
cp ../../Tools/ToolTestShape/*.* temp_zip/Tools/ToolTestShape
cp ../../Tools/ToolTestShinyButton/*.* temp_zip/Tools/ToolTestShinyButton
cp ../../Tools/ToolTestTimedServerPusher/*.* temp_zip/Tools/ToolTestTimedServerPusher
cp ../../Tools/ToolTestToggleButton/*.* temp_zip/Tools/ToolTestToggleButton
cp ../../Tools/ToolTestTwoDigitNewick/*.* temp_zip/Tools/ToolTestTwoDigitNewick
cp ../../Tools/ToolTimePoll/*.* temp_zip/Tools/ToolTimePoll

#echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Games
zip -r $FILENAME Libraries
zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Cleaning up Classes"
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppAsciiArter/*.*
rm temp_zip/Classes/CppAssert/*.*
rm temp_zip/Classes/CppBinaryNewickVector/*.*
rm temp_zip/Classes/CppConnectThree/*.*
rm temp_zip/Classes/CppConnectThreeWidget/*.*
rm temp_zip/Classes/CppCopy_if/*.*
rm temp_zip/Classes/CppCounter/*.*
rm temp_zip/Classes/CppDial/*.*
rm temp_zip/Classes/CppDialWidget/*.*
rm temp_zip/Classes/CppEncranger/*.*
rm temp_zip/Classes/CppExercise/*.*
rm temp_zip/Classes/CppFuzzy_equal_to/*.*
rm temp_zip/Classes/CppIpAddress/*.*
rm temp_zip/Classes/CppLed/*.*
rm temp_zip/Classes/CppLedWidget/*.*
rm temp_zip/Classes/CppLoopReader/*.*
rm temp_zip/Classes/CppManyDigitNewick/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestion/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppMultiVector/*.*
rm temp_zip/Classes/CppMysteryMachine/*.*
rm temp_zip/Classes/CppMysteryMachineWidget/*.*
rm temp_zip/Classes/CppNewick/*.*
rm temp_zip/Classes/CppNewickVector/*.*
rm temp_zip/Classes/CppOpenQuestion/*.*
rm temp_zip/Classes/CppOpenQuestionDialog/*.*
rm temp_zip/Classes/CppProFile/*.*
rm temp_zip/Classes/CppQuestion/*.*
rm temp_zip/Classes/CppQuestionDialog/*.*
rm temp_zip/Classes/CppRainbow/*.*
rm temp_zip/Classes/CppRandomCode/*.*
rm temp_zip/Classes/CppRectangle/*.*
rm temp_zip/Classes/CppRubiksClock/*.*
rm temp_zip/Classes/CppRubiksClockWidget/*.*
rm temp_zip/Classes/CppShape/*.*
rm temp_zip/Classes/CppShapeWidget/*.*
rm temp_zip/Classes/CppShinyButton/*.*
rm temp_zip/Classes/CppShinyButtonWidget/*.*
rm temp_zip/Classes/CppSortedBinaryNewickVector/*.*
rm temp_zip/Classes/CppStopwatch/*.*
rm temp_zip/Classes/CppTicTacToe/*.*
rm temp_zip/Classes/CppToggleButton/*.*
rm temp_zip/Classes/CppToggleButtonWidget/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppTwoDigitNewick/*.*
rm temp_zip/Classes/CppWidget/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtBroadcastServer/*.*
rm temp_zip/Classes/CppWtConnectThreeWidget/*.*
rm temp_zip/Classes/CppWtDialWidget/*.*
rm temp_zip/Classes/CppWtEntrance/*.*
rm temp_zip/Classes/CppWtExercise/*.*
rm temp_zip/Classes/CppWtGroupWidget/*.*
rm temp_zip/Classes/CppWtLedWidget/*.*
rm temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppWtMysteryMachineWidget/*.*
rm temp_zip/Classes/CppWtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppWtQuestionDialog/*.*
rm temp_zip/Classes/CppWtRubiksClockWidget/*.*
rm temp_zip/Classes/CppWtSelectFileDialog/*.*
rm temp_zip/Classes/CppWtServerPusher/*.*
rm temp_zip/Classes/CppWtShapeGroupWidget/*.*
rm temp_zip/Classes/CppWtShapeWidget/*.*
rm temp_zip/Classes/CppWtShinyButtonWidget/*.*
rm temp_zip/Classes/CppWtTicTacToeWidget/*.*
rm temp_zip/Classes/CppWtTimedServerPusher/*.*
rm temp_zip/Classes/CppWtToggleButtonWidget/*.*

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppAsciiArter
rmdir temp_zip/Classes/CppAssert
rmdir temp_zip/Classes/CppBinaryNewickVector
rmdir temp_zip/Classes/CppConnectThree
rmdir temp_zip/Classes/CppConnectThreeWidget
rmdir temp_zip/Classes/CppCopy_if
rmdir temp_zip/Classes/CppCounter
rmdir temp_zip/Classes/CppDial
rmdir temp_zip/Classes/CppDialWidget
rmdir temp_zip/Classes/CppEncranger
rmdir temp_zip/Classes/CppExercise
rmdir temp_zip/Classes/CppFuzzy_equal_to
rmdir temp_zip/Classes/CppIpAddress
rmdir temp_zip/Classes/CppLed
rmdir temp_zip/Classes/CppLedWidget
rmdir temp_zip/Classes/CppLoopReader
rmdir temp_zip/Classes/CppManyDigitNewick
rmdir temp_zip/Classes/CppMultipleChoiceQuestion
rmdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppMultiVector
rmdir temp_zip/Classes/CppMysteryMachine
rmdir temp_zip/Classes/CppMysteryMachineWidget
rmdir temp_zip/Classes/CppNewick
rmdir temp_zip/Classes/CppNewickVector
rmdir temp_zip/Classes/CppOpenQuestion
rmdir temp_zip/Classes/CppOpenQuestionDialog
rmdir temp_zip/Classes/CppProFile
rmdir temp_zip/Classes/CppQuestion
rmdir temp_zip/Classes/CppQuestionDialog
rmdir temp_zip/Classes/CppRainbow
rmdir temp_zip/Classes/CppRandomCode
rmdir temp_zip/Classes/CppRectangle
rmdir temp_zip/Classes/CppRubiksClock
rmdir temp_zip/Classes/CppRubiksClockWidget
rmdir temp_zip/Classes/CppShape
rmdir temp_zip/Classes/CppShapeWidget
rmdir temp_zip/Classes/CppShinyButton
rmdir temp_zip/Classes/CppShinyButtonWidget
rmdir temp_zip/Classes/CppSortedBinaryNewickVector
rmdir temp_zip/Classes/CppStopwatch
rmdir temp_zip/Classes/CppTicTacToe
rmdir temp_zip/Classes/CppToggleButton
rmdir temp_zip/Classes/CppToggleButtonWidget
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppTwoDigitNewick
rmdir temp_zip/Classes/CppWidget
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtBroadcastServer
rmdir temp_zip/Classes/CppWtConnectThreeWidget
rmdir temp_zip/Classes/CppWtDialWidget
rmdir temp_zip/Classes/CppWtEntrance
rmdir temp_zip/Classes/CppWtExercise
rmdir temp_zip/Classes/CppWtGroupWidget
rmdir temp_zip/Classes/CppWtLedWidget
rmdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppWtMysteryMachineWidget
rmdir temp_zip/Classes/CppWtOpenQuestionDialog
rmdir temp_zip/Classes/CppWtQuestionDialog
rmdir temp_zip/Classes/CppWtRubiksClockWidget
rmdir temp_zip/Classes/CppWtSelectFileDialog
rmdir temp_zip/Classes/CppWtServerPusher
rmdir temp_zip/Classes/CppWtShapeGroupWidget
rmdir temp_zip/Classes/CppWtShapeWidget
rmdir temp_zip/Classes/CppWtShinyButtonWidget
rmdir temp_zip/Classes/CppWtTicTacToeWidget
rmdir temp_zip/Classes/CppWtTimedServerPusher
rmdir temp_zip/Classes/CppWtToggleButtonWidget
rmdir temp_zip/Classes

echo "Cleaning up Libraries"
rm temp_zip/Libraries/bigint-2010.04.30/*.*
rm temp_zip/Libraries/fparser4.4.3/extrasrc/*.*
rm temp_zip/Libraries/fparser4.4.3/*.*
rmdir temp_zip/Libraries/bigint-2010.04.30
rmdir temp_zip/Libraries/fparser4.4.3/extrasrc
rmdir temp_zip/Libraries/fparser4.4.3
rmdir temp_zip/Libraries

echo "Cleaning up Projects"
rm temp_zip/Projects/ProjectGtst/*.*
rm temp_zip/Projects/ProjectWtWebsite/*.*
rmdir temp_zip/Projects/ProjectGtst
rmdir temp_zip/Projects/ProjectWtWebsite
rmdir temp_zip/Projects

echo "Cleaning up Games"
rm temp_zip/Games/GameConnectThree/*.*
rm temp_zip/Games/GameRubiksClock/*.*
rm temp_zip/Games/GameTicTacToe/*.*
rmdir temp_zip/Games/GameConnectThree
rmdir temp_zip/Games/GameRubiksClock
rmdir temp_zip/Games/GameTicTacToe
rmdir temp_zip/Games

echo "Cleaning up Tools"
rm temp_zip/Tools/ToolCodeToHtml/*.*
rm temp_zip/Tools/ToolHometrainer/*.*
rm temp_zip/Tools/ToolRandomCode/*.*
rm temp_zip/Tools/ToolSimMysteryMachine/*.*
rm temp_zip/Tools/ToolTestAsciiArter/*.*
rm temp_zip/Tools/ToolTestDial/*.*
rm temp_zip/Tools/ToolTestEncranger/*.*
rm temp_zip/Tools/ToolTestEntrance/*.*
rm temp_zip/Tools/ToolTestExercise/*.*
rm temp_zip/Tools/ToolTestFunctionParser/*.*
rm temp_zip/Tools/ToolTestGroupWidget/*.*
rm temp_zip/Tools/ToolTestLed/*.*
rm temp_zip/Tools/ToolTestNewickVector/*.*
rm temp_zip/Tools/ToolTestQuestion/*.*
rm temp_zip/Tools/ToolTestSelectFileDialog/*.*
rm temp_zip/Tools/ToolTestServerPusher/*.*
rm temp_zip/Tools/ToolTestShape/*.*
rm temp_zip/Tools/ToolTestShinyButton/*.*
rm temp_zip/Tools/ToolTestTimedServerPusher/*.*
rm temp_zip/Tools/ToolTestToggleButton/*.*
rm temp_zip/Tools/ToolTestTwoDigitNewick/*.*
rm temp_zip/Tools/ToolTimePoll/*.*

rmdir temp_zip/Tools/ToolCodeToHtml
rmdir temp_zip/Tools/ToolHometrainer
rmdir temp_zip/Tools/ToolRandomCode
rmdir temp_zip/Tools/ToolSimMysteryMachine
rmdir temp_zip/Tools/ToolTestAsciiArter
rmdir temp_zip/Tools/ToolTestDial
rmdir temp_zip/Tools/ToolTestEncranger
rmdir temp_zip/Tools/ToolTestEntrance
rmdir temp_zip/Tools/ToolTestExercise
rmdir temp_zip/Tools/ToolTestFunctionParser
rmdir temp_zip/Tools/ToolTestGroupWidget
rmdir temp_zip/Tools/ToolTestLed
rmdir temp_zip/Tools/ToolTestNewickVector
rmdir temp_zip/Tools/ToolTestQuestion
rmdir temp_zip/Tools/ToolTestSelectFileDialog
rmdir temp_zip/Tools/ToolTestServerPusher
rmdir temp_zip/Tools/ToolTestShape
rmdir temp_zip/Tools/ToolTestShinyButton
rmdir temp_zip/Tools/ToolTestToggleButton
rmdir temp_zip/Tools/ToolTestTwoDigitNewick
rmdir temp_zip/Tools/ToolTestTimedServerPusher
rmdir temp_zip/Tools/ToolTimePoll
rmdir temp_zip/Tools

rm temp_zip/*.*
rmdir temp_zip
echo "Done"

../../Tools/ToolCodeToHtmlConsole-build-desktop/codetohtml --source "../"$FOLDERNAME
cp $FOLDERNAME".htm" $HTM_FILENAME
rm $FOLDERNAME".htm"
