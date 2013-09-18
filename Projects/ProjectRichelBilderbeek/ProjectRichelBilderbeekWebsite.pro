QT += core gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include ( ProjectRichelBilderbeek.pri )

INCLUDEPATH += \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtConnectThreeWidget \
    ../../Classes/CppWtDialWidget \
    ../../Classes/CppWtEntrance \
    ../../Classes/CppWtExercise \
    ../../Classes/CppWtGroupWidget \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtMysteryMachineWidget \
    ../../Classes/CppWtOpenQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog \
    ../../Classes/CppWtRubiksClockWidget \
    ../../Classes/CppWtSelectFileDialog \
    ../../Classes/CppWtServerPusher \
    ../../Classes/CppWtShapeGroupWidget \
    ../../Classes/CppWtShapeWidget \
    ../../Classes/CppWtShinyButtonWidget \
    ../../Classes/CppWtTicTacToeWidget \
    ../../Classes/CppWtTimedServerPusher \
    ../../Classes/CppWtToggleButtonWidget \
    ../../Games/GameConnectThree \
    ../../Games/GamePylos \
    ../../Games/GameRubiksClock \
    ../../Games/GameTicTacToe \
    ../../Tools/ToolAsciiArter \
    ../../Tools/ToolCodeToHtml \
    ../../Tools/ToolCreateQtProjectZipFile \
    ../../Tools/ToolHometrainer \
    ../../Tools/ToolKalmanFilterer \
    ../../Tools/ToolRandomCode \
    ../../Tools/ToolRegexTester \
    ../../Tools/ToolSimMysteryMachine \
    ../../Tools/ToolStateObserver \
    ../../Tools/ToolTestDial \
    ../../Tools/ToolTestEncranger \
    ../../Tools/ToolTestEntrance \
    ../../Tools/ToolTestExercise \
    ../../Tools/ToolTestFunctionParser \
    ../../Tools/ToolTestGroupWidget \
    ../../Tools/ToolTestLed \
    ../../Tools/ToolTestNewickVector \
    ../../Tools/ToolTestQtCreatorProFile \
    ../../Tools/ToolTestQtArrowItems \
    ../../Tools/ToolTestQrcFile \
    ../../Tools/ToolTestQuestion \
    ../../Tools/ToolTestSelectFileDialog \
    ../../Tools/ToolTestServerPusher \
    ../../Tools/ToolTestShape \
    ../../Tools/ToolTestShinyButton \
    ../../Tools/ToolTestTimedServerPusher \
    ../../Tools/ToolTestToggleButton \
    ../../Tools/ToolTestTwoDigitNewick \
    ../../Tools/ToolTimePoll \
    ../../Projects/ProjectGtst \
    ../../Projects/RichelbilderbeekNl

SOURCES += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppWtEntrance/wtentrance.cpp \
    ../../Classes/CppWtExercise/wtexercise.cpp \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.cpp \
    ../../Classes/CppWtLedWidget/wtledwidget.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.cpp \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog/wtrichelbilderbeekgallerydialog.cpp \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusher.cpp \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.cpp \
    ../../Classes/CppWtShapeWidget/wtshapewidget.cpp \
    ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.cpp \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.cpp \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.cpp \
#    ../../Games/GameConnectThree/connectthreemenudialog.cpp \
#    ../../Games/GameConnectThree/connectthreeresources.cpp \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.cpp \
    ../../Games/GameConnectThree/wtconnectthreeresources.cpp \
    ../../Games/GameConnectThree/wtselectplayerwidget.cpp \
#    ../../Games/GameRubiksClock/rubiksclockmenudialog.cpp \
    ../../Games/GameRubiksClock/wtrubiksclockmaindialog.cpp \
    ../../Games/GameRubiksClock/wtrubiksclockmenudialog.cpp \
