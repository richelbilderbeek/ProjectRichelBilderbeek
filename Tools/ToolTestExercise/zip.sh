#!/bin/sh
#zip packs all the files to port into a single .zip file,
#minicking the same folder structure
#Folder structure
# *
#   * Classes
#     * CppAbout
#     * CppExercise
#     * CppMultipleChoiceQuestion
#     * CppMultipleChoiceQuestionDialog
#     * CppOpenQuestion
#     * CppOpenQuestionDialog
#     * CppQuestion
#     * CppQuestionDialog
#     * CppTrace
#     * CppWtAboutDialog
#     * CppWtAutoConfig
#     * CppWtExercise
#     * CppWtMultipleChoiceQuestionDialog
#     * CppWtOpenQuestionDialog
#     * CppWtQuestionDialog
#   * Tools
#    * ToolTestExercise

FOLDERNAME=ToolTestExercise
FILENAME=$FOLDERNAME"Source_1_0"
ZIP_FILENAME=$FILENAME".zip"
HTM_FILENAME=$FILENAME".htm"

#echo "Converting DIA to PNG"
#dia --filter=png ToolTestExerciseArchitecture.dia

echo "Removing previous user's information"
rm *.user

echo "Mimicking file structure"
mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppExercise
mkdir temp_zip/Classes/CppMultipleChoiceQuestion
mkdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppOpenQuestion
mkdir temp_zip/Classes/CppOpenQuestionDialog
mkdir temp_zip/Classes/CppQuestion
mkdir temp_zip/Classes/CppQuestionDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtExercise
mkdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppWtOpenQuestionDialog
mkdir temp_zip/Classes/CppWtQuestionDialog
mkdir temp_zip/Tools
mkdir temp_zip/Tools/ToolTestExercise

echo "Copying files"
cp ../../Classes/CppAbout/*.* temp_zip/Classes/CppAbout
cp ../../Classes/CppExercise/*.* temp_zip/Classes/CppExercise
cp ../../Classes/CppMultipleChoiceQuestion/*.* temp_zip/Classes/CppMultipleChoiceQuestion
cp ../../Classes/CppMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppMultipleChoiceQuestionDialog
cp ../../Classes/CppOpenQuestion/*.* temp_zip/Classes/CppOpenQuestion
cp ../../Classes/CppOpenQuestionDialog/*.* temp_zip/Classes/CppOpenQuestionDialog
cp ../../Classes/CppQuestion/*.* temp_zip/Classes/CppQuestion
cp ../../Classes/CppQuestionDialog/*.* temp_zip/Classes/CppQuestionDialog
cp ../../Classes/CppTrace/*.* temp_zip/Classes/CppTrace
cp ../../Classes/CppWtAboutDialog/*.* temp_zip/Classes/CppWtAboutDialog
cp ../../Classes/CppWtAutoConfig/*.* temp_zip/Classes/CppWtAutoConfig
cp ../../Classes/CppWtExercise/*.* temp_zip/Classes/CppWtExercise
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/*.* temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
cp ../../Classes/CppWtOpenQuestionDialog/*.* temp_zip/Classes/CppWtOpenQuestionDialog
cp ../../Classes/CppWtQuestionDialog/*.* temp_zip/Classes/CppWtQuestionDialog
cp ../../Tools/ToolTestExercise/*.* temp_zip/Tools/ToolTestExercise

#echo "Compressing files"
cd temp_zip
zip -r $FILENAME Classes
#zip -r $FILENAME Libraries
#zip -r $FILENAME Projects
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

#Classes
rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppExercise/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestion/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppOpenQuestion/*.*
rm temp_zip/Classes/CppOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQuestion/*.*
rm temp_zip/Classes/CppQuestionDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtExercise/*.*
rm temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppWtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppWtQuestionDialog/*.*

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppExercise
rmdir temp_zip/Classes/CppMultipleChoiceQuestion
rmdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppOpenQuestion
rmdir temp_zip/Classes/CppOpenQuestionDialog
rmdir temp_zip/Classes/CppQuestion
rmdir temp_zip/Classes/CppQuestionDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtExercise
rmdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppWtOpenQuestionDialog
rmdir temp_zip/Classes/CppWtQuestionDialog
rmdir temp_zip/Classes

#Tools
rm temp_zip/Tools/ToolTestExercise/*.*
rmdir temp_zip/Tools/ToolTestExercise
rmdir temp_zip/Tools
rm temp_zip/*.*
rmdir temp_zip
echo "Done"

../ToolCodeToHtmlConsole-build-desktop/codetohtml --source "../"$FOLDERNAME
cp $FOLDERNAME".htm" $HTM_FILENAME
rm $FOLDERNAME".htm"
