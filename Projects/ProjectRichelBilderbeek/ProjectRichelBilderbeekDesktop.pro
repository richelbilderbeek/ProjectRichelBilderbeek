win32 {
  #Add the line below when cross-compiling
  CONFIG += static
}

QT += core gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app



INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppAsciiArter \
    ../../Classes/CppBinaryNewickVector \
    ../../Classes/CppChess \
    ../../Classes/CppChessResources \
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
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtArrowItem \
    ../../Classes/CppQtChess \
    ../../Classes/CppQtConnectThreeWidget \
    ../../Classes/CppQtCreatorProFile \
    ../../Classes/CppQtDialWidget \
    ../../Classes/CppQtDisplayPosItem \
    ../../Classes/CppQtExercise \
    ../../Classes/CppQtGaborFilterWidget \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView \
    ../../Classes/CppQtLabeledQuadBezierArrowItem \
    ../../Classes/CppQtLedWidget \
    ../../Classes/CppQtLeftRightRectItem \
    ../../Classes/CppQtMatrix \
    ../../Classes/CppQtModel \
    ../../Classes/CppQtMultipleChoiceQuestionDialog \
    ../../Classes/CppQtMysteryMachineWidget \
    ../../Classes/CppQtOpenQuestionDialog \
    ../../Classes/CppQtPathArrowItem \
    ../../Classes/CppQtPylos \
    ../../Classes/CppQtQuadBezierArrowItem \
    ../../Classes/CppQtQuestionDialog \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog \
    ../../Classes/CppQtRoundedEditRectItem \
    ../../Classes/CppQtRoundedRectItem \
    ../../Classes/CppQtRoundedTextRectItem \
    ../../Classes/CppQtRubiksClockWidget \
    ../../Classes/CppQtShapeWidget \
    ../../Classes/CppQtShinyButtonWidget \
    ../../Classes/CppQtSprites \
    ../../Classes/CppQtTicTacToeWidget \
    ../../Classes/CppQtToggleButtonWidget \
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
    ../../Games/GameBeerWanter \
    ../../Games/GameBoenken \
    ../../Games/GameConnectThree \
    ../../Games/GameDasWahreSchlagerfest \
    ../../Games/GameMaziak \
    ../../Games/GamePylos \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateGlossary \
    ../../Tools/ToolCreateQtProjectZipFile \
    ../../Tools/ToolGaborFilter \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolKalmanFilterer \
    ../../Tools/ToolMazeCreator \
    ../../Tools/ToolMusicTheory \
    ../../Tools/ToolPerfectElasticCollision \
    ../../Tools/ToolPicToCode \
    ../../Tools/ToolRandomCode \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolRichelBilderbeekGallery \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolStateObserver \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestEncranger \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestNewickVector \
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
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick \
    ../../Projects/RichelbilderbeekNl

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppAsciiArter/asciiarter.cpp \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.cpp \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.cpp \
    ../../Classes/CppCodeToHtml/codetohtml.cpp \
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
    ../../Classes/CppQtModel/modelfunctionparser.cpp \
    ../../Tools/ToolPause/pausemenudialog.cpp \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.cpp \
    ../../Tools/ToolStateObserver/stateobservermenudialog.cpp \
    ../../Tools/ToolStateObserver/slidingmodeobserver.cpp \
    ../../Tools/ToolStateObserver/qtstateobservermenudialog.cpp \
    ../../Tools/ToolStateObserver/qtstateobservermaindialog.cpp \
    ../../Tools/ToolStateObserver/noisefunctionparser.cpp \
    ../../Tools/ToolStateObserver/lsqfilter.cpp \
    ../../Classes/CppStateObserver/multialphafilter.cpp \
    ../../Classes/CppStateObserver/alphafilter.cpp \
    ../../Classes/CppStateObserver/alphabetagammafilter.cpp \
    ../../Classes/CppStateObserver/alphabetafilter.cpp \
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
    ../../Classes/CppLazy_init/lazy_init.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewick.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.cpp \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMusic/musicchord.cpp \
    ../../Classes/CppMusic/musicnote.cpp \
    ../../Classes/CppMusic/musicscale.cpp \
    ../../Classes/CppMysteryMachine/mysterymachine.cpp \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.cpp \
    ../../Classes/CppNewick/newick.cpp \
    ../../Classes/CppNewick/newickcpp98.cpp \
    ../../Classes/CppNewickVector/newickvector.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
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
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.cpp \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.cpp \
    ../../Classes/CppQtDialWidget/qtdialwidget.cpp \
    ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtLedWidget/qtledwidget.cpp \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.cpp \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp \
    ../../Classes/CppQtPylos/qtpylosboardwidget.cpp \
    ../../Classes/CppQtPylos/qtpylosgamewidget.cpp \
    ../../Classes/CppQtPylos/qtpylossprites.cpp \
    ../../Classes/CppQtPylos/qtpyloswidget.cpp \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.cpp \
    ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.cpp \
    ../../Classes/CppQtShapeWidget/qtshapewidget.cpp \
    ../../Classes/CppQtShinyButtonWidget/qtshinybuttonwidget.cpp \
    ../../Classes/CppQtSprites/qtsprites.cpp \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.cpp \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRubiksClock/rubiksclock.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.cpp \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppShinyButton/shinybutton.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.cpp \
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
    ../../Games/GameBeerWanter/qtbeerwantermaindialog.cpp \
    ../../Games/GameBeerWanter/qtbeerwantermenudialog.cpp \
    ../../Games/GameBeerWanter/qtbeerwanterwidget.cpp \
    ../../Games/GameBoenken/boenkengame.cpp \
    ../../Games/GameBoenken/boenkenmenudialog.cpp \
    ../../Games/GameBoenken/boenkenspriteball.cpp \
    ../../Games/GameBoenken/boenkensprite.cpp \
    ../../Games/GameBoenken/boenkenspritemoving.cpp \
    ../../Games/GameBoenken/boenkenspritenonmoving.cpp \
    ../../Games/GameBoenken/boenkenspriteplayer.cpp \
    ../../Games/GameBoenken/qtboenkenarenadialog.cpp \
    ../../Games/GameBoenken/qtboenkencontrolsdialog.cpp \
    ../../Games/GameBoenken/qtboenkenmaindialog.cpp \
    ../../Games/GameBoenken/qtboenkenmenudialog.cpp \
    ../../Games/GameBoenken/qtboenkenplayersdialog.cpp \
    ../../Games/GameBoenken/qtboenkenpresskeydialog.cpp \
    ../../Games/GameBoenken/qtboenkentraindialog.cpp \
    ../../Games/GameConnectThree/connectthreemenudialog.cpp \
    ../../Games/GameConnectThree/connectthreeresources.cpp \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/qtconnectthreeresources.cpp \
    ../../Games/GameConnectThree/qtselectplayerwidget.cpp \
    ../../Games/GameConnectThree/qtshowwinnerdialog.cpp \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.cpp \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.cpp \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.cpp \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.cpp \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.cpp \
    ../../Games/GameMaziak/maziakmenudialog.cpp \
    ../../Games/GameMaziak/qtmaziakgameoverdialog.cpp \
    ../../Games/GameMaziak/qtmaziakgamewondialog.cpp \
    ../../Games/GameMaziak/qtmaziakinstructionsdialog.cpp \
    ../../Games/GameMaziak/qtmaziakmaindialog.cpp \
    ../../Games/GameMaziak/qtmaziakmenudialog.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp \
    ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.cpp \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.cpp \
    ../../Games/GamePylos/pylosmenudialog.cpp \
    ../../Games/GamePylos/qtpylosinstructionsdialog.cpp \
    ../../Games/GamePylos/qtpylosmaindialog.cpp \
    ../../Games/GamePylos/qtpylosmenudialog.cpp \
    ../../Games/GamePylos/qtpyloswondialog.cpp \
    ../../Games/GameRubiksClock/qtrubiksclockmaindialog.cpp \
    ../../Games/GameRubiksClock/qtrubiksclockmenudialog.cpp \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp \
    ../../Games/GameTicTacToe/qttictactoegamedialog.cpp \
    ../../Games/GameTicTacToe/qttictactoemenudialog.cpp \
    ../../Games/GameTicTacToe/qttictactoewinnerdialog.cpp \
    ../../Games/GameTicTacToe/tictactoemenudialog.cpp \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.cpp \
    qtmain.cpp \
    qtrichelbilderbeekmenudialog.cpp \
    richelbilderbeekmenudialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp \
    ../../Tools/ToolAsciiArter/qtasciiartermaindialog.cpp \
    ../../Tools/ToolAsciiArter/qtasciiartermenudialog.cpp \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.cpp \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.cpp \
    ../../Tools/ToolCreateGlossary/createglossarymaindialog.cpp \
    ../../Tools/ToolCreateGlossary/createglossarymenudialog.cpp \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.cpp \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.cpp \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.cpp \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.cpp \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.cpp \
    ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/hometrainerresources.cpp \
    ../../Tools/ToolMazeCreator/mazecreatormenudialog.cpp \
    ../../Tools/ToolMazeCreator/qtmazecreatormaindialog.cpp \
    ../../Tools/ToolMazeCreator/qtmazecreatormenudialog.cpp \
    ../../Tools/ToolMusicTheory/musictheorymenudialog.cpp \
    ../../Tools/ToolMusicTheory/qtchordedge.cpp \
    ../../Tools/ToolMusicTheory/qtchordrelationswidget.cpp \
    ../../Tools/ToolMusicTheory/qtchordvertex.cpp \
    ../../Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.cpp \
    ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.cpp \
    ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.cpp \
    ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.cpp \
    ../../Tools/ToolPerfectElasticCollision/perfectelasticcollisionmenudialog.cpp \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmaindialog.cpp \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmenudialog.cpp \
    ../../Tools/ToolPicToCode/pictocodemaindialog.cpp \
    ../../Tools/ToolPicToCode/pictocodemenudialog.cpp \
    ../../Tools/ToolPicToCode/qtpictocodemaindialog.cpp \
    ../../Tools/ToolPicToCode/qtpictocodemenudialog.cpp \
    ../../Tools/ToolRandomCode/qtrandomcodemaindialog.cpp \
    ../../Tools/ToolRandomCode/qtrandomcodemenudialog.cpp \
    ../../Tools/ToolRandomCode/randomcodemenudialog.cpp \
    ../../Tools/ToolRichelBilderbeekGallery/qtrichelbilderbeekgallerymenudialog.cpp \
    ../../Tools/ToolRichelBilderbeekGallery/richelbilderbeekgallerymenudialog.cpp \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.cpp \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.cpp \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.cpp \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.cpp \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.cpp \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.cpp \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.cpp \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp \
    ../../Tools/ToolTestDial/qttestdialmaindialog.cpp \
    ../../Tools/ToolTestDial/qttestdialmenudialog.cpp \
    ../../Tools/ToolTestDial/testdialmenudialog.cpp \
    ../../Tools/ToolTestEncranger/qttestencrangerdialog.cpp \
    ../../Tools/ToolTestEncranger/testencrangerdialog.cpp \
    ../../Tools/ToolTestExercise/testexercisemenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.cpp \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestLed/qttestleddialog.cpp \
    ../../Tools/ToolTestLed/testledmenudialog.cpp \
    ../../Tools/ToolTestNewickVector/qttestnewickvectordialog.cpp \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.cpp \
    ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.cpp \
    ../../Tools/ToolTestPylos/qttestpylosmenudialog.cpp \
    ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.cpp \
    ../../Tools/ToolTestPylos/qttestpylostestboarddialog.cpp \
    ../../Tools/ToolTestPylos/qttestpylostestgamedialog.cpp \
    ../../Tools/ToolTestPylos/testpylosmenudialog.cpp \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemaindialog.cpp \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemenudialog.cpp \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemaindialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemenudialog.cpp \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.cpp \
    ../../Tools/ToolTestShape/qttestshapemaindialog.cpp \
    ../../Tools/ToolTestShape/qttestshapemenudialog.cpp \
    ../../Tools/ToolTestShape/testshapemaindialog.cpp \
    ../../Tools/ToolTestShape/testshapemenudialog.cpp \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmaindialog.cpp \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmaindialog.cpp \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.cpp \
    ../../Tools/ToolTestTwoDigitNewick/qttesttwodigitnewickdialog.cpp \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.cpp \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestermenudialog.cpp \
    ../../Tools/ToolRegexTester/regextestermaindialog.cpp \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.cpp \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.cpp \
    ../../Tools/ToolRegexTester/qtregextestermenudialog.cpp \
    ../../Tools/ToolRegexTester/qtregextestermaindialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp \
    ../../Tools/ToolTestQuestion/qttestquestionmenudialog.cpp \
    ../../Tools/ToolTestQuestion/qttestquestionmaindialog.cpp \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.cpp \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.cpp \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.cpp \
    ../../Classes/CppQtArrowItem/qtarrowitem.cpp \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.cpp \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.cpp \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.cpp \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.cpp \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.cpp \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.cpp \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/testqtkeyboardfriendlygraphicsviewmenudialog.cpp \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/qttestqtkeyboardfriendlygraphicsviewwidget.cpp \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/qttestqtkeyboardfriendlygraphicsviewmenudialog.cpp \
    ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.cpp \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.cpp \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.cpp \
    ../../Classes/CppQtDisplayPosItem/qtdisplaypositem.cpp \
    ../../Classes/CppQtLeftRightRectItem/qtleftrightrectitem.cpp \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.cpp \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.cpp \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.cpp \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.cpp \
    ../../Classes/CppMatrix/matrix.cpp \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.cpp \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.cpp \
    qtrichelbilderbeekmenuitemwidget.cpp \
    qtrichelbilderbeekprogram.cpp \
    ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermodel.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.cpp \
    ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.cpp \
    ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/whitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.cpp \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.cpp \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/kalmanfilter.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.cpp \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.cpp \
    ../../Classes/CppQtMatrix/qtmatrix.cpp \
    ../../Classes/CppQtExercise/qtexercise.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppAsciiArter/asciiarter.h \
    ../../Classes/CppAssert/assert.h \
    ../../Classes/CppBinaryNewickVector/binarynewickvector.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontent.h \
    ../../Classes/CppCodeToHtml/codetohtmlcontenttype.h \
    ../../Classes/CppCodeToHtml/codetohtmlcreateemptypagedialog.h \
    ../../Classes/CppCodeToHtml/codetohtmldialog.h \
    ../../Classes/CppCodeToHtml/codetohtmlfooter.h \
    ../../Classes/CppCodeToHtml/codetohtml.h \
    ../../Classes/CppCodeToHtml/codetohtmlheader.h \
    ../../Classes/CppCodeToHtml/codetohtmlinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmlpagetype.h \
    ../../Classes/CppCodeToHtml/codetohtmlreplacements.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfo.h \
    ../../Classes/CppCodeToHtml/codetohtmltechinfotype.h \
    ../../Classes/CppCodeToHtml/codetohtmlversion.h \
    ../../Classes/CppConnectThree/connectthree.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h \
    ../../Tools/ToolTestQtRoundedRectItem/testqtroundedrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemwidget.h \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.h \
    ../../Classes/CppConnectThreeWidget/connectthreewidget.h \
    ../../Classes/CppCopy_if/copy_if.h \
    ../../Classes/CppCounter/counter.h \
    ../../Classes/CppQtModel/modelfunctionparser.h \
    ../../Tools/ToolPause/pausemenudialog.h \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.h \
    ../../Tools/ToolStateObserver/stateobservermenudialog.h \
    ../../Tools/ToolStateObserver/slidingmodeobserver.h \
    ../../Tools/ToolStateObserver/qtstateobservermenudialog.h \
    ../../Tools/ToolStateObserver/qtstateobservermaindialog.h \
    ../../Tools/ToolStateObserver/noisefunctionparser.h \
    ../../Tools/ToolStateObserver/lsqfilter.h \
    ../../Classes/CppStateObserver/multialphafilter.h \
    ../../Classes/CppStateObserver/alphafilter.h \
    ../../Classes/CppStateObserver/alphabetagammafilter.h \
    ../../Classes/CppStateObserver/alphabetafilter.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppExercise/exercise.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppGaborFilter/gaborfilter.h \
    ../../Classes/CppGaborFilterWidget/gaborfilterwidget.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppIpAddress/ipaddress.h \
    ../../Classes/CppLazy_init/lazy_init.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickcoordinat.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickderivative.h \
    ../../Classes/CppManyDigitNewick/manydigitnewick.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindexer.h \
    ../../Classes/CppManyDigitNewick/manydigitnewickindextable.h \
    ../../Classes/CppManyDigitNewick/manydigitnewicks.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultiVector/multivector.h \
    ../../Classes/CppMusic/musicchord.h \
    ../../Classes/CppMusic/musicnote.h \
    ../../Classes/CppMusic/musicscale.h \
    ../../Classes/CppMysteryMachine/mysterymachine.h \
    ../../Classes/CppMysteryMachineWidget/mysterymachinewidget.h \
    ../../Classes/CppNewick/newickcpp98.h \
    ../../Classes/CppNewick/newick.h \
    ../../Classes/CppNewick/newickstorage.h \
    ../../Classes/CppNewickVector/newickvector.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
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
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtArrowItem/qtarrowitem.h \
    ../../Classes/CppQtConnectThreeWidget/qtconnectthreewidget.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofile.h \
    ../../Classes/CppQtCreatorProFile/qtcreatorprofilezipscript.h \
    ../../Classes/CppQtDialWidget/qtdialwidget.h \
    ../../Classes/CppQtGaborFilterWidget/qtgaborfilterwidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/qtkeyboardfriendlygraphicsview.h \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/qtlabeledquadbezierarrowitem.h \
    ../../Classes/CppQtLedWidget/qtledwidget.h \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h \
    ../../Classes/CppQtMysteryMachineWidget/qtmysterymachinewidget.h \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h \
    ../../Classes/CppQtPathArrowItem/qtpatharrowitem.h \
    ../../Classes/CppQtPylos/qtpylosboardwidget.h \
    ../../Classes/CppQtPylos/qtpylosgamewidget.h \
    ../../Classes/CppQtPylos/qtpylossprites.h \
    ../../Classes/CppQtPylos/qtpyloswidget.h \
    ../../Classes/CppQtQuadBezierArrowItem/qtquadbezierarrowitem.h \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.h \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.h \
    ../../Classes/CppQtRoundedRectItem/qtroundedrectitem.h \
    ../../Classes/CppQtRoundedTextRectItem/qtroundedtextrectitem.h \
    ../../Classes/CppQtRubiksClockWidget/qtrubiksclockwidget.h \
    ../../Classes/CppQtShapeWidget/qtshapewidget.h \
    ../../Classes/CppQtShinyButtonWidget/qtshinybuttonwidget.h \
    ../../Classes/CppQtSprites/qtsprites.h \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.h \
    ../../Classes/CppQtToggleButtonWidget/qttogglebuttonwidget.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppRainbow/rainbow.h \
    ../../Classes/CppRandomCode/randomcode.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.h \
    ../../Classes/CppRubiksClock/rubiksclock.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdial.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockdialwidget.h \
    ../../Classes/CppRubiksClockWidget/rubiksclockwidget.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppShinyButton/shinybutton.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppSortedBinaryNewickVector/sortedbinarynewickvector.h \
    ../../Classes/CppStopwatch/stopwatch.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppToggleButton/togglebutton.h \
    ../../Classes/CppToggleButtonWidget/togglebuttonwidget.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickderivative.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewick.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindexer.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewickindextable.h \
    ../../Classes/CppTwoDigitNewick/twodigitnewicks.h \
    ../../Classes/CppWidget/widget.h \
    ../../Games/GameBeerWanter/beerwantermaindialog.h \
    ../../Games/GameBeerWanter/beerwantermenudialog.h \
    ../../Games/GameBeerWanter/qtbeerwantermaindialog.h \
    ../../Games/GameBeerWanter/qtbeerwantermenudialog.h \
    ../../Games/GameBeerWanter/qtbeerwanterwidget.h \
    ../../Games/GameBoenken/boenkenarenasettings.h \
    ../../Games/GameBoenken/boenkencontrols.h \
    ../../Games/GameBoenken/boenkengame.h \
    ../../Games/GameBoenken/boenkenmenudialog.h \
    ../../Games/GameBoenken/boenkenspriteball.h \
    ../../Games/GameBoenken/boenkensprite.h \
    ../../Games/GameBoenken/boenkenspritemoving.h \
    ../../Games/GameBoenken/boenkenspritenonmoving.h \
    ../../Games/GameBoenken/boenkenspriteplayer.h \
    ../../Games/GameBoenken/qtboenkenarenadialog.h \
    ../../Games/GameBoenken/qtboenkencontrolsdialog.h \
    ../../Games/GameBoenken/qtboenkenmaindialog.h \
    ../../Games/GameBoenken/qtboenkenmenudialog.h \
    ../../Games/GameBoenken/qtboenkenplayersdialog.h \
    ../../Games/GameBoenken/qtboenkenpresskeydialog.h \
    ../../Games/GameBoenken/qtboenkentraindialog.h \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/qtconnectthreeresources.h \
    ../../Games/GameConnectThree/qtselectplayerwidget.h \
    ../../Games/GameConnectThree/qtshowwinnerdialog.h \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestmenudialog.h \
    ../../Games/GameDasWahreSchlagerfest/daswahreschlagerfestwidget.h \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.h \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.h \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestwidget.h \
    ../../Games/GameMaziak/maziakmenudialog.h \
    ../../Games/GameMaziak/qtmaziakgameoverdialog.h \
    ../../Games/GameMaziak/qtmaziakgamewondialog.h \
    ../../Games/GameMaziak/qtmaziakinstructionsdialog.h \
    ../../Games/GameMaziak/qtmaziakmaindialog.h \
    ../../Games/GameMaziak/qtmaziakmenudialog.h \
    ../../Games/GamePylos/pylosmenudialog.h \
    ../../Games/GamePylos/qtpylosinstructionsdialog.h \
    ../../Games/GamePylos/qtpylosmaindialog.h \
    ../../Games/GamePylos/qtpylosmenudialog.h \
    ../../Games/GamePylos/qtpyloswondialog.h \
    ../../Games/GameRubiksClock/qtrubiksclockmaindialog.h \
    ../../Games/GameRubiksClock/qtrubiksclockmenudialog.h \
    ../../Games/GameRubiksClock/rubiksclockmenudialog.h \
    ../../Games/GameTicTacToe/qttictactoegamedialog.h \
    ../../Games/GameTicTacToe/qttictactoemenudialog.h \
    ../../Games/GameTicTacToe/qttictactoewinnerdialog.h \
    ../../Games/GameTicTacToe/tictactoemenudialog.h \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.h \
    qtrichelbilderbeekmenudialog.h \
    richelbilderbeekmenudialog.h \
    ../../Tools/ToolAsciiArter/asciiartermaindialog.h \
    ../../Tools/ToolAsciiArter/asciiartermenudialog.h \
    ../../Tools/ToolAsciiArter/qtasciiartermaindialog.h \
    ../../Tools/ToolAsciiArter/qtasciiartermenudialog.h \
    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.h \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.h \
    ../../Tools/ToolCreateGlossary/createglossarymaindialog.h \
    ../../Tools/ToolCreateGlossary/createglossarymenudialog.h \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.h \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.h \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.h \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.h \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.h \
    ../../Tools/ToolGaborFilter/toolgaborfiltermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainermenudialog.h \
    ../../Tools/ToolHometrainer/hometrainerresources.h \
    ../../Tools/ToolMazeCreator/mazecreatormenudialog.h \
    ../../Tools/ToolMazeCreator/qtmazecreatormaindialog.h \
    ../../Tools/ToolMazeCreator/qtmazecreatormenudialog.h \
    ../../Tools/ToolMusicTheory/musictheorymenudialog.h \
    ../../Tools/ToolMusicTheory/qtchordedge.h \
    ../../Tools/ToolMusicTheory/qtchordrelationswidget.h \
    ../../Tools/ToolMusicTheory/qtchordvertex.h \
    ../../Tools/ToolMusicTheory/qtmultiscalechordrelationswidget.h \
    ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.h \
    ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.h \
    ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.h \
    ../../Tools/ToolPerfectElasticCollision/perfectelasticcollisionmenudialog.h \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmaindialog.h \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmenudialog.h \
    ../../Tools/ToolPicToCode/pictocodemaindialog.h \
    ../../Tools/ToolPicToCode/pictocodemenudialog.h \
    ../../Tools/ToolPicToCode/qtpictocodemaindialog.h \
    ../../Tools/ToolPicToCode/qtpictocodemenudialog.h \
    ../../Tools/ToolRandomCode/qtrandomcodemaindialog.h \
    ../../Tools/ToolRandomCode/qtrandomcodemenudialog.h \
    ../../Tools/ToolRandomCode/randomcodemenudialog.h \
    ../../Tools/ToolRegexTester/qtregextestermaindialog.h \
    ../../Tools/ToolRegexTester/qtregextestermenudialog.h \
    ../../Tools/ToolRegexTester/regextesterboostmaindialog.h \
    ../../Tools/ToolRegexTester/regextestercpp11maindialog.h \
    ../../Tools/ToolRegexTester/regextestermaindialog.h \
    ../../Tools/ToolRegexTester/regextestermenudialog.h \
    ../../Tools/ToolRegexTester/regextesterqtmaindialog.h \
    ../../Tools/ToolRegexTester/regextestertr1maindialog.h \
    ../../Tools/ToolRichelBilderbeekGallery/qtrichelbilderbeekgallerymenudialog.h \
    ../../Tools/ToolRichelBilderbeekGallery/richelbilderbeekgallerymenudialog.h \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.h \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.h \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemapgeneratormenudialog.h \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.h \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.h \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.h \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.h \
    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h \
    ../../Tools/ToolTestDial/qttestdialmaindialog.h \
    ../../Tools/ToolTestDial/qttestdialmenudialog.h \
    ../../Tools/ToolTestDial/testdialmenudialog.h \
    ../../Tools/ToolTestEncranger/qttestencrangerdialog.h \
    ../../Tools/ToolTestEncranger/testencrangerdialog.h \
    ../../Tools/ToolTestExercise/testexercisemenudialog.h \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.h \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.h \
    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.h \
    ../../Tools/ToolTestLed/qttestleddialog.h \
    ../../Tools/ToolTestLed/testledmenudialog.h \
    ../../Tools/ToolTestNewickVector/qttestnewickvectordialog.h \
    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.h \
    ../../Tools/ToolTestPylos/qttestpylosmenudialog.h \
    ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.h \
    ../../Tools/ToolTestPylos/qttestpylostestboarddialog.h \
    ../../Tools/ToolTestPylos/qttestpylostestgamedialog.h \
    ../../Tools/ToolTestPylos/testpylosmenudialog.h \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemaindialog.h \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemenudialog.h \
    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.h \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtArrowItems/testqtarrowitemsmenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemaindialog.h \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/qttestqtkeyboardfriendlygraphicsviewmenudialog.h \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/qttestqtkeyboardfriendlygraphicsviewwidget.h \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/testqtkeyboardfriendlygraphicsviewmenudialog.h \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.h \
    ../../Tools/ToolTestQtModels/tooltestqtmodelsmenudialog.h \
    ../../Tools/ToolTestQuestion/qttestquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/qttestquestionmenudialog.h \
    ../../Tools/ToolTestQuestion/testquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestShape/qttestshapemaindialog.h \
    ../../Tools/ToolTestShape/qttestshapemenudialog.h \
    ../../Tools/ToolTestShape/testshapemaindialog.h \
    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmaindialog.h \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmenudialog.h \
    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmaindialog.h \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    ../../Tools/ToolTestTwoDigitNewick/qttesttwodigitnewickdialog.h \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.h \
    ../../Classes/CppQtDisplayPosItem/qtdisplaypositem.h \
    ../../Classes/CppQtLeftRightRectItem/qtleftrightrectitem.h \
    ../../Classes/CppQtModel/qtublasvectordoublemodel.h \
    ../../Classes/CppQtModel/qtublasmatrixdoublemodel.h \
    ../../Classes/CppQtModel/qtstdvectorstringmodel.h \
    ../../Classes/CppQtModel/qtstdvectorfunctionmodel.h \
    ../../Classes/CppMatrix/matrix.h \
    ../../Classes/CppQtRoundedEditRectItem/qtroundededitrectitem.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/testqtroundededitrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemwidget.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/testqtroundedtextrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemwidget.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.h \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.h \
    qtrichelbilderbeekmenuitemwidget.h \
    qtrichelbilderbeekprogram.h \
    ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.h \
    ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.h \
    ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentmodel.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermodel.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.h \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.h \
    ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.h \
    ../../Tools/ToolKalmanFilterer/kalmanfilterermenudialog.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtypes.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemtype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparametertype.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemparameter.h \
    ../../Classes/CppKalmanFilter/whitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/whitenoisesystem.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/steadystatekalmanfilter.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/standardwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/standardkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/standardkalmanfilter.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemparameters.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystemfactory.h \
    ../../Classes/CppKalmanFilter/laggedwhitenoisesystem.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertypes.h \
    ../../Classes/CppKalmanFilter/kalmanfiltertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/kalmanfilterparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparametertype.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperimentparameter.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexperiment.h \
    ../../Classes/CppKalmanFilter/kalmanfilterexample.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelementsfactory.h \
    ../../Classes/CppKalmanFilter/kalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/kalmanfilter.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterparameters.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilterfactory.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfiltercalculationelements.h \
    ../../Classes/CppKalmanFilter/fixedlagsmootherkalmanfilter.h \
    ../../Classes/CppQtMatrix/qtmatrix.h \
    ../../Classes/CppQtExercise/qtexercise.h