#    ../../Games/GameTicTacToe/tictactoemenudialog.cpp \
    ../../Games/GameTicTacToe/wttictactoegamedialog.cpp \
    ../../Games/GameTicTacToe/wttictactoemenudialog.cpp \
    ../../Projects/ProjectGtst/administrator.cpp \
    ../../Projects/ProjectGtst/administratordialog.cpp \
    ../../Projects/ProjectGtst/administratordialogstate.cpp \
    ../../Projects/ProjectGtst/administratordialogstateloggedin.cpp \
    ../../Projects/ProjectGtst/administratordialogstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/administrators.cpp \
    ../../Projects/ProjectGtst/chatmessage.cpp \
    ../../Projects/ProjectGtst/chatshapefactory.cpp \
    ../../Projects/ProjectGtst/chooseactionoption.cpp \
    ../../Projects/ProjectGtst/debugdialog.cpp \
    ../../Projects/ProjectGtst/groupassigner.cpp \
    ../../Projects/ProjectGtst/group.cpp \
    ../../Projects/ProjectGtst/groupfinished.cpp \
    ../../Projects/ProjectGtst/grouploggedin.cpp \
    ../../Projects/ProjectGtst/groupnotloggedin.cpp \
    ../../Projects/ProjectGtst/groupparticipating.cpp \
    ../../Projects/ProjectGtst/groups.cpp \
    ../../Projects/ProjectGtst/logfile.cpp \
    ../../Projects/ProjectGtst/parametersassignpayoff.cpp \
    ../../Projects/ProjectGtst/parameterschat.cpp \
    ../../Projects/ProjectGtst/parameterschooseaction.cpp \
    ../../Projects/ProjectGtst/parameters.cpp \
    ../../Projects/ProjectGtst/parametersfinished.cpp \
    ../../Projects/ProjectGtst/parametersgroupassign.cpp \
    ../../Projects/ProjectGtst/parametersgroupreassign.cpp \
    ../../Projects/ProjectGtst/parametersquiz.cpp \
    ../../Projects/ProjectGtst/parametersviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/parametersviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/parametersvoting.cpp \
    ../../Projects/ProjectGtst/participant.cpp \
    ../../Projects/ProjectGtst/participantdialog.cpp \
    ../../Projects/ProjectGtst/participantdialogstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/participantdialogstatechat.cpp \
    ../../Projects/ProjectGtst/participantdialogstatechooseaction.cpp \
    ../../Projects/ProjectGtst/participantdialogstate.cpp \
    ../../Projects/ProjectGtst/participantdialogstatefinished.cpp \
    ../../Projects/ProjectGtst/participantdialogstategroupassign.cpp \
    ../../Projects/ProjectGtst/participantdialogstategroupreassign.cpp \
    ../../Projects/ProjectGtst/participantdialogstateloggedin.cpp \
    ../../Projects/ProjectGtst/participantdialogstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/participantdialogstatequiz.cpp \
    ../../Projects/ProjectGtst/participantdialogstates.cpp \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/participantdialogstatevoting.cpp \
    ../../Projects/ProjectGtst/participantstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/participantstatechat.cpp \
    ../../Projects/ProjectGtst/participantstatechooseaction.cpp \
    ../../Projects/ProjectGtst/participantstate.cpp \
    ../../Projects/ProjectGtst/participantstatefinished.cpp \
    ../../Projects/ProjectGtst/participantstategroupassign.cpp \
    ../../Projects/ProjectGtst/participantstategroupreassign.cpp \
    ../../Projects/ProjectGtst/participantstateloggedin.cpp \
    ../../Projects/ProjectGtst/participantstatenotloggedin.cpp \
    ../../Projects/ProjectGtst/participantstatequiz.cpp \
    ../../Projects/ProjectGtst/participantstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/participantstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/participantstatevoting.cpp \
    ../../Projects/ProjectGtst/payoff.cpp \
    ../../Projects/ProjectGtst/payoffs.cpp \
    ../../Projects/ProjectGtst/projectgtstmenudialog.cpp \
    ../../Projects/ProjectGtst/repeatassigner.cpp \
    ../../Projects/ProjectGtst/repeatassignerfixed.cpp \
    ../../Projects/ProjectGtst/repeatassignerrandomgeometric.cpp \
    ../../Projects/ProjectGtst/repeatassignerrandomuniform.cpp \
    ../../Projects/ProjectGtst/resources.cpp \
    ../../Projects/ProjectGtst/server.cpp \
    ../../Projects/ProjectGtst/serverstateassignpayoff.cpp \
    ../../Projects/ProjectGtst/serverstatechat.cpp \
    ../../Projects/ProjectGtst/serverstatechooseaction.cpp \
    ../../Projects/ProjectGtst/serverstate.cpp \
    ../../Projects/ProjectGtst/serverstatefinished.cpp \
    ../../Projects/ProjectGtst/serverstategroupassign.cpp \
    ../../Projects/ProjectGtst/serverstategroupreassign.cpp \
    ../../Projects/ProjectGtst/serverstatequiz.cpp \
    ../../Projects/ProjectGtst/serverstates.cpp \
    ../../Projects/ProjectGtst/serverstateviewresultsgroup.cpp \
    ../../Projects/ProjectGtst/serverstateviewresultsvoting.cpp \
    ../../Projects/ProjectGtst/serverstatevoting.cpp \
    ../../Projects/ProjectGtst/serverstatewaiting.cpp \
    ../../Projects/ProjectGtst/state.cpp \
    ../../Projects/ProjectGtst/test.cpp \
    ../../Projects/ProjectGtst/testparameterparsing.cpp \
    ../../Projects/ProjectGtst/testparameters.cpp \
    ../../Projects/ProjectGtst/testparticipant.cpp \
    ../../Projects/ProjectGtst/teststate.cpp \
    ../../Projects/ProjectGtst/vote.cpp \
    ../../Projects/ProjectGtst/votingoption.cpp \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.cpp \
