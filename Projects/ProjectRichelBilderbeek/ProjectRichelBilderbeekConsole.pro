include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppExercise/CppExercise.pri)
include(../../Classes/CppFileIo/CppFileIo.pro)
include(ProjectRichelBilderbeekConsole.pri)

# Go ahead and use Qt.Core: it is about as platform-independent as
# the STL and Boost
QT += core

# Go ahead and use Qt.Gui: it is about as platform-independent as
# the STL and Boost. It is needed for QImage
QT += gui

# Don't define widgets: it would defy the purpose of this console
# application to work non-GUI
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

# Console

INCLUDEPATH += \
#    ../../Classes/CppAbout \
    ../../Classes/CppApproximator \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppCanvas \
    ../../Classes/CppChess \
    ../../Classes/CppChessResources \
    ../../Classes/CppCodeToHtml \
    ../../Classes/CppConnectThree \
    ../../Classes/CppConnectThreeWidget \
    ../../Classes/CppCopy_if \
    ../../Classes/CppCounter \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppDotMatrix \
    ../../Classes/CppEncranger \
#    ../../Classes/CppExercise \
    ../../Classes/CppFileIo \
    ../../Classes/CppFuzzy_equal_to \
    ../../Classes/CppGaborFilter \
    ../../Classes/CppGaborFilterWidget \
    ../../Classes/CppHelp \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppIpAddress \
    ../../Classes/CppKalmanFilter \
    ../../Classes/CppLazy_init \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppLoopReader \
    ../../Classes/CppManyDigitNewick \
    ../../Classes/CppMatrix \
    ../../Classes/CppMenuDialog \
    ../../Classes/CppMultiApproximator \
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
    ../../Classes/CppSimpleLinearRegression \
    ../../Classes/CppSortedBinaryNewickVector \
    ../../Classes/CppStateObserver \
    ../../Classes/CppStopwatch \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppToggleButton \
    ../../Classes/CppToggleButtonWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppTwoDigitNewick \
    ../../Classes/CppWidget \
    ../../Games/GameBeerWanter \
    ../../Games/GameBoenken \
    ../../Games/GameConnectThree \
    ../../Games/GameDasWahreSchlagerfest \
    ../../Games/GameK3OpEenRij \
    ../../Games/GameMaziak \
    ../../Games/GamePylos \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Projects/RichelbilderbeekNl \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateGlossary \
    ../../Tools/ToolDotMatrix \
    ../../Tools/ToolEncranger \
    ../../Tools/ToolGaborFilter \
    ../../Tools/ToolGrayCoder \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolKalmanFilterer \
    ../../Tools/ToolMazeCreator \
    ../../Tools/ToolMultiEncranger \
    ../../Tools/ToolMusicTheory \
    ../../Tools/ToolPerfectElasticCollision \
    ../../Tools/ToolPicToCode \
    ../../Tools/ToolPrimeExpert \
    ../../Tools/ToolQmakeWatcher \
    ../../Tools/ToolQuadraticSolver \
    ../../Tools/ToolRandomCode \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolRichelBilderbeekGallery \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolSimplifyNewick \
    ../../Tools/ToolStateObserver \
    ../../Tools/ToolTestAbout \
    ../../Tools/ToolTestApproximator \
    ../../Tools/ToolTestCanvas \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestMultiApproximator \
    ../../Tools/ToolTestMultipleChoiceQuestion \
    ../../Tools/ToolTestNewickVector \
    ../../Tools/ToolTestOpenQuestion \
    ../../Tools/ToolTestPylos \
    ../../Tools/ToolTestQrcFile \
    ../../Tools/ToolTestQtArrowItems \
    ../../Tools/ToolTestQtCreatorProFile \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView \
    ../../Tools/ToolTestQtModels \
    ../../Tools/ToolTestQtRoundedEditRectItem \
    ../../Tools/ToolTestQtRoundedRectItem \
    ../../Tools/ToolTestQtRoundedTextRectItem \
    ../../Tools/ToolTestQuestion \
    ../../Tools/ToolTestSelectFileDialog \
    ../../Tools/ToolTestShape \
    ../../Tools/ToolTestShinyButton \
    ../../Tools/ToolTestSimpleLinearRegression \
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick

SOURCES += \
    main.cpp \