RESOURCES += \
    ../../Games/GameConnectThree/GameConnectThree.qrc \
    ../../Games/GameRubiksClock/GameRubiksClock.qrc \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtml.qrc \
    ../../Tools/ToolHometrainer/ToolHometrainer.qrc \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.qrc \
    ../../Tools/ToolAsciiArter/ToolAsciiArter.qrc \
    ../../Tools/ToolTestDial/ToolTestDial.qrc \
    ../../Tools/ToolTestExercise/ToolTestExercise.qrc \
    ../../Tools/ToolTestFunctionParser/ToolTestFunctionParser.qrc \
    ../../Tools/ToolTestGroupWidget/ToolTestGroupWidget.qrc \
    ../../Tools/ToolTestShape/ToolTestShape.qrc \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButton.qrc \
    ProjectRichelBilderbeek.qrc \
    ../../Tools/ToolTestNewickVector/ToolTestNewickVector.qrc \
    ../../Tools/ToolTestTwoDigitNewick/ToolTestTwoDigitNewick.qrc \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc \
    ../../Tools/ToolTestQtCreatorProFile/ToolTestQtCreatorProFile.qrc \
    ../../Classes/CppChessResources/chessresources.qrc \
    ../../Tools/ToolTestChess/ToolTestChess.qrc \
    ../../Games/GameBeerWanter/beerwanter.qrc \
    ../../Tools/ToolPicToCode/ToolPicToCode.qrc \
    ../../Tools/ToolMazeCreator/mazecreator.qrc \
    ../../Games/GameMaziak/gamemaziak.qrc \
    ../../Tools/ToolPerfectElasticCollision/ToolPerfectElasticCollision.qrc \
    ../../Games/GameBoenken/GameBoenken.qrc \
    ../../Tools/ToolTestPylos/ToolTestPylos.qrc \
    ../../Games/GamePylos/GamePylos.qrc \
    ../../Tools/ToolTestQrcFile/ToolTestQrcFile.qrc \
    ../../Games/GameTicTacToe/GameTicTacToe.qrc \
    ../../Tools/ToolRandomCode/ToolRandomCode.qrc \
    ../../Tools/ToolTestEncranger/ToolTestEncranger.qrc \
    ../../Tools/ToolTestLed/ToolTestLed.qrc \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButton.qrc \
    ../../Tools/ToolCreateQtProjectZipFile/ToolCreateQtProjectZipFile.qrc \
    ../../Games/GameDasWahreSchlagerfest/GameDasWahreSchlagerfest.qrc \
    ../../Tools/ToolGaborFilter/ToolGaborFilter.qrc \
    ../../Tools/ToolCreateGlossary/ToolCreateGlossary.qrc \
    ../../Tools/ToolMusicTheory/ToolMusicTheory.qrc \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/ToolRichelbilderbeekNlSitemapGenerator.qrc \
    ../../Tools/ToolRegexTester/ToolRegexTester.qrc \
    ../../Tools/ToolTestQuestion/ToolTestQuestion.qrc \
    ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.qrc \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/ToolTestQtKeyboardFriendlyGraphicsView.qrc \
    ../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItem.qrc \
    ../../Tools/ToolStateObserver/ToolStateObserver.qrc \
    ../../Tools/ToolTestQtRoundedEditRectItem/ToolTestQtRoundedEditRectItem.qrc \
    ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.qrc \
    ../../Tools/ToolKalmanFilterer/ToolKalmanFilterer.qrc

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui \
    ../../Classes/CppQtRichelBilderbeekGalleryDialog/qtrichelbilderbeekgallerydialog.ui \
    ../../Games/GameBeerWanter/qtbeerwantermaindialog.ui \
    ../../Games/GameBeerWanter/qtbeerwantermenudialog.ui \
    ../../Games/GameBoenken/qtboenkenarenadialog.ui \
    ../../Games/GameBoenken/qtboenkencontrolsdialog.ui \
    ../../Games/GameBoenken/qtboenkenmaindialog.ui \
    ../../Games/GameBoenken/qtboenkenmenudialog.ui \
    ../../Games/GameBoenken/qtboenkenplayersdialog.ui \
    ../../Games/GameBoenken/qtboenkenpresskeydialog.ui \
    ../../Games/GameBoenken/qtboenkentraindialog.ui \
    ../../Games/GameConnectThree/qtconnectthreegamedialog.ui \
    ../../Games/GameConnectThree/qtconnectthreemenudialog.ui \
    ../../Games/GameConnectThree/qtshowwinnerdialog.ui \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmaindialog.ui \
    ../../Games/GameDasWahreSchlagerfest/qtdaswahreschlagerfestmenudialog.ui \
    ../../Games/GameMaziak/qtmaziakgameoverdialog.ui \
    ../../Games/GameMaziak/qtmaziakgamewondialog.ui \
    ../../Games/GameMaziak/qtmaziakinstructionsdialog.ui \
    ../../Games/GameMaziak/qtmaziakmaindialog.ui \
    ../../Games/GameMaziak/qtmaziakmenudialog.ui \
    ../../Games/GamePylos/qtpylosinstructionsdialog.ui \
    ../../Games/GamePylos/qtpylosmaindialog.ui \
    ../../Games/GamePylos/qtpylosmenudialog.ui \
    ../../Games/GamePylos/qtpyloswondialog.ui \
    ../../Games/GameRubiksClock/qtrubiksclockmaindialog.ui \
    ../../Games/GameRubiksClock/qtrubiksclockmenudialog.ui \
    ../../Games/GameTicTacToe/qttictactoegamedialog.ui \
    ../../Games/GameTicTacToe/qttictactoemenudialog.ui \
    ../../Games/GameTicTacToe/qttictactoewinnerdialog.ui \
    qtrichelbilderbeekmenudialog.ui \
    ../../Tools/ToolAsciiArter/qtasciiartermaindialog.ui \
    ../../Tools/ToolAsciiArter/qtasciiartermenudialog.ui \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmaindialog.ui \
    ../../Tools/ToolCodeToHtml/qtcodetohtmlmenudialog.ui \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymaindialog.ui \
    ../../Tools/ToolCreateGlossary/qtcreateglossarymenudialog.ui \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemaindialog.ui \
    ../../Tools/ToolCreateQtProjectZipFile/qtcreateqtprojectzipfilemenudialog.ui \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermaindialog.ui \
    ../../Tools/ToolGaborFilter/qttoolgaborfiltermenudialog.ui \
    ../../Tools/ToolMazeCreator/qtmazecreatormaindialog.ui \
    ../../Tools/ToolMazeCreator/qtmazecreatormenudialog.ui \
    ../../Tools/ToolMusicTheory/qtmusictheorymenudialog.ui \
    ../../Tools/ToolMusicTheory/qtmusictheorymultiscaledialog.ui \
    ../../Tools/ToolMusicTheory/qtmusictheorysinglescaledialog.ui \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmaindialog.ui \
    ../../Tools/ToolPerfectElasticCollision/qtperfectelasticcollisionmenudialog.ui \
    ../../Tools/ToolPicToCode/qtpictocodemaindialog.ui \
    ../../Tools/ToolPicToCode/qtpictocodemenudialog.ui \
    ../../Tools/ToolRandomCode/qtrandomcodemaindialog.ui \
    ../../Tools/ToolRandomCode/qtrandomcodemenudialog.ui \
    ../../Tools/ToolRegexTester/qtregextestermaindialog.ui \
    ../../Tools/ToolRegexTester/qtregextestermenudialog.ui \
    ../../Tools/ToolRegexTester/qtregextesterremovedialog.ui \
    ../../Tools/ToolRichelBilderbeekGallery/qtrichelbilderbeekgallerymenudialog.ui \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormaindialog.ui \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/qtsitemapgeneratormenudialog.ui \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachineinstructionsdialog.ui \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemaindialog.ui \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinemenudialog.ui \
    ../../Tools/ToolSimMysteryMachine/qtsimmysterymachinerealmachinedialog.ui \
    ../../Tools/ToolTestChess/qttestchessboarddialog.ui \
    ../../Tools/ToolTestChess/qttestchessgamedialog.ui \
    ../../Tools/ToolTestChess/qttestchessmenudialog.ui \
    ../../Tools/ToolTestChess/qttestchessviewresourcesdialog.ui \
    ../../Tools/ToolTestDial/qttestdialmaindialog.ui \
    ../../Tools/ToolTestDial/qttestdialmenudialog.ui \
    ../../Tools/ToolTestEncranger/qttestencrangerdialog.ui \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermaindialog.ui \
    ../../Tools/ToolTestFunctionParser/qttestfunctionparsermenudialog.ui \
    ../../Tools/ToolTestLed/qttestleddialog.ui \
    ../../Tools/ToolTestNewickVector/qttestnewickvectordialog.ui \
    ../../Tools/ToolTestPylos/qttestpylosgametestsdialog.ui \
    ../../Tools/ToolTestPylos/qttestpylosmenudialog.ui \
    ../../Tools/ToolTestPylos/qttestpylosrandomplaydialog.ui \
    ../../Tools/ToolTestPylos/qttestpylostestboarddialog.ui \
    ../../Tools/ToolTestPylos/qttestpylostestgamedialog.ui \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemaindialog.ui \
    ../../Tools/ToolTestQrcFile/qttestqrcfilemenudialog.ui \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmaindialog.ui \
    ../../Tools/ToolTestQtArrowItems/qttestqtarrowitemsmenudialog.ui \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemaindialog.ui \
    ../../Tools/ToolTestQtCreatorProFile/qttestqtcreatorprofilemenudialog.ui \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/qttestqtkeyboardfriendlygraphicsviewmenudialog.ui \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmenudialog.ui \
    ../../Tools/ToolTestQuestion/qttestquestionmaindialog.ui \
    ../../Tools/ToolTestQuestion/qttestquestionmenudialog.ui \
    ../../Tools/ToolTestShape/qttestshapemaindialog.ui \
    ../../Tools/ToolTestShape/qttestshapemenudialog.ui \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmaindialog.ui \
    ../../Tools/ToolTestShinyButton/qttestshinybuttonmenudialog.ui \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmaindialog.ui \
    ../../Tools/ToolTestToggleButton/qttesttogglebuttonmenudialog.ui \
    ../../Tools/ToolTestTwoDigitNewick/qttesttwodigitnewickdialog.ui \
    ../../Tools/ToolTestQtModels/qttooltestqtmodelsmaindialog.ui \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmenudialog.ui \
    ../../Tools/ToolTestQtRoundedRectItem/qttestqtroundedrectitemmaindialog.ui \
    ../../Tools/ToolQmakeWatcher/qtqmakewatchermaindialog.ui \
    ../../Tools/ToolStateObserver/qtstateobservermenudialog.ui \
    ../../Tools/ToolStateObserver/qtstateobservermaindialog.ui \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmenudialog.ui \
    ../../Tools/ToolTestQtRoundedEditRectItem/qttestqtroundededitrectitemmaindialog.ui \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmenudialog.ui \
    ../../Tools/ToolTestQtRoundedTextRectItem/qttestqtroundedtextrectitemmaindialog.ui \
    ../../Tools/ToolKalmanFilterer/qtwhitenoisesystemparametersdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtsteadystatekalmanfiltercalculationdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtstandardkalmanfiltercalculationdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexperimentdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterexamplesdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltererparameterdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermenudialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterermaindialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfilterdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtkalmanfiltercalculationdialog.ui \
    ../../Tools/ToolKalmanFilterer/qtfixedlagsmootherkalmanfiltercalculationdialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
    ../../Classes/CppAssert/Licence.txt \
    ../../Classes/CppBinaryNewickVector/Licence.txt \
    ../../Classes/CppChess/Licence.txt \
    ../../Classes/CppChessResources/Licence.txt \
    ../../Classes/CppCodeToHtml/Licence.txt \
    ../../Classes/CppConnectThree/Licence.txt \
    ../../Classes/CppConnectThreeWidget/Licence.txt \
    ../../Classes/CppCopy_if/Licence.txt \
    ../../Classes/CppCounter/Licence.txt \
    ../../Classes/CppDial/Licence.txt \
    ../../Classes/CppDialWidget/Licence.txt \
    ../../Classes/CppEncranger/Licence.txt \
    ../../Classes/CppExercise/Licence.txt \
    ../../Classes/CppFuzzy_equal_to/Licence.txt \
    ../../Classes/CppGaborFilter/Licence.txt \
    ../../Tools/ToolTestQtRoundedRectItem/ToolTestQtRoundedRectItemWelcome.png \
    ../../Tools/ToolTestQtRoundedRectItem/R.png \
    ../../Tools/ToolTestQtRoundedRectItem/Licence.txt \
    ../../Classes/CppGaborFilterWidget/Licence.txt \
    ../../Classes/CppHtmlPage/Licence.txt \
    ../../Classes/CppIpAddress/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppPylos/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtArrowItem/Licence.txt \
    ../../Classes/CppQtChess/Licence.txt \
    ../../Classes/CppQtConnectThreeWidget/Licence.txt \
    ../../Classes/CppQtGaborFilterWidget/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    ../../Classes/CppQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Classes/CppQtLabeledQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtPathArrowItem/Licence.txt \
    ../../Classes/CppQtPylos/Licence.txt \
    ../../Classes/CppQtQuadBezierArrowItem/Licence.txt \
    ../../Classes/CppQtRoundedRectItem/Licence.txt \
    ../../Classes/CppQtRoundedTextRectItem/Licence.txt \
    ../../Classes/CppQtRubiksClockWidget/Licence.txt \
    ../../Classes/CppQtSprites/Licence.txt \
    ../../Classes/CppQtTicTacToeWidget/Licence.txt \
    ../../Classes/CppWtAutoConfig/Licence.txt \
    crosscompiletowindows.sh \
    ../../Games/GameBeerWanter/Beer.png \
    ../../Games/GameBeerWanter/Licence.txt \
    ../../Games/GameBeerWanter/PicR.png \
    ../../Games/GameBoenken/Computer.png \
    ../../Games/GameBoenken/Green.png \
    ../../Games/GameBoenken/Grey.png \
    ../../Games/GameBoenken/Human.png \
    ../../Games/GameBoenken/Licence.txt \
    ../../Games/GameBoenken/PlayerBlue.png \
    ../../Games/GameBoenken/PlayerRed.png \
    ../../Games/GameBoenken/R.png \
    ../../Games/GameConnectThree/ConnectThreeComputer1.png \
    ../../Games/GameConnectThree/ConnectThreeComputer2.png \
    ../../Games/GameConnectThree/ConnectThreeComputer3.png \
    ../../Games/GameConnectThree/ConnectThreeComputerGrey.png \
    ../../Games/GameConnectThree/ConnectThree.css \
    ../../Games/GameConnectThree/ConnectThreeEmpty.png \
    ../../Games/GameConnectThree/ConnectThreeGood1.png \
    ../../Games/GameConnectThree/ConnectThreeGood2.png \
    ../../Games/GameConnectThree/ConnectThreePlayer1Grey.png \
    ../../Games/GameConnectThree/ConnectThreePlayer1.png \
    ../../Games/GameConnectThree/ConnectThreePlayer2Grey.png \
    ../../Games/GameConnectThree/ConnectThreePlayer2.png \
    ../../Games/GameConnectThree/ConnectThreePlayer3Grey.png \
    ../../Games/GameConnectThree/ConnectThreePlayer3.png \
    ../../Games/GameConnectThree/ConnectThreeWrong.png \
    ../../Games/GameConnectThree/GameConnectThreeArchitecture_6_2.dia \
    ../../Games/GameConnectThree/GameConnectThreeArchitecture_6_2.png \
    ../../Games/GameConnectThree/GameConnectThreeWelcomeNoLegend.png \
    ../../Games/GameConnectThree/GameConnectThreeWelcome.png \
    ../../Games/GameMaziak/AboutPicture.png \
    ../../Games/GameMaziak/About.png \
    ../../Games/GameMaziak/Congratulations.png \
    ../../Games/GameMaziak/Easy_not_selected.png \
    ../../Games/GameMaziak/Easy_selected.png \
    ../../Games/GameMaziak/Empty.png \
    ../../Games/GameMaziak/Enemy1.png \
    ../../Games/GameMaziak/Enemy2.png \
    ../../Games/GameMaziak/Entrance.png \
    ../../Games/GameMaziak/Exit.png \
    ../../Games/GameMaziak/Fight2.png \
    ../../Games/GameMaziak/Fight3.png \
    ../../Games/GameMaziak/Fight4.png \
    ../../Games/GameMaziak/FightLost1.png \
    ../../Games/GameMaziak/FightLost2.png \
    ../../Games/GameMaziak/FightNoSword1.png \
    ../../Games/GameMaziak/FightSword1.png \
    ../../Games/GameMaziak/FightWon1.png \
    ../../Games/GameMaziak/FightWon2.png \
    ../../Games/GameMaziak/GameOver.png \
    ../../Games/GameMaziak/Gold.png \
    ../../Games/GameMaziak/Hard_not_selected.png \
    ../../Games/GameMaziak/Hard_selected.png \
    ../../Games/GameMaziak/Instructions.png \
    ../../Games/GameMaziak/Medium_not_selected.png \
    ../../Games/GameMaziak/Medium_selected.png \
    ../../Games/GameMaziak/Path.png \
    ../../Games/GameMaziak/PlayerLookDown.png \
    ../../Games/GameMaziak/PlayerLookDownSword.png \
    ../../Games/GameMaziak/PlayerLookLeft.png \
    ../../Games/GameMaziak/PlayerLookLeftSword.png \
    ../../Games/GameMaziak/PlayerLookRight.png \
    ../../Games/GameMaziak/PlayerLookRightSword.png \
    ../../Games/GameMaziak/PlayerLookUp.png \
    ../../Games/GameMaziak/PlayerLookUpSword.png \
    ../../Games/GameMaziak/PlayerScared.png \
    ../../Games/GameMaziak/PlayerWalkDown1.png \
    ../../Games/GameMaziak/PlayerWalkDown2.png \
    ../../Games/GameMaziak/PlayerWalkDownSword1.png \
    ../../Games/GameMaziak/PlayerWalkDownSword2.png \
    ../../Games/GameMaziak/PlayerWalkLeft1.png \
    ../../Games/GameMaziak/PlayerWalkLeft2.png \
    ../../Games/GameMaziak/PlayerWalkLeftSword1.png \
    ../../Games/GameMaziak/PlayerWalkLeftSword2.png \
    ../../Games/GameMaziak/PlayerWalkRight1.png \
    ../../Games/GameMaziak/PlayerWalkRight2.png \
    ../../Games/GameMaziak/PlayerWalkRightSword1.png \
    ../../Games/GameMaziak/PlayerWalkRightSword2.png \
    ../../Games/GameMaziak/PlayerWalkUp1.png \
    ../../Games/GameMaziak/PlayerWalkUp2.png \
    ../../Games/GameMaziak/PlayerWalkUpSword1.png \
    ../../Games/GameMaziak/PlayerWalkUpSword2.png \
    ../../Games/GameMaziak/PlayerWon1.png \
    ../../Games/GameMaziak/PlayerWon2.png \
    ../../Games/GameMaziak/Prisoner1.png \
    ../../Games/GameMaziak/Prisoner2.png \
    ../../Games/GameMaziak/Quit.png \
    ../../Games/GameMaziak/Rip.png \
    ../../Games/GameMaziak/R.png \
    ../../Games/GameMaziak/Start.png \
    ../../Games/GameMaziak/Sword.png \
    ../../Games/GameMaziak/Transparent.png \
    ../../Games/GameMaziak/Treasure.png \
    ../../Games/GameMaziak/Wall.png \
    ../../Games/GamePylos/Licence.txt \
    ../../Games/GameRubiksClock/GameRubiksClock.png \
    ../../Games/GameRubiksClock/GameRubiksClockWelcome_2_1.png \
    ../../Games/GameRubiksClock/GameRubiksClockWelcomeNoLegend.png \
    ../../Games/GameRubiksClock/Licence.txt \
    ../../Games/GameTicTacToe/GameTicTacToeArchitecture_1_5.dia \
    ../../Games/GameTicTacToe/Licence.txt \
    ../../Games/GameTicTacToe/O_big.png \
    ../../Games/GameTicTacToe/O.png \
    ../../Games/GameTicTacToe/RichelbilderbeekNlBackground.png \
    ../../Games/GameTicTacToe/R.png \
    ../../Games/GameTicTacToe/wt.css \
    ../../Games/GameTicTacToe/X_big.png \
    ../../Games/GameTicTacToe/X.png \
    ../../Tools/ToolAsciiArter/Licence.txt \
    ../../Tools/ToolAsciiArter/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolAsciiArter/ToolAsciiArterWelcome.png \
    ../../Tools/ToolAsciiArter/wt.css \
    ../../Tools/ToolCodeToHtml/Licence.txt \
    ../../Tools/ToolCodeToHtml/R.png \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtmlOverview.png \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtmlWelcomeNoText.png \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtmlWelcome.png \
    ../../Tools/ToolCreateGlossary/Licence.txt \
    ../../Tools/ToolCreateGlossary/R.png \
    ../../Tools/ToolCreateQtProjectZipFile/Licence.txt \
    ../../Tools/ToolHometrainer/Licence.txt \
    ../../Tools/ToolHometrainer/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseAdapter.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseAuks.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseBakMetFilters.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseCdSpelerNumarck.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseClouds.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDcc.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDi.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDimmerpack.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseDmxVrouwtje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseEffect.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseEuroMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseEuroVrouwtje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilterboekje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilterhouder.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFilter.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFiltervellen.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFlightcase.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFresnel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantLinks.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantRechts.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAlesis.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMiddenboven.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMidden.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsboven.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsonder.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelYamaha.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGordijnhaak.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseHaspel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackMannetjeMono.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeEnXlrVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKabeltester.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLamp500W.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplanDeBruiloften.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplan.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichttafel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdGrijs.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdSpeler.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdTransparent.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMicrofoonShureSm58.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMiniJackStereoVrouwJackStereoMan.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMonitorTorqueConnectors.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultimeterMetex.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultistekkerdoos.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseOn.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseOpwindstatief.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePar.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePc.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePriklijst.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseProfielspot.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseRcf322aAchterkant.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseRgbLamp.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSafety.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseScartMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSchukoVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseShureSm58.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpanningsmeterFluke.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakerEvent3000.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwSpeakonVrouw.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpringV2.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseStandenplot.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseStekkerdoos.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTbar.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTest.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussHaarspeld.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTruss.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussklem.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussPin.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussVerbindingsstuk.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtBasis.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtGeluid.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtLicht.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTulpMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVerloopstukje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamsonAchterkant.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamson.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVgaVrouwVgaVrouw.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVoetstatief.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhemGenummerd.bmp \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhem.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrVrouwtje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseZekering.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerManual.odt \
    ../../Tools/ToolHometrainer/ToolHometrainerQuestionmark.png \
    ../../Tools/ToolHometrainer/ToolHometrainerQuestion.png \
    ../../Tools/ToolHometrainer/ToolHometrainerTitle.png \
    ../../Tools/ToolHometrainer/ToolHometrainerWelcome.png \
    ../../Tools/ToolMusicTheory/crosscompiletowindows.sh \
    ../../Tools/ToolMusicTheory/R.png \
    ../../Tools/ToolMusicTheory/ToolMusicTheory.png \
    ../../Tools/ToolPerfectElasticCollision/Licence.txt \
    ../../Tools/ToolRandomCode/Licence.txt \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Tools/ToolRegexTester/PicBoost.png \
    ../../Tools/ToolRegexTester/PicCpp11.png \
    ../../Tools/ToolRegexTester/PicCppTr1.png \
    ../../Tools/ToolRegexTester/PicQt.png \
    ../../Tools/ToolRegexTester/PicR.png \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/Licence.txt \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemap_gen.py \
    ../../Tools/ToolSimMysteryMachine/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWelcome.png \
    ../../Tools/ToolSimMysteryMachine/wt.css \
    ../../Tools/ToolTestChess/ToolTestChess.odp \
    ../../Tools/ToolTestChess/ToolTestChessWelcome.png \
    ../../Tools/ToolTestDial/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestDial/ToolTestDialArchitecture.dia \
    ../../Tools/ToolTestDial/ToolTestDialArchitecture.png \
    ../../Tools/ToolTestDial/ToolTestDialWelcome_2_1.png \
    ../../Tools/ToolTestDial/wt.css \
    ../../Tools/ToolTestEncranger/Licence.txt \
    ../../Tools/ToolTestExercise/ToolTestExerciseQuestionmark.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseQuestion.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseWelcomeNoLegend.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseWelcome.png \
    ../../Tools/ToolTestExercise/wt.css \
    ../../Tools/ToolTestFunctionParser/Licence.txt \
    ../../Tools/ToolTestFunctionParser/ToolTestFunctionParserWelcome.png \
    ../../Tools/ToolTestLed/Licence.txt \
    ../../Tools/ToolTestNewickVector/Licence.txt \
    ../../Tools/ToolTestNewickVector/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestNewickVector/R.png \
    ../../Tools/ToolTestPylos/Licence.txt \
    ../../Tools/ToolTestPylos/R.png \
    ../../Tools/ToolTestPylos/ToolTestPylosCanMove.png \
    ../../Tools/ToolTestPylos/ToolTestPylosDoubleRemoveTest.png \
    ../../Tools/ToolTestPylos/ToolTestPylosMoveMustRemove.png \
    ../../Tools/ToolTestPylos/ToolTestPylosMustRemove.png \
    ../../Tools/ToolTestQrcFile/Licence.txt \
    ../../Tools/ToolTestQrcFile/R.png \
    ../../Tools/ToolTestQrcFile/ToolTestQrcFileWelcome.png \
    ../../Tools/ToolTestQtArrowItems/Licence.txt \
    ../../Tools/ToolTestQtArrowItems/R.png \
    ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.png \
    ../../Tools/ToolTestQtCreatorProFile/Licence.txt \
    ../../Tools/ToolTestQtCreatorProFile/PicR.png \
    ../../Tools/ToolTestQtCreatorProFile/ToolTestQtCreatorProFile.png \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/PicR14x14_opaque.png \
    ../../Tools/ToolTestQuestion/Questionmark.png \
    ../../Tools/ToolTestQuestion/question.png \
    ../../Tools/ToolTestQuestion/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionIcon14x14.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome1.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome2.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome.png \
    ../../Tools/ToolTestShape/ToolTestShapeArchitecture.dia \
    ../../Tools/ToolTestShape/ToolTestShapeArchitecture.png \
    ../../Tools/ToolTestShape/ToolTestShapeWelcome.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButton_1_0.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButtonWelcomeNoLegend.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButtonWelcome.png \
    ../../Tools/ToolTestToggleButton/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButtonArchitecture_1_0.dia \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButtonWelcome.png \
    ../../Tools/ToolTestToggleButton/wt.css \
    ../../Tools/ToolTestTwoDigitNewick/doxygen.txt \
    ../../Tools/ToolTestTwoDigitNewick/Licence.txt \
    ../../Tools/ToolTestTwoDigitNewick/R.png \
    ../../Tools/ToolTestTwoDigitNewick/testtwodigitnewicks.sh \
    ../../Tools/ToolTestQtModels/Licence.txt \
    ../../Classes/CppQtDisplayPosItem/Licence.txt \
    ../../Classes/CppQtLeftRightRectItem/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppQtRoundedEditRectItem/Licence.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFiltervellen.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFlightcase.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseFresnel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantLinks.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAchterkantRechts.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelAlesis.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMiddenboven.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantMidden.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsboven.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelBovenkantRechtsonder.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGeluidstafelYamaha.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseGordijnhaak.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseHaspel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackMannetjeMono.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseJackVrouwtjeEnXlrVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKabeltester.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseKrachtstroomVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLamp500W.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplanDeBruiloften.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichtplan.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseLichttafel.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdGrijs.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdSpeler.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMdTransparent.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMicrofoonShureSm58.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMiniJackStereoVrouwJackStereoMan.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMonitorTorqueConnectors.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultikabelVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultimeterMetex.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseMultistekkerdoos.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseOn.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseOpwindstatief.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePar.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePc.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExercisePriklijst.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseProfielspot.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseRcf322aAchterkant.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseRgbLamp.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSafety.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseScartMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSchukoVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseShureSm58.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpanningsmeterFluke.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakerEvent3000.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwSpeakonVrouw.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpeakonVrouwtjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseSpringV2.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseStandenplot.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseStekkerdoos.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTbar.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTest.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussHaarspeld.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTruss.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussklem.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussPin.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTrussVerbindingsstuk.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtBasis.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtGeluid.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTtLicht.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseTulpMannetje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVerloopstukje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamsonAchterkant.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVersterkerSamson.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVgaVrouwVgaVrouw.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseVoetstatief.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhemGenummerd.bmp \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseWijkenArnhem.txt \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrMannetjeConnector.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseXlrVrouwtje.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerExerciseZekering.jpg \
    ../../Tools/ToolHometrainer/ToolHometrainerManual.odt \
    ../../Tools/ToolHometrainer/ToolHometrainerQuestionmark.png \
    ../../Tools/ToolHometrainer/ToolHometrainerQuestion.png \
    ../../Tools/ToolHometrainer/ToolHometrainerTitle.png \
    ../../Tools/ToolHometrainer/ToolHometrainerWelcome.png \
    ../../Tools/ToolMusicTheory/crosscompiletowindows.sh \
    ../../Tools/ToolMusicTheory/R.png \
    ../../Tools/ToolMusicTheory/ToolMusicTheory.png \
    ../../Tools/ToolPerfectElasticCollision/Licence.txt \
    ../../Tools/ToolRandomCode/Licence.txt \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Tools/ToolRegexTester/PicBoost.png \
    ../../Tools/ToolRegexTester/PicCpp11.png \
    ../../Tools/ToolRegexTester/PicCppTr1.png \
    ../../Tools/ToolRegexTester/PicQt.png \
    ../../Tools/ToolRegexTester/PicR.png \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/Licence.txt \
    ../../Tools/ToolRichelbilderbeekNlSitemapGenerator/sitemap_gen.py \
    ../../Tools/ToolSimMysteryMachine/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.dia \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineArchitecture_1_0.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.png \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachineWelcome.png \
    ../../Tools/ToolSimMysteryMachine/wt.css \
    ../../Tools/ToolTestChess/ToolTestChess.odp \
    ../../Tools/ToolTestChess/ToolTestChessWelcome.png \
    ../../Tools/ToolTestDial/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestDial/ToolTestDialArchitecture.dia \
    ../../Tools/ToolTestDial/ToolTestDialArchitecture.png \
    ../../Tools/ToolTestDial/ToolTestDialWelcome_2_1.png \
    ../../Tools/ToolTestDial/wt.css \
    ../../Tools/ToolTestEncranger/Licence.txt \
    ../../Tools/ToolTestExercise/ToolTestExerciseQuestionmark.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseQuestion.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseWelcomeNoLegend.png \
    ../../Tools/ToolTestExercise/ToolTestExerciseWelcome.png \
    ../../Tools/ToolTestExercise/wt.css \
    ../../Tools/ToolTestFunctionParser/Licence.txt \
    ../../Tools/ToolTestFunctionParser/ToolTestFunctionParserWelcome.png \
    ../../Tools/ToolTestLed/Licence.txt \
    ../../Tools/ToolTestNewickVector/Licence.txt \
    ../../Tools/ToolTestNewickVector/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestNewickVector/R.png \
    ../../Tools/ToolTestPylos/Licence.txt \
    ../../Tools/ToolTestPylos/R.png \
    ../../Tools/ToolTestPylos/ToolTestPylosCanMove.png \
    ../../Tools/ToolTestPylos/ToolTestPylosDoubleRemoveTest.png \
    ../../Tools/ToolTestPylos/ToolTestPylosMoveMustRemove.png \
    ../../Tools/ToolTestPylos/ToolTestPylosMustRemove.png \
    ../../Tools/ToolTestQrcFile/Licence.txt \
    ../../Tools/ToolTestQrcFile/R.png \
    ../../Tools/ToolTestQrcFile/ToolTestQrcFileWelcome.png \
    ../../Tools/ToolTestQtArrowItems/Licence.txt \
    ../../Tools/ToolTestQtArrowItems/R.png \
    ../../Tools/ToolTestQtArrowItems/ToolTestQtArrowItems.png \
    ../../Tools/ToolTestQtCreatorProFile/Licence.txt \
    ../../Tools/ToolTestQtCreatorProFile/PicR.png \
    ../../Tools/ToolTestQtCreatorProFile/ToolTestQtCreatorProFile.png \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/Licence.txt \
    ../../Tools/ToolTestQtKeyboardFriendlyGraphicsView/PicR14x14_opaque.png \
    ../../Tools/ToolTestQuestion/Questionmark.png \
    ../../Tools/ToolTestQuestion/question.png \
    ../../Tools/ToolTestQuestion/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionIcon14x14.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome1.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome2.png \
    ../../Tools/ToolTestQuestion/ToolTestQuestionWelcome.png \
    ../../Tools/ToolTestShape/ToolTestShapeArchitecture.dia \
    ../../Tools/ToolTestShape/ToolTestShapeArchitecture.png \
    ../../Tools/ToolTestShape/ToolTestShapeWelcome.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButton_1_0.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButtonWelcomeNoLegend.png \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButtonWelcome.png \
    ../../Tools/ToolPause/Licence.txt \
    ../../Tools/ToolStateObserver/ToolStateObserverWelcome.png \
    ../../Tools/ToolStateObserver/Licence.txt \
    ../../Tools/ToolStateObserver/crosscompiletowindows.sh \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Tools/ToolTestToggleButton/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButtonArchitecture_1_0.dia \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButtonWelcome.png \
    ../../Tools/ToolTestToggleButton/wt.css \
    ../../Tools/ToolTestTwoDigitNewick/doxygen.txt \
    ../../Tools/ToolTestTwoDigitNewick/Licence.txt \
    ../../Tools/ToolTestTwoDigitNewick/R.png \
    ../../Tools/ToolTestTwoDigitNewick/testtwodigitnewicks.sh \
    ../../Tools/ToolTestQtModels/Licence.txt \
    ../../Classes/CppQtDisplayPosItem/Licence.txt \
    ../../Classes/CppQtLeftRightRectItem/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Classes/CppQtRoundedEditRectItem/Licence.txt \
    ../../Tools/ToolTestQtRoundedEditRectItem/zip.sh \
    ../../Tools/ToolTestQtRoundedEditRectItem/R.png \
    ../../Tools/ToolTestQtRoundedEditRectItem/Licence.txt \
    ../../Tools/ToolTestQtRoundedEditRectItem/crosscompiletowindows.sh \
    ../../Tools/ToolTestQtRoundedTextRectItem/ToolTestQtRoundedTextRectItem.png \
    ../../Tools/ToolTestQtRoundedTextRectItem/R.png \
    ../../Tools/ToolTestQtRoundedTextRectItem/Licence.txt \
    ../../Tools/ToolKalmanFilterer/zip.sh \
    ../../Tools/ToolKalmanFilterer/ToolKalmanFiltererWelcome.png \
    ../../Tools/ToolKalmanFilterer/ToolKalmanFiltererDesktop.pro \
    ../../Tools/ToolKalmanFilterer/R.png \
    ../../Tools/ToolKalmanFilterer/PicYellow.png \
    ../../Tools/ToolKalmanFilterer/PicTransparent.png \
    ../../Tools/ToolKalmanFilterer/PicRed.png \
    ../../Tools/ToolKalmanFilterer/PicOrange.png \
    ../../Tools/ToolKalmanFilterer/PicGreen.png \
    ../../Tools/ToolKalmanFilterer/PicBlack.png \
    ../../Tools/ToolKalmanFilterer/Licence.txt \
    ../../Tools/ToolKalmanFilterer/crosscompiletowindows.sh \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppQtMatrix/Licence.txt \
    ../../Classes/CppQtExercise/Licence.txt


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
QMAKE_CXXFLAGS += -Wall -Wextra