#    richelbilderbeekmenudialog.cpp \
#    ../../Tools/ToolAsciiArter/asciiartermaindialog.cpp \
#    ../../Tools/ToolAsciiArter/asciiartermenudialog.cpp \
    ../../Tools/ToolAsciiArter/wtasciiartermaindialog.cpp \
#    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.cpp \
    ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.cpp \
    ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.cpp \
#    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.cpp \
#    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.cpp \
#    ../../Tools/ToolHometrainer/hometrainermenudialog.cpp \
#    ../../Tools/ToolHometrainer/hometrainerresources.cpp \
    ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.cpp \
    ../../Tools/ToolHometrainer/wthometrainermenudialog.cpp \
    ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.cpp \
    ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.cpp \
    ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.cpp \
    ../../Tools/ToolRandomCode/wtrandomcodemenudialog.cpp \
#    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.cpp \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.cpp \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.cpp \
#    ../../Tools/ToolTestDial/testdialmenudialog.cpp \
    ../../Tools/ToolTestDial/wttestdialmaindialog.cpp \
    ../../Tools/ToolTestDial/wttestdialmenudialog.cpp \
#    ../../Tools/ToolTestEncranger/testencrangerdialog.cpp \
    ../../Tools/ToolTestEncranger/wttestencrangermaindialog.cpp \
    ../../Tools/ToolTestEncranger/wttestencrangermenudialog.cpp \
    ../../Tools/ToolTestEntrance/wttestentrancemaindialog.cpp \
    ../../Tools/ToolTestEntrance/wttestentrancemenudialog.cpp \
#    ../../Tools/ToolTestExercise/testexercisemenudialog.cpp \
    ../../Tools/ToolTestExercise/wttestexercisemaindialog.cpp \
    ../../Tools/ToolTestExercise/wttestexercisemenudialog.cpp \
#    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.cpp \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.cpp \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.cpp \
#    ../../Tools/ToolTestGroupWidget/testgroupwidgetmenudialog.cpp \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmaindialog.cpp \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmenudialog.cpp \
#    ../../Tools/ToolTestLed/testledmenudialog.cpp \
    ../../Tools/ToolTestLed/wttestledmaindialog.cpp \
    ../../Tools/ToolTestLed/wttestledmenudialog.cpp \
#    ../../Tools/ToolTestNewickVector/testnewickvectordialog.cpp \
    ../../Tools/ToolTestNewickVector/wttestnewickvectordialog.cpp \
#    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.cpp \
#    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.cpp \
#    ../../Tools/ToolTestQuestion/testquestionmaindialog.cpp \
#    ../../Tools/ToolTestQuestion/testquestionmenudialog.cpp \
    ../../Tools/ToolTestQuestion/wttestquestionmaindialog.cpp \
    ../../Tools/ToolTestQuestion/wttestquestionmenudialog.cpp \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmaindialog.cpp \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmenudialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherdata.cpp \
    ../../Tools/ToolTestServerPusher/testserverpushermenudialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmaindialog.cpp \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmenudialog.cpp \
#    ../../Tools/ToolTestShape/testshapemaindialog.cpp \
#    ../../Tools/ToolTestShape/testshapemenudialog.cpp \
    ../../Tools/ToolTestShape/wttestshapemaindialog.cpp \
    ../../Tools/ToolTestShape/wttestshapemenudialog.cpp \
