#!/bin/sh

echo "Removing user information"
rm *.user

echo "Removing possible temp file"
rm copy.txt
rm tmp.txt


echo "Creating of all main folders"

mkdir temp_zip
mkdir temp_zip/Classes
mkdir temp_zip/Tools

echo "Creating of all subfolders"

mkdir temp_zip/Classes/CppAbout
mkdir temp_zip/Classes/CppExercise
mkdir temp_zip/Classes/CppMultipleChoiceQuestion
mkdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppOpenQuestion
mkdir temp_zip/Classes/CppOpenQuestionDialog
mkdir temp_zip/Classes/CppQtAboutDialog
mkdir temp_zip/Classes/CppQtExercise
mkdir temp_zip/Classes/CppQtHideAndShowDialog
mkdir temp_zip/Classes/CppQtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppQtOpenQuestionDialog
mkdir temp_zip/Classes/CppQtQuestionDialog
mkdir temp_zip/Classes/CppQuestion
mkdir temp_zip/Classes/CppQuestionDialog
mkdir temp_zip/Classes/CppTrace
mkdir temp_zip/Classes/CppWtAboutDialog
mkdir temp_zip/Classes/CppWtAutoConfig
mkdir temp_zip/Classes/CppWtExercise
mkdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
mkdir temp_zip/Classes/CppWtOpenQuestionDialog
mkdir temp_zip/Classes/CppWtQuestionDialog
mkdir temp_zip/Classes/CppWtSelectFileDialog
mkdir temp_zip/Tools/ToolHometrainer

echo "Copying files"

