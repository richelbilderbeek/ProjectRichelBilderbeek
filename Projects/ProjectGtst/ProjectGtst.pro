#-------------------------------------------------
#
# Project created by QtCreator 2010-07-24T16:04:35
#
#-------------------------------------------------
QT += core gui
TARGET = gtst
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

#Detect dead code
#LIBS += -lgcov
#QMAKE_CXXFLAGS += --coverage
release:DEFINES+=NDEBUG

#Use of gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCopy_if \
    ../../Classes/CppCounter \
    ../../Classes/CppFuzzy_equal_to \
    ../../Classes/CppIpAddress \
    ../../Classes/CppLed \
    ../../Classes/CppLedWidget \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRainbow \
    ../../Classes/CppRectangle \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppStopwatch \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtGroupWidget \
    ../../Classes/CppWtLedWidget \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppWtSelectFileDialog \
    ../../Classes/CppWtServerPusher \
    ../../Classes/CppWtShapeGroupWidget \
    ../../Classes/CppWtShapeWidget \
    ../../Classes/CppWtTimedServerPusher \
    ../../Libraries/fparser4.4.3

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppIpAddress/ipaddress.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppShape/shape.cpp \
    ../../Classes/CppShapeWidget/shapewidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.cpp \
    ../../Classes/CppWtLedWidget/wtledwidget.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusher.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.cpp \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.cpp \
    ../../Classes/CppWtShapeWidget/wtshapewidget.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.cpp \
    ../../Libraries/fparser4.4.3/fparser.cc \
    administrator.cpp \
    administratordialog.cpp \
    administratordialogstate.cpp \
    administratordialogstateloggedin.cpp \
    administratordialogstatenotloggedin.cpp \
    administrators.cpp \
    chatmessage.cpp \
    chatshapefactory.cpp \
    chooseactionoption.cpp \
    debugdialog.cpp \
    group.cpp \
    groupassigner.cpp \
    groupfinished.cpp \
    grouploggedin.cpp \
    groupnotloggedin.cpp \
    groupparticipating.cpp \
    groups.cpp \
    logfile.cpp \
    main.cpp \
    parameters.cpp \
    parametersassignpayoff.cpp \
    parameterschat.cpp \
    parameterschooseaction.cpp \
    parametersfinished.cpp \
    parametersgroupassign.cpp \
    parametersgroupreassign.cpp \
    parametersquiz.cpp \
    parametersviewresultsgroup.cpp \
    parametersviewresultsvoting.cpp \
    parametersvoting.cpp \
    participant.cpp \
    participantdialog.cpp \
    participantdialogstate.cpp \
    participantdialogstateassignpayoff.cpp \
    participantdialogstatechat.cpp \
    participantdialogstatechooseaction.cpp \
    participantdialogstatefinished.cpp \
    participantdialogstategroupassign.cpp \
    participantdialogstategroupreassign.cpp \
    participantdialogstateloggedin.cpp \
    participantdialogstatenotloggedin.cpp \
    participantdialogstatequiz.cpp \
    participantdialogstates.cpp \
    participantdialogstateviewresultsgroup.cpp \
    participantdialogstateviewresultsvoting.cpp \
    participantdialogstatevoting.cpp \
    participantstate.cpp \
    participantstateassignpayoff.cpp \
    participantstatechat.cpp \
    participantstatechooseaction.cpp \
    participantstatefinished.cpp \
    participantstategroupassign.cpp \
    participantstategroupreassign.cpp \
    participantstateloggedin.cpp \
    participantstatenotloggedin.cpp \
    participantstatequiz.cpp \
    participantstateviewresultsgroup.cpp \
    participantstateviewresultsvoting.cpp \
    participantstatevoting.cpp \
    payoff.cpp \
    payoffs.cpp \
    projectgtstmenudialog.cpp \
    repeatassigner.cpp \
    repeatassignerfixed.cpp \
    repeatassignerrandomgeometric.cpp \
    repeatassignerrandomuniform.cpp \
    resources.cpp \
    server.cpp \
    serverstate.cpp \
    serverstateassignpayoff.cpp \
    serverstatechat.cpp \
    serverstatechooseaction.cpp \
    serverstatefinished.cpp \
    serverstategroupassign.cpp \
    serverstategroupreassign.cpp \
    serverstatequiz.cpp \
    serverstates.cpp \
    serverstateviewresultsgroup.cpp \
    serverstateviewresultsvoting.cpp \
    serverstatevoting.cpp \
    serverstatewaiting.cpp \
    state.cpp \
    test.cpp \
    testparameterparsing.cpp \
    testparameters.cpp \
    testparticipant.cpp \
    teststate.cpp \
    vote.cpp \
    votingoption.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppCopy_if/copy_if.h \
    ../../Classes/CppCounter/counter.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppIpAddress/ipaddress.h \
    ../../Classes/CppLed/led.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppShape/shape.h \
    ../../Classes/CppShapeWidget/shapewidget.h \
    ../../Classes/CppStopwatch/stopwatch.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.h \
    ../../Classes/CppWtLedWidget/wtledwidget.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    ../../Classes/CppWtServerPusher/wtserverpusher.h \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.h \
    ../../Classes/CppWtShapeGroupWidget/wtshapegroupwidget.h \
    ../../Classes/CppWtShapeWidget/wtshapewidget.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.h \
    ../../Libraries/fparser4.4.3/fparser.hh \
    administrator.h \
    administratordialog.h \
    administratordialogstate.h \
    administratordialogstateloggedin.h \
    administratordialogstatenotloggedin.h \
    administrators.h \
    all_groups.h \
    all_parameters.h \
    all_participantdialogstates.h \
    all_participantstates.h \
    all_serverstates.h \
    chatmessage.h \
    chatshapefactory.h \
    chooseactionoption.h \
    debugdialog.h \
    forward_declarations.h \
    group.h \
    groupassigner.h \
    groupfinished.h \
    grouploggedin.h \
    groupnotloggedin.h \
    groupparticipating.h \
    groups.h \
    logfile.h \
    parameters.h \
    parametersassignpayoff.h \
    parameterschat.h \
    parameterschooseaction.h \
    parametersfinished.h \
    parametersgroupassign.h \
    parametersgroupreassign.h \
    parametersquiz.h \
    parametersviewresultsall.h \
    parametersviewresultsgroup.h \
    parametersviewresultsvoting.h \
    parametersvoting.h \
    participant.h \
    participantdialog.h \
    participantdialogstate.h \
    participantdialogstateassignpayoff.h \
    participantdialogstatechat.h \
    participantdialogstatechooseaction.h \
    participantdialogstatefinished.h \
    participantdialogstategroupassign.h \
    participantdialogstategroupreassign.h \
    participantdialogstateloggedin.h \
    participantdialogstatenotloggedin.h \
    participantdialogstatequiz.h \
    participantdialogstates.h \
    participantdialogstateviewresultsgroup.h \
    participantdialogstateviewresultsvoting.h \
    participantdialogstatevoting.h \
    participantstate.h \
    participantstateassignpayoff.h \
    participantstatechat.h \
    participantstatechooseaction.h \
    participantstatefinished.h \
    participantstategroupassign.h \
    participantstategroupreassign.h \
    participantstateloggedin.h \
    participantstatenotloggedin.h \
    participantstatequiz.h \
    participantstateviewresultsgroup.h \
    participantstateviewresultsvoting.h \
    participantstatevoting.h \
    payoff.h \
    payoffs.h \
    projectgtstmenudialog.h \
    repeatassigner.h \
    repeatassignerfixed.h \
    repeatassignerrandomgeometric.h \
    repeatassignerrandomuniform.h \
    resources.h \
    server.h \
    serverstate.h \
    serverstateassignpayoff.h \
    serverstatechat.h \
    serverstatechooseaction.h \
    serverstatefinished.h \
    serverstategroupassign.h \
    serverstategroupreassign.h \
    serverstatequiz.h \
    serverstates.h \
    serverstateviewresultsgroup.h \
    serverstateviewresultsvoting.h \
    serverstatevoting.h \
    serverstatewaiting.h \
    state.h \
    test.h \
    vote.h \
    votingoption.h \
    ../../Classes/CppRainbow/rainbow.h

RESOURCES += \
    ProjectGtst.qrc