#    ../../Classes/CppAbout/about.cpp \
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
#    ../../Classes/CppExercise/exercise.cpp \
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
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppShinyButton/shinybutton.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppSimpleLinearRegression/simplelinearregression.cpp \
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
    ../../Games/GameBeerWanter/beerwantermaindialog.cpp \
    ../../Games/GameBeerWanter/beerwantermenudialog.cpp \
    ../../Games/GameBoenken/boenkenmenudialog.cpp \
    ../../Games/GameConnectThree/connectthreemenudialog.cpp \
    ../../Games/GameConnectThree/connectthreeresources.cpp \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.cpp \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp \
    ../../Games/GameK3OpEenRij/k3opeenrijmenudialog.cpp \
    ../../Games/GameMaziak/maziakmenudialog.cpp \
    ../../Games/GamePylos/pylosmenudialog.cpp \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp \
    ../../Games/GameTicTacToe/tictactoemenudialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp \
    ../../Tools/ToolCreateGlossary/createglossarymaindialog.cpp \
    ../../Tools/ToolCreateGlossary/createglossarymenudialog.cpp \
    ../../Tools/ToolEncranger/toolencrangermaindialog.cpp \
    ../../Tools/ToolEncranger/toolencrangermenudialog.cpp \
    ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.cpp \
    ../../Tools/ToolGrayCoder/toolgraycodermaindialog.cpp \
    ../../Tools/ToolGrayCoder/toolgraycodermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainerresources.cpp \
    ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.cpp \
    ../../Tools/ToolMazeCreator/mazecreatormenudialog.cpp \
    ../../Tools/ToolMultiEncranger/toolmultiencrangermenudialog.cpp \
    ../../Tools/ToolMusicTheory/musictheorymenudialog.cpp \
    ../../Tools/ToolPerfectElasticCollision/perfectelasticcollisionmenudialog.cpp \
    ../../Tools/ToolPicToCode/pictocodemaindialog.cpp \
    ../../Tools/ToolPicToCode/pictocodemenudialog.cpp \
    ../../Tools/ToolQmakeWatcher/qmakewatchermenudialog.cpp \
    ../../Tools/ToolRandomCode/randomcodemenudialog.cpp \
    ../../Tools/ToolRegexTester/regextesterboostregexmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextesterboostxpressivemaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermenudialog.cpp \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.cpp \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.cpp \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp \
    ../../Tools/ToolSimplifyNewick/toolsimplifynewickmaindialog.cpp \
    ../../Tools/ToolSimplifyNewick/toolsimplifynewickmenudialog.cpp \
    ../../Tools/ToolStateObserver/noisefunctionparser.cpp \
    ../../Tools/ToolStateObserver/stateobservermenudialog.cpp \
    ../../Tools/ToolTestApproximator/tooltestapproximatormenudialog.cpp \
    ../../Tools/ToolTestCanvas/tooltestcanvasmenudialog.cpp \
    ../../Tools/ToolTestDial/testdialmenudialog.cpp \
    ../../Tools/ToolTestEntrance/testentrancemenudialog.cpp \
    ../../Tools/ToolTestExercise/testexercisemenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.cpp \
    ../../Tools/ToolTestLed/tooltestledmenudialog.cpp \
    ../../Tools/ToolTestMultiApproximator/tooltestmultiapproximatormenudialog.cpp \
    ../../Tools/ToolTestMultipleChoiceQuestion/testmultiplechoicequestionmaindialog.cpp \
    ../../Tools/ToolTestMultipleChoiceQuestion/testmultiplechoicequestionmenudialog.cpp \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.cpp \
    ../../Tools/ToolTestPylos/testpylosmenudialog.cpp \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.cpp \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.cpp \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/testqtkeyboardfriendlygraphicsviewmenudialog.cpp \
    ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp \
    ../../Tools/ToolTestShape/testshapemaindialog.cpp \
    ../../Tools/ToolTestShape/testshapemenudialog.cpp \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestOpenQuestion/testopenquestionmenudialog.cpp \
    ../../Tools/ToolTestOpenQuestion/testopenquestionmaindialog.cpp \
    ../../Tools/ToolTestSimpleLinearRegression/tooltestsimplelinearregressionmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.cpp \
    ../../Tools/ToolMultiEncranger/toolmultiencrangermaindialog.cpp \
    ../../Classes/CppCanvas/canvas.cpp \
    ../../Tools/ToolQuadraticSolver/quadraticsolvermenudialog.cpp \
    ../../Tools/ToolQuadraticSolver/quadraticsolvermaindialog.cpp \
    ../../Tools/ToolPrimeExpert/toolprimeexpertmenudialog.cpp \
    ../../Tools/ToolPrimeExpert/primeexpert.cpp \
    ../../Tools/ToolDotMatrix/tooldotmatrixmenudialog.cpp \
    ../../Classes/CppDotMatrix/dotmatrixstring.cpp \
    ../../Classes/CppDotMatrix/dotmatrixchar.cpp \
    ../../Classes/CppFileIo/fileio.cpp \
    ../../Tools/ToolHometrainer/hometrainermaindialog.cpp \
    ../../Classes/CppMenuDialog/menudialog.cpp \
    ../../Classes/CppHelp/help.cpp