cp ../../Classes/CppAbout/about.cpp temp_zip/Classes/CppAbout/about.cpp
cp ../../Classes/CppAbout/about.h temp_zip/Classes/CppAbout/about.h
cp ../../Classes/CppExercise/Licence.txt temp_zip/Classes/CppExercise/Licence.txt
cp ../../Classes/CppExercise/exercise.cpp temp_zip/Classes/CppExercise/exercise.cpp
cp ../../Classes/CppExercise/exercise.h temp_zip/Classes/CppExercise/exercise.h
cp ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp temp_zip/Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp
cp ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h temp_zip/Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h
cp ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp temp_zip/Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp
cp ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h temp_zip/Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h
cp ../../Classes/CppOpenQuestion/openquestion.cpp temp_zip/Classes/CppOpenQuestion/openquestion.cpp
cp ../../Classes/CppOpenQuestion/openquestion.h temp_zip/Classes/CppOpenQuestion/openquestion.h
cp ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp temp_zip/Classes/CppOpenQuestionDialog/openquestiondialog.cpp
cp ../../Classes/CppOpenQuestionDialog/openquestiondialog.h temp_zip/Classes/CppOpenQuestionDialog/openquestiondialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.cpp
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.h temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.h
cp ../../Classes/CppQtAboutDialog/qtaboutdialog.ui temp_zip/Classes/CppQtAboutDialog/qtaboutdialog.ui
cp ../../Classes/CppQtExercise/Licence.txt temp_zip/Classes/CppQtExercise/Licence.txt
cp ../../Classes/CppQtExercise/qtexercise.cpp temp_zip/Classes/CppQtExercise/qtexercise.cpp
cp ../../Classes/CppQtExercise/qtexercise.h temp_zip/Classes/CppQtExercise/qtexercise.h
cp ../../Classes/CppQtHideAndShowDialog/Licence.txt temp_zip/Classes/CppQtHideAndShowDialog/Licence.txt
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp
cp ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h temp_zip/Classes/CppQtHideAndShowDialog/qthideandshowdialog.h
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h
cp ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h
cp ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui temp_zip/Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui
cp ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp temp_zip/Classes/CppQtQuestionDialog/qtquestiondialog.cpp
cp ../../Classes/CppQtQuestionDialog/qtquestiondialog.h temp_zip/Classes/CppQtQuestionDialog/qtquestiondialog.h
cp ../../Classes/CppQuestion/question.cpp temp_zip/Classes/CppQuestion/question.cpp
cp ../../Classes/CppQuestion/question.h temp_zip/Classes/CppQuestion/question.h
cp ../../Classes/CppQuestionDialog/questiondialog.cpp temp_zip/Classes/CppQuestionDialog/questiondialog.cpp
cp ../../Classes/CppQuestionDialog/questiondialog.h temp_zip/Classes/CppQuestionDialog/questiondialog.h
cp ../../Classes/CppTrace/Licence.txt temp_zip/Classes/CppTrace/Licence.txt
cp ../../Classes/CppTrace/trace.h temp_zip/Classes/CppTrace/trace.h
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.cpp
cp ../../Classes/CppWtAboutDialog/wtaboutdialog.h temp_zip/Classes/CppWtAboutDialog/wtaboutdialog.h
cp ../../Classes/CppWtAutoConfig/wtautoconfig.cpp temp_zip/Classes/CppWtAutoConfig/wtautoconfig.cpp
cp ../../Classes/CppWtAutoConfig/wtautoconfig.h temp_zip/Classes/CppWtAutoConfig/wtautoconfig.h
cp ../../Classes/CppWtExercise/wtexercise.cpp temp_zip/Classes/CppWtExercise/wtexercise.cpp
cp ../../Classes/CppWtExercise/wtexercise.h temp_zip/Classes/CppWtExercise/wtexercise.h
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp
cp ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h
cp ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp temp_zip/Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp
cp ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h temp_zip/Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h
cp ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp temp_zip/Classes/CppWtQuestionDialog/wtquestiondialog.cpp
cp ../../Classes/CppWtQuestionDialog/wtquestiondialog.h temp_zip/Classes/CppWtQuestionDialog/wtquestiondialog.h
cp ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp temp_zip/Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp
cp ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h temp_zip/Classes/CppWtSelectFileDialog/wtselectfiledialog.h
cp ../../Tools/ToolHometrainer/Licence.txt temp_zip/Tools/ToolHometrainer/Licence.txt
cp ../../Tools/ToolHometrainer/RichelbilderbeekNlBackground.png temp_zip/Tools/ToolHometrainer/RichelbilderbeekNlBackground.png
cp ../../Tools/ToolHometrainer/ToolHometrainer.qrc temp_zip/Tools/ToolHometrainer/ToolHometrainer.qrc
cp ../../Tools/ToolHometrainer/ToolHometrainerArchitecture.dia~ temp_zip/Tools/ToolHometrainer/ToolHometrainerArchitecture.dia~
cp ../../Tools/ToolHometrainer/ToolHometrainerDesktop.pro temp_zip/Tools/ToolHometrainer/ToolHometrainerDesktop.pro
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseAdapter.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseAdapter.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseAuks.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseAuks.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseBakMetFilters.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseBakMetFilters.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseCdSpelerNumarck.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseCdSpelerNumarck.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseClouds.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseClouds.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDcc.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDcc.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDi.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDi.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDimmerpack.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDimmerpack.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseEffect.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseEffect.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseEuroMannetjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseEuroMannetjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseEuroVrouwtje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseEuroVrouwtje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilter.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFilter.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilterboekje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFilterboekje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilterhouder.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFilterhouder.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFiltervellen.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFiltervellen.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFlightcase.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFlightcase.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseFresnel.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseFresnel.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantLinks.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantLinks.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantRechts.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantRechts.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAlesis.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAlesis.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMidden.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMidden.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMiddenboven.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMiddenboven.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsboven.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsboven.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsonder.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsonder.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelYamaha.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelYamaha.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseGordijnhaak.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseGordijnhaak.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseHaspel.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseHaspel.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackMannetjeMono.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseJackMannetjeMono.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeEnXlrVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeEnXlrVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseKabeltester.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseKabeltester.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseLamp500W.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseLamp500W.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplan.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseLichtplan.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplanDeBruiloften.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseLichtplanDeBruiloften.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichttafel.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseLichttafel.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdGrijs.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMdGrijs.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdSpeler.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMdSpeler.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdTransparent.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMdTransparent.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMicrofoonShureSm58.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMicrofoonShureSm58.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMiniJackStereoVrouwJackStereoMan.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMiniJackStereoVrouwJackStereoMan.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMonitorTorqueConnectors.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMonitorTorqueConnectors.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelMannetjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelMannetjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultimeterMetex.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMultimeterMetex.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultistekkerdoos.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseMultistekkerdoos.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseOn.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseOn.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseOpwindstatief.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseOpwindstatief.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExercisePar.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExercisePar.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExercisePc.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExercisePc.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExercisePriklijst.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExercisePriklijst.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseProfielspot.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseProfielspot.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseRcf322aAchterkant.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseRcf322aAchterkant.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseRgbLamp.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseRgbLamp.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSafety.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSafety.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseScartMannetje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseScartMannetje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSchukoVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSchukoVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseShureSm58.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseShureSm58.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpanningsmeterFluke.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSpanningsmeterFluke.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakerEvent3000.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSpeakerEvent3000.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwSpeakonVrouw.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwSpeakonVrouw.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwtjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwtjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpringV2.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseSpringV2.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseStandenplot.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseStandenplot.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseStekkerdoos.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseStekkerdoos.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTbar.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTbar.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTest.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTest.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTruss.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTruss.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussHaarspeld.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTrussHaarspeld.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussPin.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTrussPin.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussVerbindingsstuk.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTrussVerbindingsstuk.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussklem.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTrussklem.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtBasis.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTtBasis.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtGeluid.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTtGeluid.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtLicht.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTtLicht.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseTulpMannetje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseTulpMannetje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseVerloopstukje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseVerloopstukje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamson.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamson.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamsonAchterkant.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamsonAchterkant.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseVgaVrouwVgaVrouw.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseVgaVrouwVgaVrouw.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseVoetstatief.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseVoetstatief.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhem.txt temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhem.txt
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhemGenummerd.bmp temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhemGenummerd.bmp
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrMannetjeConnector.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseXlrMannetjeConnector.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrVrouwtje.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseXlrVrouwtje.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerExerciseZekering.jpg temp_zip/Tools/ToolHometrainer/ToolHometrainerExerciseZekering.jpg
cp ../../Tools/ToolHometrainer/ToolHometrainerManual.odt temp_zip/Tools/ToolHometrainer/ToolHometrainerManual.odt
cp ../../Tools/ToolHometrainer/ToolHometrainerQuestion.png temp_zip/Tools/ToolHometrainer/ToolHometrainerQuestion.png
cp ../../Tools/ToolHometrainer/ToolHometrainerQuestionmark.png temp_zip/Tools/ToolHometrainer/ToolHometrainerQuestionmark.png
cp ../../Tools/ToolHometrainer/ToolHometrainerTitle.png temp_zip/Tools/ToolHometrainer/ToolHometrainerTitle.png
cp ../../Tools/ToolHometrainer/ToolHometrainerWebsite.pro temp_zip/Tools/ToolHometrainer/ToolHometrainerWebsite.pro
cp ../../Tools/ToolHometrainer/ToolHometrainerWelcome.png temp_zip/Tools/ToolHometrainer/ToolHometrainerWelcome.png
cp ../../Tools/ToolHometrainer/ToolTestDialArchitecture.dia~ temp_zip/Tools/ToolHometrainer/ToolTestDialArchitecture.dia~
cp ../../Tools/ToolHometrainer/ToolTestDialArchitecture_1_0.dia~ temp_zip/Tools/ToolHometrainer/ToolTestDialArchitecture_1_0.dia~
cp ../../Tools/ToolHometrainer/ToolTestQuestionArchitecture.dia~ temp_zip/Tools/ToolHometrainer/ToolTestQuestionArchitecture.dia~
cp ../../Tools/ToolHometrainer/crosscompiletowindows.sh temp_zip/Tools/ToolHometrainer/crosscompiletowindows.sh
cp ../../Tools/ToolHometrainer/hometrainermenudialog.cpp temp_zip/Tools/ToolHometrainer/hometrainermenudialog.cpp
cp ../../Tools/ToolHometrainer/hometrainermenudialog.h temp_zip/Tools/ToolHometrainer/hometrainermenudialog.h
cp ../../Tools/ToolHometrainer/hometrainerresources.cpp temp_zip/Tools/ToolHometrainer/hometrainerresources.cpp
cp ../../Tools/ToolHometrainer/hometrainerresources.h temp_zip/Tools/ToolHometrainer/hometrainerresources.h
cp ../../Tools/ToolHometrainer/qthometrainermaindialog.cpp temp_zip/Tools/ToolHometrainer/qthometrainermaindialog.cpp
cp ../../Tools/ToolHometrainer/qthometrainermaindialog.h temp_zip/Tools/ToolHometrainer/qthometrainermaindialog.h
cp ../../Tools/ToolHometrainer/qthometrainermaindialog.ui temp_zip/Tools/ToolHometrainer/qthometrainermaindialog.ui
cp ../../Tools/ToolHometrainer/qthometrainermenudialog.cpp temp_zip/Tools/ToolHometrainer/qthometrainermenudialog.cpp
cp ../../Tools/ToolHometrainer/qthometrainermenudialog.h temp_zip/Tools/ToolHometrainer/qthometrainermenudialog.h
cp ../../Tools/ToolHometrainer/qthometrainermenudialog.ui temp_zip/Tools/ToolHometrainer/qthometrainermenudialog.ui
cp ../../Tools/ToolHometrainer/qtmain.cpp temp_zip/Tools/ToolHometrainer/qtmain.cpp
cp ../../Tools/ToolHometrainer/trace_out.txt temp_zip/Tools/ToolHometrainer/trace_out.txt
cp ../../Tools/ToolHometrainer/wt.css temp_zip/Tools/ToolHometrainer/wt.css
cp ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.cpp temp_zip/Tools/ToolHometrainer/wthometrainerloadexercisedialog.cpp
cp ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.h temp_zip/Tools/ToolHometrainer/wthometrainerloadexercisedialog.h
cp ../../Tools/ToolHometrainer/wthometrainermenudialog.cpp temp_zip/Tools/ToolHometrainer/wthometrainermenudialog.cpp
cp ../../Tools/ToolHometrainer/wthometrainermenudialog.h temp_zip/Tools/ToolHometrainer/wthometrainermenudialog.h
cp ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.cpp temp_zip/Tools/ToolHometrainer/wthometrainerstartexercisedialog.cpp
cp ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.h temp_zip/Tools/ToolHometrainer/wthometrainerstartexercisedialog.h
cp ../../Tools/ToolHometrainer/wtmain.cpp temp_zip/Tools/ToolHometrainer/wtmain.cpp
cp ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.cpp temp_zip/Tools/ToolHometrainer/wtselecthometrainerfiledialog.cpp
cp ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.h temp_zip/Tools/ToolHometrainer/wtselecthometrainerfiledialog.h
cp ../../Tools/ToolHometrainer/zip.sh temp_zip/Tools/ToolHometrainer/zip.sh