#    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmaindialog.cpp \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmenudialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherdata.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpushermenudialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmaindialog.cpp \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmenudialog.cpp \
#    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.cpp \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmaindialog.cpp \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmenudialog.cpp \
    ../../Tools/ToolTestTwoDigitNewick/wttesttwodigitnewickdialog.cpp \
    ../../Tools/ToolTimePoll/timepolldata.cpp \
    ../../Tools/ToolTimePoll/timepollmenudialog.cpp \
    ../../Tools/ToolTimePoll/timepollwtmaindialog.cpp \
    ../../Tools/ToolTimePoll/timepollwtmenudialog.cpp \
    wtmain.cpp \
    wtrichelbilderbeekadmindialog.cpp \
    wtrichelbilderbeekmenudialog.cpp \
    wtrichelbilderbeekmenuitem.cpp \
    ../../Games/GameConnectThree/qtconnectthreeresources.cpp

HEADERS += \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtConnectThreeWidget/wtconnectthreewidget.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppWtEntrance/wtentrance.h \
    ../../Classes/CppWtExercise/wtexercise.h \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.h \
    ../../Classes/CppWtLedWidget/wtledwidget.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtMysteryMachineWidget/wtmysterymachinewidget.h \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppWtRichelBilderbeekGalleryDialog/wtrichelbilderbeekgallerydialog.h \
    ../../Classes/CppWtRubiksClockWidget/wtrubiksclockwidget.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.h \
    ../../Classes/CppWtServerPusher/wtserverpusher.h \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.h \
    ../../Classes/CppWtShapeWidget/wtshapewidget.h \
    ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.h \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.h \
    ../../Classes/CppWtToggleButtonWidget/wttogglebuttonwidget.h \
#    ../../Games/GameConnectThree/connectthreemenudialog.h \
#    ../../Games/GameConnectThree/connectthreeresources.h \
    ../../Games/GameConnectThree/wtconnectthreegamedialog.h \
    ../../Games/GameConnectThree/wtconnectthreemenudialog.h \
    ../../Games/GameConnectThree/wtconnectthreeresources.h \
    ../../Games/GameConnectThree/wtselectplayerwidget.h \
#    ../../Games/GameRubiksClock/rubiksclockmenudialog.h \
    ../../Games/GameRubiksClock/wtrubiksclockmaindialog.h \
    ../../Games/GameRubiksClock/wtrubiksclockmenudialog.h \