unix {
  message(Unix)
  #Strict error handling
  QMAKE_CXXFLAGS += -std=c++11 -Werror
}

win32 {
  !static {
    message(Native Windows)
  }

  static {
    message(Crosscompiling from Lubuntu to Windows)
  }

  #Allow the crosscompiler to emit warnings without terminating
  QMAKE_CXXFLAGS += -std=c++11 #-Werror

  #Prevents error:
  #/my_boost_folder/boost/type_traits/detail/has_binary_operator.hp:50: Parse error at "BOOST_JOIN"
  DEFINES += BOOST_TT_HAS_OPERATOR_HPP_INCLUDED
}

#
#
# Boost
#
#

unix {
  LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system
}

win32 {

  #Boost libraries
  INCLUDEPATH += \
    ../../Libraries/boost_1_53_0

  #Prevent the following error:
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp: In function 'boost::program_options::parsed_options boost::program_options::parse_environment(const boost::program_options::options_description&, const boost::function1<std::basic_string<char>, std::basic_string<char> >&)':
  #../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp:194:36: error: 'environ' was not declared in this scope
  DEFINES += __COMO_VERSION__


  #Boost.Data_time
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_names.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_weekday.cpp \
    ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/gregorian_types.cpp \
    ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/greg_month.cpp \
    ../../Libraries/boost_1_53_0/libs/date_time/src/gregorian/date_generators.cpp

  #Boost.Filesystem
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/codecvt_error_category.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/operations.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/path_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/portability.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/unique_path.cpp \
    ../../Libraries/boost_1_53_0/libs/filesystem/src/utf8_codecvt_facet.cpp \ #Keep, comment program_options/src/utf8_codecvt_facet.cpp
    ../../Libraries/boost_1_53_0/libs/filesystem/src/windows_file_codecvt.cpp

  #Boost.Program_options
  #
  #This lib does not seem to work well together with Boost.Filesystem
  #when compiled from source like this
  #
  #SOURCES += \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/cmdline.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/config_file.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/convert.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/options_description.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/parsers.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/positional_options.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/split.cpp \
  #  #../../Libraries/boost_1_53_0/libs/program_options/src/utf8_codecvt_facet.cpp \ #Comment, keep filesystem/src/utf8_codecvt_facet.cpp
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/value_semantic.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/variables_map.cpp \
  #  ../../Libraries/boost_1_53_0/libs/program_options/src/winmain.cpp

  #Boost.Regex
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/regex/src/internals.hpp

  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/regex/src/winstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wide_posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/wc_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/w32_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/usinstances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/static_mutex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_traits_defaults.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_raw_buffer.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex_debug.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/regex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/posix_api.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/instances.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/icu.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/fileiter.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/c_regex_traits.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cregex.cpp \
    ../../Libraries/boost_1_53_0/libs/regex/src/cpp_regex_traits.cpp

  #Boost.System
  HEADERS += \
    ../../Libraries/boost_1_53_0/libs/system/src/local_free_on_destruction.hpp
  SOURCES += \
    ../../Libraries/boost_1_53_0/libs/system/src/error_code.cpp
}