FILENAME="ToolHometrainerSource"
ZIP_FILENAME=$FILENAME".zip"

echo "Compressing files"

cd temp_zip
zip -r $FILENAME Classes
zip -r $FILENAME Tools
cd ..
cp "temp_zip/"$ZIP_FILENAME $ZIP_FILENAME

echo "Cleaning up"

echo "Emptying subfolders"

rm temp_zip/Classes/CppAbout/*.*
rm temp_zip/Classes/CppExercise/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestion/*.*
rm temp_zip/Classes/CppMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppOpenQuestion/*.*
rm temp_zip/Classes/CppOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQtAboutDialog/*.*
rm temp_zip/Classes/CppQtExercise/*.*
rm temp_zip/Classes/CppQtHideAndShowDialog/*.*
rm temp_zip/Classes/CppQtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppQtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppQtQuestionDialog/*.*
rm temp_zip/Classes/CppQuestion/*.*
rm temp_zip/Classes/CppQuestionDialog/*.*
rm temp_zip/Classes/CppTrace/*.*
rm temp_zip/Classes/CppWtAboutDialog/*.*
rm temp_zip/Classes/CppWtAutoConfig/*.*
rm temp_zip/Classes/CppWtExercise/*.*
rm temp_zip/Classes/CppWtMultipleChoiceQuestionDialog/*.*
rm temp_zip/Classes/CppWtOpenQuestionDialog/*.*
rm temp_zip/Classes/CppWtQuestionDialog/*.*
rm temp_zip/Classes/CppWtSelectFileDialog/*.*
rm temp_zip/Tools/ToolHometrainer/*.*

echo "Removing subfolders"

rmdir temp_zip/Classes/CppAbout
rmdir temp_zip/Classes/CppExercise
rmdir temp_zip/Classes/CppMultipleChoiceQuestion
rmdir temp_zip/Classes/CppMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppOpenQuestion
rmdir temp_zip/Classes/CppOpenQuestionDialog
rmdir temp_zip/Classes/CppQtAboutDialog
rmdir temp_zip/Classes/CppQtExercise
rmdir temp_zip/Classes/CppQtHideAndShowDialog
rmdir temp_zip/Classes/CppQtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppQtOpenQuestionDialog
rmdir temp_zip/Classes/CppQtQuestionDialog
rmdir temp_zip/Classes/CppQuestion
rmdir temp_zip/Classes/CppQuestionDialog
rmdir temp_zip/Classes/CppTrace
rmdir temp_zip/Classes/CppWtAboutDialog
rmdir temp_zip/Classes/CppWtAutoConfig
rmdir temp_zip/Classes/CppWtExercise
rmdir temp_zip/Classes/CppWtMultipleChoiceQuestionDialog
rmdir temp_zip/Classes/CppWtOpenQuestionDialog
rmdir temp_zip/Classes/CppWtQuestionDialog
rmdir temp_zip/Classes/CppWtSelectFileDialog
rmdir temp_zip/Tools/ToolHometrainer

echo "Removing main folders"

rmdir temp_zip/Classes
rmdir temp_zip/Tools

echo "Removing temporary folder"

rm temp_zip/*.*
rmdir temp_zip

echo "Done"

# CreateQtProjectZipFile, version 1.3
# Copyright (C) 2012 Richel Bilderbeek
# Programmed on the 10th of June 2012
# by Richel Bilderbeek
# 
# CreateQtProjectZipFile can be downloaded from http://www.richelbilderbeek.nl/ToolCreateQtProjectZipFile.htm
# Licenced under GPL 3.0