#    ../../Games/GameTicTacToe/tictactoemenudialog.h \
    ../../Games/GameTicTacToe/wttictactoegamedialog.h \
    ../../Games/GameTicTacToe/wttictactoemenudialog.h \
    ../../Projects/ProjectGtst/administratordialog.h \
    ../../Projects/ProjectGtst/administratordialogstate.h \
    ../../Projects/ProjectGtst/administratordialogstateloggedin.h \
    ../../Projects/ProjectGtst/administratordialogstatenotloggedin.h \
    ../../Projects/ProjectGtst/administrator.h \
    ../../Projects/ProjectGtst/administrators.h \
    ../../Projects/ProjectGtst/all_groups.h \
    ../../Projects/ProjectGtst/all_parameters.h \
    ../../Projects/ProjectGtst/all_participantdialogstates.h \
    ../../Projects/ProjectGtst/all_participantstates.h \
    ../../Projects/ProjectGtst/all_serverstates.h \
    ../../Projects/ProjectGtst/chatmessage.h \
    ../../Projects/ProjectGtst/chatshapefactory.h \
    ../../Projects/ProjectGtst/chooseactionoption.h \
    ../../Projects/ProjectGtst/debugdialog.h \
    ../../Projects/ProjectGtst/forward_declarations.h \
    ../../Projects/ProjectGtst/groupassigner.h \
    ../../Projects/ProjectGtst/groupfinished.h \
    ../../Projects/ProjectGtst/group.h \
    ../../Projects/ProjectGtst/grouploggedin.h \
    ../../Projects/ProjectGtst/groupnotloggedin.h \
    ../../Projects/ProjectGtst/groupparticipating.h \
    ../../Projects/ProjectGtst/groups.h \
    ../../Projects/ProjectGtst/logfile.h \
    ../../Projects/ProjectGtst/parametersassignpayoff.h \
    ../../Projects/ProjectGtst/parameterschat.h \
    ../../Projects/ProjectGtst/parameterschooseaction.h \
    ../../Projects/ProjectGtst/parametersfinished.h \
    ../../Projects/ProjectGtst/parametersgroupassign.h \
    ../../Projects/ProjectGtst/parametersgroupreassign.h \
    ../../Projects/ProjectGtst/parameters.h \
    ../../Projects/ProjectGtst/parametersquiz.h \
    ../../Projects/ProjectGtst/parametersviewresultsall.h \
    ../../Projects/ProjectGtst/parametersviewresultsgroup.h \
    ../../Projects/ProjectGtst/parametersviewresultsvoting.h \
    ../../Projects/ProjectGtst/parametersvoting.h \
    ../../Projects/ProjectGtst/participantdialog.h \
    ../../Projects/ProjectGtst/participantdialogstateassignpayoff.h \
    ../../Projects/ProjectGtst/participantdialogstatechat.h \
    ../../Projects/ProjectGtst/participantdialogstatechooseaction.h \
    ../../Projects/ProjectGtst/participantdialogstatefinished.h \
    ../../Projects/ProjectGtst/participantdialogstategroupassign.h \
    ../../Projects/ProjectGtst/participantdialogstategroupreassign.h \
    ../../Projects/ProjectGtst/participantdialogstate.h \
    ../../Projects/ProjectGtst/participantdialogstateloggedin.h \
    ../../Projects/ProjectGtst/participantdialogstatenotloggedin.h \
    ../../Projects/ProjectGtst/participantdialogstatequiz.h \
    ../../Projects/ProjectGtst/participantdialogstates.h \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/participantdialogstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/participantdialogstatevoting.h \
    ../../Projects/ProjectGtst/participant.h \
    ../../Projects/ProjectGtst/participantstateassignpayoff.h \
    ../../Projects/ProjectGtst/participantstatechat.h \
    ../../Projects/ProjectGtst/participantstatechooseaction.h \
    ../../Projects/ProjectGtst/participantstatefinished.h \
    ../../Projects/ProjectGtst/participantstategroupassign.h \
    ../../Projects/ProjectGtst/participantstategroupreassign.h \
    ../../Projects/ProjectGtst/participantstate.h \
    ../../Projects/ProjectGtst/participantstateloggedin.h \
    ../../Projects/ProjectGtst/participantstatenotloggedin.h \
    ../../Projects/ProjectGtst/participantstatequiz.h \
    ../../Projects/ProjectGtst/participantstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/participantstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/participantstatevoting.h \
    ../../Projects/ProjectGtst/payoff.h \
    ../../Projects/ProjectGtst/payoffs.h \
    ../../Projects/ProjectGtst/projectgtstmenudialog.h \
    ../../Projects/ProjectGtst/repeatassignerfixed.h \
    ../../Projects/ProjectGtst/repeatassigner.h \
    ../../Projects/ProjectGtst/repeatassignerrandomgeometric.h \
    ../../Projects/ProjectGtst/repeatassignerrandomuniform.h \
    ../../Projects/ProjectGtst/resources.h \
    ../../Projects/ProjectGtst/server.h \
    ../../Projects/ProjectGtst/serverstateassignpayoff.h \
    ../../Projects/ProjectGtst/serverstatechat.h \
    ../../Projects/ProjectGtst/serverstatechooseaction.h \
    ../../Projects/ProjectGtst/serverstatefinished.h \
    ../../Projects/ProjectGtst/serverstategroupassign.h \
    ../../Projects/ProjectGtst/serverstategroupreassign.h \
    ../../Projects/ProjectGtst/serverstate.h \
    ../../Projects/ProjectGtst/serverstatequiz.h \
    ../../Projects/ProjectGtst/serverstates.h \
    ../../Projects/ProjectGtst/serverstateviewresultsgroup.h \
    ../../Projects/ProjectGtst/serverstateviewresultsvoting.h \
    ../../Projects/ProjectGtst/serverstatevoting.h \
    ../../Projects/ProjectGtst/serverstatewaiting.h \
    ../../Projects/ProjectGtst/state.h \
    ../../Projects/ProjectGtst/test.h \
    ../../Projects/ProjectGtst/vote.h \
    ../../Projects/ProjectGtst/votingoption.h \
#    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.h \
#    richelbilderbeekmenudialog.h \
#    ../../Tools/ToolAsciiArter/asciiartermaindialog.h \
#    ../../Tools/ToolAsciiArter/asciiartermenudialog.h \
    ../../Tools/ToolAsciiArter/wtasciiartermaindialog.h \