HEADERS += \
#    ../../Classes/CppAbout/about.h \
    ../../Classes/CppApproximator/approximator.h \
    ../../Classes/CppApproximator/exceptionnoextrapolation.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Tools/ToolTestOpenQuestion/testopenquestionmenudialog.h \
    ../../Tools/ToolTestOpenQuestion/testopenquestionmaindialog.h \
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
#    ../../Classes/CppExercise/exercise.h \
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
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppShinyButton/shinybutton.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppSimpleLinearRegression/simplelinearregression.h \
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
    ../../Games/GameBeerWanter/beerwantermenudialog.h \
    ../../Games/GameBoenken/boenkenarenasettings.h \
    ../../Games/GameBoenken/boenkencontrols.h \
    ../../Games/GameBoenken/boenkenmenudialog.h \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.h \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h \
    ../../Games/GameK3OpEenRij/k3opeenrijmenudialog.h \
    ../../Games/GameMaziak/maziakmenudialog.h \
    ../../Games/GamePylos/pylosmenudialog.h \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.h \
    ../../Games/GameTicTacToe/tictactoemenudialog.h \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.h \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.h \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h \
    ../../Tools/ToolCreateGlossary/createglossarymaindialog.h \
    ../../Tools/ToolCreateGlossary/createglossarymenudialog.h \
    ../../Tools/ToolEncranger/toolencrangermaindialog.h \
    ../../Tools/ToolEncranger/toolencrangermenudialog.h \
    ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.h \
    ../../Tools/ToolGrayCoder/toolgraycodermaindialog.h \
    ../../Tools/ToolGrayCoder/toolgraycodermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainerresources.h \
    ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.h \
    ../../Tools/ToolMazeCreator/mazecreatormenudialog.h \
    ../../Tools/ToolMultiEncranger/toolmultiencrangermenudialog.h \
    ../../Tools/ToolMusicTheory/musictheorymenudialog.h \
    ../../Tools/ToolPerfectElasticCollision/perfectelasticcollisionmenudialog.h \
    ../../Tools/ToolPicToCode/pictocodemaindialog.h \
    ../../Tools/ToolPicToCode/pictocodemenudialog.h \
    ../../Tools/ToolQmakeWatcher/qmakewatchermenudialog.h \
    ../../Tools/ToolRandomCode/randomcodemenudialog.h \
    ../../Tools/ToolRegexTester/regextesterboostregexmaindialog.h \
    ../../Tools/ToolRegexTester/regextesterboostxpressivemaindialog.h \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.h \
    ../../Tools/ToolRegexTester/regextestermaindialog.h \
    ../../Tools/ToolRegexTester/regextestermenudialog.h \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.h \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.h \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.h \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h \
    ../../Tools/ToolSimplifyNewick/toolsimplifynewickmaindialog.h \
    ../../Tools/ToolSimplifyNewick/toolsimplifynewickmenudialog.h \
    ../../Tools/ToolStateObserver/noisefunctionparser.h \
    ../../Tools/ToolStateObserver/stateobservermenudialog.h \
    ../../Tools/ToolTestApproximator/tooltestapproximatormenudialog.h \
    ../../Tools/ToolTestCanvas/tooltestcanvasmenudialog.h \
    ../../Tools/ToolTestDial/testdialmenudialog.h \
    ../../Tools/ToolTestEntrance/testentrancemenudialog.h \
    ../../Tools/ToolTestExercise/testexercisemenudialog.h \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.h \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.h \
    ../../Tools/ToolTestLed/tooltestledmenudialog.h \
    ../../Tools/ToolTestMultiApproximator/tooltestmultiapproximatormenudialog.h \
    ../../Tools/ToolTestMultipleChoiceQuestion/testmultiplechoicequestionmaindialog.h \
    ../../Tools/ToolTestMultipleChoiceQuestion/testmultiplechoicequestionmenudialog.h \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestPylos/testpylosmenudialog.h \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/testqtkeyboardfriendlygraphicsviewmenudialog.h \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/testqtkeyboardfriendlygraphicsviewmenudialog.h \
    ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestShape/testshapemaindialog.h \
    ../../Tools/ToolTestShape/testshapemaindialog.h \
    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestSimpleLinearRegression/tooltestsimplelinearregressionmenudialog.h \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    ../../Tools/ToolMultiEncranger/toolmultiencrangermaindialog.h \
    ../../Classes/CppCanvas/canvas.h \
    ../../Tools/ToolQuadraticSolver/quadraticsolvermenudialog.h \
    ../../Tools/ToolQuadraticSolver/quadraticsolvermaindialog.h \
    ../../Tools/ToolPrimeExpert/toolprimeexpertmenudialog.h \
    ../../Tools/ToolPrimeExpert/primeexpert.h \
    ../../Tools/ToolDotMatrix/tooldotmatrixmenudialog.h \
    ../../Classes/CppDotMatrix/dotmatrixstring.h \
    ../../Classes/CppDotMatrix/dotmatrixchar.h \
    ../../Classes/CppFileIo/fileio.h \
    ../../Tools/ToolHometrainer/hometrainermaindialog.h \
    ../../Classes/CppMenuDialog/menudialog.h \
    ../../Classes/CppHelp/help.h


