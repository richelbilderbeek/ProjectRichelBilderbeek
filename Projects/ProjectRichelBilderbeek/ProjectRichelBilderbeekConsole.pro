QT += core
QT -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppCopy_if \
    ../../Classes/CppCounter \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppEncranger \
    ../../Classes/CppExercise \
    ../../Classes/CppFuzzy_equal_to \
    ../../Classes/CppGaborFilter \
    ../../Classes/CppGaborFilterWidget \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppIpAddress \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppLazy_init \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppLoopReader \
    ../../Classes/CppManyDigitNewick \
    ../../Classes/CppMatrix \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppMultiVector \
    ../../Classes/CppMusic \
    ../../Classes/CppMysteryMachine \
    ../../Classes/CppMysteryMachineWidget \
    ../../Classes/CppNewick \
    ../../Classes/CppNewickVector \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppPylos \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtModel \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRainbow \
    ../../Classes/CppRandomCode \
    ../../Classes/CppRectangle \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppRubiksClock \
    ../../Classes/CppRubiksClockWidget \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppShinyButton \
    ../../Classes/CppShinyButtonWidget \
    ../../Classes/CppSortedBinaryNewickVector \
    ../../Classes/CppStateObserver \
    ../../Classes/CppStopwatch \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppTwoDigitNewick \
    ../../Classes/CppWidget \
    ../../Games/GameConnectThree \
    ../../Games/GamePylos \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateQtProjectZipFile \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolStateObserver \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestEncranger \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestNewickVector \
    ../../Tools/ToolTestQrcFile \
    ../../Tools/ToolTestQtArrowItems \
    ../../Tools/ToolTestQtCreatorProFile \
    ../../Tools/ToolTestQuestion \
    ../../Tools/ToolTestSelectFileDialog \
    ../../Tools/ToolTestShape \
    ../../Tools/ToolTestShinyButton \
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppAsciiArter/asciiarter.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmldialog.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlheader.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementscpp.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlreplacementspro.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.cpp \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlversion.cpp \
    ../../Classes/CppConnectThree/connectthree.cpp \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.cpp \
    ../../Classes/CppCounter/counter.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppExercise/exercise.cpp \
    ../../Classes/CppGaborFilter/gaborfilter.cpp \
    ../../Classes/CppGaborFilterWidget/gaborfilterwidget.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    ../../Classes/CppIpAddress/ipaddress.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.cpp \
    ../../Classes/CppLazy_init/lazy_init.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppPylos/pylosboard.cpp \
    ../../Classes/CppPylos/pyloscoordinat.cpp \
    ../../Classes/CppPylos/pyloscurrentmovestate.cpp \
    ../../Classes/CppPylos/pylosgame.cpp \
    ../../Classes/CppPylos/pylosmove.cpp \
    ../../Classes/CppPylos/pylosmustremovestate.cpp \
    ../../Classes/CppPylos/pylosplayer.cpp \
    ../../Classes/CppPylos/pylospositionstate.cpp \
    ../../Classes/CppPylos/pyloswinner.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtModel/modelfunctionparser.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppShinyButton/shinybutton.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
    ../../Classes/CppStateObserver/alphabetafilter.cpp \
    ../../Classes/CppStateObserver/alphabetagammafilter.cpp \
    ../../Classes/CppStateObserver/alphafilter.cpp \
    ../../Classes/CppStateObserver/floatingpointstateobserver.cpp \
    ../../Classes/CppStateObserver/integeralphafilter.cpp \
    ../../Classes/CppStateObserver/integerstateobserver.cpp \
    ../../Classes/CppStateObserver/integersymmetricalphafilter.cpp \
    ../../Classes/CppStateObserver/multialphafilter.cpp \
    ../../Classes/CppStateObserver/multiintegerstateobserver.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    ../../Classes/CppToggleButton/togglebutton.cpp \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.cpp \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Games/GameConnectThree/connectthreemenudialog.cpp \
    ../../Games/GameConnectThree/connectthreeresources.cpp \
    ../../Games/GamePylos/pylosmenudialog.cpp \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp \
    ../../Games/GameTicTacToe/tictactoemenudialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp \
    ../../Tools/ToolHometrainer/hometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainerresources.cpp \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermenudialog.cpp \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.cpp \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp \
    ../../Tools/ToolStateObserver/stateobservermenudialog.cpp \
    ../../Tools/ToolTestDial/testdialmenudialog.cpp \
    ../../Tools/ToolTestEncranger/testencrangerdialog.cpp \
    ../../Tools/ToolTestExercise/testexercisemenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestLed/testledmenudialog.cpp \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.cpp \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp \
    ../../Tools/ToolTestShape/testshapemaindialog.cpp \
    ../../Tools/ToolTestShape/testshapemenudialog.cpp \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.cpp \
    main.cpp \
    richelbilderbeekmenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppCounter/counter.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppExercise/exercise.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppGaborFilter/gaborfilter.h \
    ../../Classes/CppGaborFilterWidget/gaborfilterwidget.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppIpAddress/ipaddress.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/gapsfilledwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystem.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.h \
    ../../Classes/CppLazy_init/lazy_init.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppManyDigitNewick/manydigitnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.h \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppMultiVector/multivector.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppPylos/pylosboard.h \
    ../../Classes/CppPylos/pyloscoordinat.h \
    ../../Classes/CppPylos/pyloscurrentmovestate.h \
    ../../Classes/CppPylos/pylosfwd.h \
    ../../Classes/CppPylos/pylosgame.h \
    ../../Classes/CppPylos/pylosmove.h \
    ../../Classes/CppPylos/pylosmustremovestate.h \
    ../../Classes/CppPylos/pylosplayer.h \
    ../../Classes/CppPylos/pylospositionstate.h \
    ../../Classes/CppPylos/pyloswinner.h \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtModel/modelfunctionparser.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppRainbow/rainbow.h \
    ../../Classes/CppRandomCode/randomcode.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppShinyButton/shinybutton.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h \
    ../../Classes/CppStateObserver/alphabetafilter.h \
    ../../Classes/CppStateObserver/alphabetagammafilter.h \
    ../../Classes/CppStateObserver/alphafilter.h \
    ../../Classes/CppStateObserver/floatingpointstateobserver.h \
    ../../Classes/CppStateObserver/integeralphafilter.h \
    ../../Classes/CppStateObserver/integerstateobserver.h \
    ../../Classes/CppStateObserver/integersymmetricalphafilter.h \
    ../../Classes/CppStateObserver/multialphafilter.h \
    ../../Classes/CppStateObserver/multiintegerstateobserver.h \
    ../../Classes/CppStateObserver/stateobserverfwd.h \
    ../../Classes/CppStopwatch/stopwatch.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppWidget/widget.h \
    ../../Games/GamePylos/pylosmenudialog.h \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.h \
    ../../Games/GameTicTacToe/tictactoemenudialog.h \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.h \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.h \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h \
    ../../Tools/ToolHometrainer/hometrainermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainerresources.h \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.h \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.h \
    ../../Tools/ToolRegexTester/regextestermaindialog.h \
    ../../Tools/ToolRegexTester/regextestermenudialog.h \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.h \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.h \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h \
    ../../Tools/ToolStateObserver/stateobservermenudialog.h \
    ../../Tools/ToolTestDial/testdialmenudialog.h \
    ../../Tools/ToolTestEncranger/testencrangerdialog.h \
    ../../Tools/ToolTestExercise/testexercisemenudialog.h \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.h \
    ../../Tools/ToolTestLed/testledmenudialog.h \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestShape/testshapemaindialog.h \
    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    richelbilderbeekmenudialog.h