#    ../../Tools/ToolCodeToHtml/codetohtmlmenudialog.h \
    ../../Tools/ToolCodeToHtml/wtcodetohtmldialog.h \
    ../../Tools/ToolCodeToHtml/wtcodetohtmlmenudialog.h \
#    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilemenudialog.h \
#    ../../Tools/ToolCreateQtProjectZipFile/createqtprojectzipfilepath.h \
#    ../../Tools/ToolHometrainer/hometrainermenudialog.h \
#    ../../Tools/ToolHometrainer/hometrainerresources.h \
    ../../Tools/ToolHometrainer/wthometrainerloadexercisedialog.h \
    ../../Tools/ToolHometrainer/wthometrainermenudialog.h \
    ../../Tools/ToolHometrainer/wthometrainerstartexercisedialog.h \
    ../../Tools/ToolHometrainer/wtselecthometrainerfiledialog.h \
#    ../../Tools/ToolRandomCode/randomcodemenudialog.h \
    ../../Tools/ToolRandomCode/wtrandomcodegeneratedialog.h \
    ../../Tools/ToolRandomCode/wtrandomcodemenudialog.h \
#    ../../Tools/ToolSimMysteryMachine/simmysterymachinemenudialog.h \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemaindialog.h \
    ../../Tools/ToolSimMysteryMachine/wtsimmysterymachinemenudialog.h \
#    ../../Tools/ToolTestDial/testdialmenudialog.h \
    ../../Tools/ToolTestDial/wttestdialmaindialog.h \
    ../../Tools/ToolTestDial/wttestdialmenudialog.h \
#    ../../Tools/ToolTestEncranger/testencrangerdialog.h \
    ../../Tools/ToolTestEncranger/wttestencrangermaindialog.h \
    ../../Tools/ToolTestEncranger/wttestencrangermenudialog.h \
#    ../../Tools/ToolTestEntrance/testentrancemenudialog.h \
    ../../Tools/ToolTestEntrance/wttestentrancemaindialog.h \
    ../../Tools/ToolTestEntrance/wttestentrancemenudialog.h \
#    ../../Tools/ToolTestExercise/testexercisemenudialog.h \
    ../../Tools/ToolTestExercise/wttestexercisemaindialog.h \
    ../../Tools/ToolTestExercise/wttestexercisemenudialog.h \
#    ../../Tools/ToolTestFunctionParser/testfunctionparsermenudialog.h \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermaindialog.h \
    ../../Tools/ToolTestFunctionParser/wttestfunctionparsermenudialog.h \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmaindialog.h \
    ../../Tools/ToolTestGroupWidget/wttestgroupwidgetmenudialog.h \
#    ../../Tools/ToolTestLed/testledmenudialog.h \
    ../../Tools/ToolTestLed/wttestledmaindialog.h \
    ../../Tools/ToolTestLed/wttestledmenudialog.h \
#    ../../Tools/ToolTestNewickVector/testnewickvectordialog.h \
    ../../Tools/ToolTestNewickVector/wttestnewickvectordialog.h \
#    ../../Tools/ToolTestQrcFile/testqrcfilemenudialog.h \
#    ../../Tools/ToolTestQtCreatorProFile/testqtcreatorprofilemenudialog.h \
#    ../../Tools/ToolTestQuestion/testquestionmaindialog.h \
#    ../../Tools/ToolTestQuestion/testquestionmenudialog.h \
    ../../Tools/ToolTestQuestion/wttestquestionmaindialog.h \
    ../../Tools/ToolTestQuestion/wttestquestionmenudialog.h \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmaindialog.h \
    ../../Tools/ToolTestSelectFileDialog/wttestselectfiledialogmenudialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherdata.h \
    ../../Tools/ToolTestServerPusher/testserverpushermenudialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmaindialog.h \
    ../../Tools/ToolTestServerPusher/testserverpusherwtmenudialog.h \
#    ../../Tools/ToolTestShape/testshapemaindialog.h \
#    ../../Tools/ToolTestShape/testshapemenudialog.h \
    ../../Tools/ToolTestShape/wttestshapemaindialog.h \
    ../../Tools/ToolTestShape/wttestshapemenudialog.h \
#    ../../Tools/ToolTestShinyButton/testshinybuttonmenudialog.h \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmaindialog.h \
    ../../Tools/ToolTestShinyButton/wttestshinybuttonmenudialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherdata.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpushermenudialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmaindialog.h \
    ../../Tools/ToolTestTimedServerPusher/testtimedserverpusherwtmenudialog.h \