#
#
# Warp's function parser
#
#
#unix {
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
#}


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
# Qwt
#
#

unix {
  INCLUDEPATH += /usr/include/qwt-qt4
  LIBS += -lqwt-qt4
}

win32 {
  !static {
    INCLUDEPATH+=C:/qwt-6.0.1/include
    LIBS += -LC:/qwt-6.0.1/lib

    #Use the correct version, otherwise
    #the following error occurs: 'QWidget: Must construct a QApplication before a QPaintDevice'
    CONFIG(debug, debug|release) {
      message(Use Qwt debug library)
      LIBS+= -lqwtd
    }
    CONFIG(release, debug|release) {
      message(Use Qwt release library)
      LIBS+= -lqwt
    }

  }

  static {
    message(Compile and link Qwt from source)
  INCLUDEPATH+=../../Libraries/qwt-6.0.1/include

  SOURCES += \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_clipper.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_color_map.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_compass.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_counter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dial.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_double_range.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_interval.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_knob.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_legend.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_item.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_magnifier.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_math.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_painter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_panner.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_picker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_axis.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_item.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_xml.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_point_3d.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_point_polar.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_raster_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_div.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_map.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_series_data.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_slider.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_spline.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_symbol.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_system_clock.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text_engine.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_text_label.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_thermo.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_wheel.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_intervalcurve.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrogram.cpp \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_svgitem.cpp \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.cpp

  HEADERS += \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale.h \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_abstract_slider.h \
    ../../Libraries/qwt-6.0.1/include/qwt_analog_clock.h \
    ../../Libraries/qwt-6.0.1/include/qwt_arrow_button.h \
    ../../Libraries/qwt-6.0.1/include/qwt_clipper.h \
    ../../Libraries/qwt-6.0.1/include/qwt_color_map.h \
    ../../Libraries/qwt-6.0.1/include/qwt_column_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compass.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compass_rose.h \
    ../../Libraries/qwt-6.0.1/include/qwt_compat.h \
    ../../Libraries/qwt-6.0.1/include/qwt_counter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_curve_fitter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dial.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dial_needle.h \
    ../../Libraries/qwt-6.0.1/include/qwt_double_range.h \
    ../../Libraries/qwt-6.0.1/include/qwt_dyngrid_layout.h \
    ../../Libraries/qwt-6.0.1/include/qwt_event_pattern.h \
    ../../Libraries/qwt-6.0.1/include/qwt_global.h \
    ../../Libraries/qwt-6.0.1/include/qwt_interval.h \
    ../../Libraries/qwt-6.0.1/include/qwt_interval_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_knob.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend_item.h \
    ../../Libraries/qwt-6.0.1/include/qwt_legend_itemmanager.h \
    ../../Libraries/qwt-6.0.1/include/qwt_magnifier.h \
    ../../Libraries/qwt-6.0.1/include/qwt_math.h \
    ../../Libraries/qwt-6.0.1/include/qwt_mathml_text_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_matrix_raster_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_null_paintdevice.h \
    ../../Libraries/qwt-6.0.1/include/qwt_painter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_panner.h \
    ../../Libraries/qwt-6.0.1/include/qwt_picker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_picker_machine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_canvas.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_curve.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_dict.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_directpainter.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_grid.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_histogram.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_item.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_layout.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_magnifier.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_marker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_panner.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_picker.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_rasteritem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_renderer.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_rescaler.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_scaleitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_seriesitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrocurve.h \
    ../../Libraries/qwt-6.0.1/include/qwt_plot_zoomer.h \
    ../../Libraries/qwt-6.0.1/include/qwt_point_3d.h \
    ../../Libraries/qwt-6.0.1/include/qwt_point_polar.h \
    ../../Libraries/qwt-6.0.1/include/qwt_raster_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_round_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_sampling_thread.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_div.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_draw.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_map.h \
    ../../Libraries/qwt-6.0.1/include/qwt_scale_widget.h \
    ../../Libraries/qwt-6.0.1/include/qwt_series_data.h \
    ../../Libraries/qwt-6.0.1/include/qwt_slider.h \
    ../../Libraries/qwt-6.0.1/include/qwt_spline.h \
    ../../Libraries/qwt-6.0.1/include/qwt_symbol.h \
    ../../Libraries/qwt-6.0.1/include/qwt_system_clock.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text_engine.h \
    ../../Libraries/qwt-6.0.1/include/qwt_text_label.h \
    ../../Libraries/qwt-6.0.1/include/qwt_thermo.h \
    ../../Libraries/qwt-6.0.1/include/qwt_wheel.h \
    ../../Libraries/qwt-6.0.1/src/qwt.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_abstract_slider.h \
    ../../Libraries/qwt-6.0.1/src/qwt_analog_clock.h \
    ../../Libraries/qwt-6.0.1/src/qwt_arrow_button.h \
    ../../Libraries/qwt-6.0.1/src/qwt_clipper.h \
    ../../Libraries/qwt-6.0.1/src/qwt_color_map.h \
    ../../Libraries/qwt-6.0.1/src/qwt_column_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compass.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compass_rose.h \
    ../../Libraries/qwt-6.0.1/src/qwt_compat.h \
    ../../Libraries/qwt-6.0.1/src/qwt_counter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_curve_fitter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dial.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dial_needle.h \
    ../../Libraries/qwt-6.0.1/src/qwt_double_range.h \
    ../../Libraries/qwt-6.0.1/src/qwt_dyngrid_layout.h \
    ../../Libraries/qwt-6.0.1/src/qwt_event_pattern.h \
    ../../Libraries/qwt-6.0.1/src/qwt_global.h \
    ../../Libraries/qwt-6.0.1/src/qwt_interval.h \
    ../../Libraries/qwt-6.0.1/src/qwt_interval_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_knob.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_item.h \
    ../../Libraries/qwt-6.0.1/src/qwt_legend_itemmanager.h \
    ../../Libraries/qwt-6.0.1/src/qwt_magnifier.h \
    ../../Libraries/qwt-6.0.1/src/qwt_math.h \
    ../../Libraries/qwt-6.0.1/src/qwt_matrix_raster_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_null_paintdevice.h \
    ../../Libraries/qwt-6.0.1/src/qwt_painter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_panner.h \
    ../../Libraries/qwt-6.0.1/src/qwt_picker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_picker_machine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_canvas.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_curve.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_dict.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_directpainter.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_grid.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_histogram.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_item.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_layout.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_magnifier.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_marker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_panner.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_picker.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rasteritem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_renderer.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_rescaler.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_scaleitem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_seriesitem.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrocurve.h \
    ../../Libraries/qwt-6.0.1/src/qwt_plot_zoomer.h \
    ../../Libraries/qwt-6.0.1/src/qwt_point_3d.h \
    ../../Libraries/qwt-6.0.1/src/qwt_point_polar.h \
    ../../Libraries/qwt-6.0.1/src/qwt_raster_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_round_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_sampling_thread.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_div.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_draw.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_engine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_map.h \
    ../../Libraries/qwt-6.0.1/src/qwt_scale_widget.h \
    ../../Libraries/qwt-6.0.1/src/qwt_series_data.h \
    ../../Libraries/qwt-6.0.1/src/qwt_slider.h \
    ../../Libraries/qwt-6.0.1/src/qwt_spline.h \
    ../../Libraries/qwt-6.0.1/src/qwt_symbol.h \
    ../../Libraries/qwt-6.0.1/src/qwt_system_clock.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text_engine.h \
    ../../Libraries/qwt-6.0.1/src/qwt_text_label.h \
    ../../Libraries/qwt-6.0.1/src/qwt_thermo.h \
    ../../Libraries/qwt-6.0.1/src/qwt_wheel.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_intervalcurve.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_spectrogram.h \
#    ../../Libraries/qwt-6.0.1/include/qwt_plot_svgitem.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_intervalcurve.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_spectrogram.h \
#    ../../Libraries/qwt-6.0.1/src/qwt_plot_svgitem.h \
    ../../Libraries/qwt-6.0.1/include/qwt.h
  }
}