#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
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

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
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

# .pro and .pri file use
#
# The general rule is this:
# - Each .pri file only contains filenames for its own folder,
#   including other .pri files from that same folder
# - Each .pro file contains more specific directions
#
# Suppose a program called X:
# - XConsole.pro: includes XConsole.pri
# - XDesktop.pro: includes XDesktop.pri, XDesktop.pri includes XConsole.pri
# - XWebsite.pro: includes XWebsite.pri, XWebsite.pri includes XConsole.pri
#
# Additionally:
# - All .pro file must add their libraries and compiler settings
# - XConsole.pro: must add its own non-X-folder items
# - XDesktop.pro: must add its own non-X-folder items,
#     note that this .pro file will have overlap with XConsole.pro
# - XWebsite.pro: must add its own non-X-folder items,
#     note that this .pro file will have overlap with XConsole.pro
#
# ProjectRichelBilderbeek:
# - ProjectRichelBilderbeekConsole: includes XConsole.pri
# - ProjectRichelBilderbeekDesktop: includes XDesktop.pri
# - ProjectRichelBilderbeekWebsite: includes XWebsite.pri
#
# For ProjectRichelBilderbeek to be able to call XY.pri, the following is needed:
# - XY.pri must only call files from its own folder
# - XY.pri must add its own folder to INCLUDEPATH
#
#
#
#
# Example:
#
# XConsole.pri:
#    SOURCES += ../../Tools/ToolConsole/console.cpp
#    HEADERS += ../../Tools/ToolConsole/console.h
#
# XDesktop.pri:
#    include(XConsole.pri); # Perhaps include(../../Tools/ToolConsole/XConsole.pri)
#    SOURCES += ../../Tools/ToolConsole/qtconsole.cpp
#    HEADERS += ../../Tools/ToolConsole/qtconsole.h
#
# XConsole.pro:
#    include(XConsole.pri); # Perhaps include(../../Tools/ToolConsole/XConsole.pri)
#    include(../../Classes/CppAbout/about.pri)
#    SOURCES += main.cpp
#    CONFIG += console
#
# XDesktop.pro:
#    include(XDesktop.pri); # Perhaps include(../../Tools/ToolConsole/XDesktop.pri)
#    SOURCES += qtmain.cpp
#    include(../../Classes/CppAbout/about.pri)
#    include(../../Classes/CppQtAbout/qtabout.pri)
#    CONFIG -= console
#
#
# ProjectRichelBilderbeekConsole.pri:
#    include(../../Tools/ToolConsole/XConsole.pri)
#    include(../../Classes/CppAbout/about.pri)
#    SOURCES += ../../Projects/ProjectRichelBilderbeek/maindialog.cpp
#    SOURCES += ../../Projects/ProjectRichelBilderbeek/maindialog.h
#
# ProjectRichelBilderbeekDesktop.pri:
#    include(ProjectRichelBilderbeekConsole.pri)
#    SOURCES += ../../Projects/ProjectRichelBilderbeek/qtmaindialog.cpp
#    SOURCES += ../../Projects/ProjectRichelBilderbeek/qtmaindialog.h
#
#
# ProjectRichelBilderbeekConsole.pro:
#    include(../../Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekConsole.pri)
#    SOURCES += main.cpp
#    CONFIG += console
#
# ProjectRichelBilderbeekDesktop.pro:
#    include(../../Projects/ProjectRichelBilderbeek/ProjectRichelBilderbeekDesktop.pri)
#    SOURCES += qtmain.cpp
#    CONFIG -= console
#
#
#
#