#    ../../Tools/ToolTestToggleButton/testtogglebuttonmenudialog.h \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmaindialog.h \
    ../../Tools/ToolTestToggleButton/wttesttogglebuttonmenudialog.h \
    ../../Tools/ToolTestTwoDigitNewick/wttesttwodigitnewickdialog.h \
    ../../Tools/ToolTimePoll/timepolldata.h \
    ../../Tools/ToolTimePoll/timepollmenudialog.h \
    ../../Tools/ToolTimePoll/timepollwtmaindialog.h \
    ../../Tools/ToolTimePoll/timepollwtmenudialog.h \
    wtrichelbilderbeekadmindialog.h \
    wtrichelbilderbeekmenudialog.h \
    wtrichelbilderbeekmenuitem.h \
    ../../Games/GameConnectThree/qtconnectthreeresources.h

RESOURCES += \
    ../../Games/GameConnectThree/GameConnectThree.qrc \
    ../../Games/GameRubiksClock/GameRubiksClock.qrc \
    ../../Tools/ToolCodeToHtml/ToolCodeToHtml.qrc \
    ../../Tools/ToolRandomCode/ToolRandomCode.qrc \
    ../../Tools/ToolSimMysteryMachine/ToolSimMysteryMachine.qrc \
    ../../Tools/ToolTestDial/ToolTestDial.qrc \
    ../../Tools/ToolTestEncranger/ToolTestEncranger.qrc \
    ../../Tools/ToolTestEntrance/ToolTestEntrance.qrc \
    ../../Tools/ToolTestFunctionParser/ToolTestFunctionParser.qrc \
    ../../Tools/ToolTestGroupWidget/ToolTestGroupWidget.qrc \
    ../../Tools/ToolTestLed/ToolTestLed.qrc \
    ../../Tools/ToolTestQuestion/ToolTestQuestion.qrc \
    ../../Tools/ToolTestSelectFileDialog/ToolTestSelectFileDialog.qrc \
    ../../Tools/ToolTestShape/ToolTestShape.qrc \
    ../../Tools/ToolTestToggleButton/ToolTestToggleButton.qrc \
    ../../Projects/ProjectGtst/ProjectGtst.qrc \
    ProjectRichelBilderbeek.qrc \
    ../../Tools/ToolTestShinyButton/ToolTestShinyButton.qrc \
    ../../Tools/ToolTestExercise/ToolTestExercise.qrc \
    ../../Tools/ToolHometrainer/ToolHometrainer.qrc \
    ../../Projects/RichelbilderbeekNl/qtrichelbilderbeekgalleryresources.qrc \
    ../../Tools/ToolAsciiArter/ToolAsciiArter.qrc \
    ../../Tools/ToolStateObserver/ToolStateObserver.qrc \
    ../../Games/GamePylos/GamePylos.qrc