OTHER_FILES += \
    ../../Classes/CppGaborFilter/Licence.txt \
    ../../Classes/CppGaborFilterWidget/Licence.txt \
    ../../Classes/CppHtmlPage/Licence.txt \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppPylos/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Tools/ToolCreateQtProjectZipFile/Licence.txt \
    ../../Tools/ToolCreateQtProjectZipFile/R.png \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Tools/ToolTestEncranger/Licence.txt \
    ../../Tools/ToolTestLed/Licence.txt \
    ../../Tools/ToolTestQrcFile/Licence.txt \
    ../../Tools/ToolTestQtCreatorProFile/Licence.txt

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra


unix {
  message(Unix)
  QMAKE_CXXFLAGS += -Werror
}

win32 {
  !static {
    message(Native Windows)
    QMAKE_CXXFLAGS += -Werror

  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
    #Allow the crosscompiler to emit warnings without terminating
    QMAKE_CXXFLAGS += -std=c++0x #-Werror
  }
}

#
#
# Big integer
#
#
INCLUDEPATH += \
    ../../Libraries/bigint-2010.04.30

HEADERS += \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.hh \
    ../../Libraries/bigint-2010.04.30/BigInteger.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerLibrary.hh \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.hh \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.hh \
    ../../Libraries/bigint-2010.04.30/NumberlikeArray.hh

SOURCES += \
    ../../Libraries/bigint-2010.04.30/BigIntegerAlgorithms.cc \
    ../../Libraries/bigint-2010.04.30/BigInteger.cc \
    ../../Libraries/bigint-2010.04.30/BigIntegerUtils.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsigned.cc \
    ../../Libraries/bigint-2010.04.30/BigUnsignedInABase.cc

#
#
# Boost
#
#

unix {
  message(Unix dynamic link to Boost)

  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  message(Windows dynamic link to Boost)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0

  debug {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-d-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-d-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-d-1_54.a
  }
  release {
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_filesystem-mgw48-mt-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_regex-mgw48-mt-1_54.a
    LIBS += ../../Libraries/boost_1_54_0/stage/lib/libboost_system-mgw48-mt-1_54.a
  }
}

#
#
# Warp's function parser
#
#
INCLUDEPATH += \
  ../../Libraries/fparser4.5.1

HEADERS += \
  ../../Libraries/fparser4.5.1/extrasrc/fpaux.hh \
  ../../Libraries/fparser4.5.1/extrasrc/fptypes.hh \
  ../../Libraries/fparser4.5.1/fparser_gmpint.hh \
  ../../Libraries/fparser4.5.1/fparser.hh \
  ../../Libraries/fparser4.5.1/fparser_mpfr.hh \
  ../../Libraries/fparser4.5.1/fpconfig.hh

SOURCES += \
  ../../Libraries/fparser4.5.1/fparser.cc \
  ../../Libraries/fparser4.5.1/fpoptimizer.cc


OTHER_FILES += \
  ../../Libraries/fparser4.5.1/extrasrc/fp_identifier_parser.inc \
  ../../Libraries/fparser4.5.1/extrasrc/fp_opcode_add.inc

#
#
# Qwt
#
#

unix {
  INCLUDEPATH += /usr/include/qwt-qt4
  LIBS += -lqwt-qt4
}

win32 {
  message(Windows: Qwt: link dynamically)
  INCLUDEPATH+= ../../Libraries/qwt-6.1.0/src
  LIBS+= -L../../Libraries/qwt-6.1.0/lib

  CONFIG(release, debug|release) {
    message(Windows: Qwt: Linking to qwt)
    LIBS += -lqwt
  }

  CONFIG(debug, debug|release) {
    message(Windows: Qwt: Linking to qwtd)
    LIBS += -lqwtd
  }
}