OTHER_FILES += \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppAsciiArter/Licence.txt \
    ../../Classes/CppBinaryNewickVector/Licence.txt \
    ../../Classes/CppCodeToHtml/Licence.txt \
    ../../Classes/CppConnectThree/Licence.txt \
    ../../Classes/CppConnectThreeWidget/Licence.txt \
    ../../Classes/CppCounter/Licence.txt \
    ../../Classes/CppDial/Licence.txt \
    ../../Classes/CppDialWidget/Licence.txt \
    ../../Classes/CppEncranger/Licence.txt \
    ../../Classes/CppExercise/Licence.txt \
    ../../Classes/CppIpAddress/Licence.txt \
    ../../Classes/CppLazy_init/Licence.txt \
    ../../Classes/CppLed/Licence.txt \
    ../../Classes/CppLedWidget/Licence.txt \
    ../../Classes/CppManyDigitNewick/Licence.txt \
    ../../Classes/CppMultipleChoiceQuestion/Licence.txt \
    ../../Classes/CppMultipleChoiceQuestionDialog/Licence.txt \
    ../../Classes/CppMysteryMachine/Licence.txt \
    ../../Classes/CppMysteryMachineWidget/Licence.txt \
    ../../Classes/CppNewick/Licence.txt \
    ../../Projects/ProjectGtst/TotalExperimentFlow.png \
    ../../Projects/ProjectGtst/RichelbilderbeekNlBackground.png \
    ../../Projects/ProjectGtst/R.png \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureServer.png \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureServer.dia \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureMenuDialog.png \
    ../../Projects/ProjectGtst/ProjectGtstArchitectureMenuDialog.dia \
    ../../Projects/ProjectGtst/ProjectGtst.odp \
    ../../Projects/ProjectGtst/Period_100_58.png \
    ../../Projects/ProjectGtst/Licence.txt \
    ../../Projects/ProjectGtst/IPGG.png \
    ../../Projects/ProjectGtst/helgrind_test_concurrency.sh \
    ../../Projects/ProjectGtst/helgrind.sh \
    ../../Projects/ProjectGtst/gtst_start_and_auto_update.sh \
    ../../Projects/ProjectGtst/Groups.png \
    ../../Projects/ProjectGtst/GroupDynamics_100.png \
    ../../Projects/ProjectGtst/ExperimentFlow.png \
    ../../Projects/ProjectGtst/Experiment_100.png \
    ../../Projects/ProjectGtst/drd.sh \
    ../../Projects/ProjectGtst/Cycle_100.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVotingParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVoting2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogVoting.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsVotingParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsVoting.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsGroupParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogViewResultsGroup.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogNotLoggedInParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogNotLoggedIn.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogLoggedInParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogLoggedIn.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupReAssignParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupReAssign.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssignParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign2Parameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogGroupAssign.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogFinishedParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogFinished.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseActionParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseAction2.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChooseAction.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChatParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogChat.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogAssignPayoffParameters.png \
    ../../Projects/ProjectGtst/ProjectGtstParticipantDialogAssignPayoff.png \
    ../../Games/GameRubiksClock/Licence.txt \
    ../../Games/GameRubiksClock/GameRubiksClockWelcomeNoLegend.png \
    ../../Games/GameRubiksClock/GameRubiksClockWelcome_2_1.png \
    ../../Games/GameRubiksClock/GameRubiksClock.png \
    ../../Tools/ToolAsciiArter/RichelbilderbeekNlBackground.png \
    ../../Tools/ToolAsciiArter/R.png \
    ../../Tools/ToolAsciiArter/Licence.txt \
    ../../Tools/ToolAsciiArter/AsciiArter.png \
    ../../Classes/CppHtmlPage/Licence.txt \
    ../../Classes/CppMusic/Licence.txt \
    ../../Classes/CppMatrix/Licence.txt \
    ../../Tools/ToolRegexTester/Licence.txt \
    ../../Classes/CppKalmanFilter/Licence.txt \
    ../../Classes/CppGaborFilter/Licence.txt \
    ../../Classes/CppGaborFilterWidget/Licence.txt \
    ../../Classes/CppStateObserver/Licence.txt \
    ../../Tools/ToolStateObserver/zip.sh \
    ../../Tools/ToolStateObserver/ToolStateObserverWelcome.png \
    ../../Tools/ToolStateObserver/Licence.txt \
    ../../Games/GamePylos/zip.sh \
    ../../Games/GamePylos/sprite_player2_select.png \
    ../../Games/GamePylos/sprite_player2_remove.png \
    ../../Games/GamePylos/sprite_player2.png \
    ../../Games/GamePylos/sprite_player1_select.png \
    ../../Games/GamePylos/sprite_player1_remove.png \
    ../../Games/GamePylos/sprite_player1.png \
    ../../Games/GamePylos/sprite_hole.png \
    ../../Games/GamePylos/R.png \
    ../../Games/GamePylos/PylosSquare.png \
    ../../Games/GamePylos/PylosRemove2.png \
    ../../Games/GamePylos/PylosRemove1.png \
    ../../Games/GamePylos/PylosPlace.png \
    ../../Games/GamePylos/PylosMove.png \
    ../../Games/GamePylos/PylosLine.png \
    ../../Games/GamePylos/PylosGoal2.png \
    ../../Games/GamePylos/PylosGoal1.png \
    ../../Games/GamePylos/Licence.txt \
    ../../Classes/CppQtModel/Licence.txt \
    ../../Classes/CppPylos/Licence.txt

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
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}


#
#
# Wt
#
#
unix {
  LIBS += \
  -lwt \
  -lwthttp
}

win32 {
  INCLUDEPATH += ../../Libraries/wt/src
}
