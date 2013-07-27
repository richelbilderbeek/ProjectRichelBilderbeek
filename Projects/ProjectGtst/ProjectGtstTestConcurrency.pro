#-------------------------------------------------
#
# Project created by QtCreator 2010-07-24T16:04:35
#
#-------------------------------------------------
QT += core gui
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app

#Detect dead code
#LIBS += -lgcov
#QMAKE_CXXFLAGS += --coverage

#Use of gprof
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppCounter \
    ../../Classes/CppFuzzy_equal_to \
    ../../Classes/CppIpAddress \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRectangle \
    ../../Classes/CppShape \
    ../../Classes/CppShapeWidget \
    ../../Classes/CppTrace \
    ../../Classes/CppStopwatch \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtBroadcastServer \
    ../../Classes/CppWtGroupWidget \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppWtSelectFileDialog \
    ../../Classes/CppWtShapeWidget \
    ../../Libraries/fparser4.4.3

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppIpAddress/ipaddress.cpp \
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
    ../../Classes/CppWtBroadcastServer/wtbroadcastserver.cpp \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserverclient.cpp \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.cpp \
    ../../Classes/CppWtShapeWidget/wtshapewidget.cpp \
    ../../Libraries/fparser4.4.3/fparser.cc \
    administrator.cpp \
    administratordialog.cpp \
    administratordialogstate.cpp \
    administratordialogstateloggedin.cpp \
    administratordialogstatenotloggedin.cpp \
    chatmessage.cpp \
    chatshapefactory.cpp \
    chooseactionoption.cpp \
    debugdialog.cpp \
    experimentstate.cpp \
    group.cpp \
    groupassigner.cpp \
    groupfinished.cpp \
    grouploggedin.cpp \
    groupnotloggedin.cpp \
    groupparticipating.cpp \
    groups.cpp \
    logfile.cpp \
    main_test_concurrency.cpp \
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
    participantstateviewresultsall.cpp \
    participantstateviewresultsgroup.cpp \
    participantstateviewresultsvoting.cpp \
    participantstatevoting.cpp \
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
    maintimer.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppFuzzy_equal_to/fuzzy_equal_to.h \
    ../../Classes/CppIpAddress/ipaddress.h \
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
    ../../Classes/CppWtBroadcastServer/wtbroadcastserver.h \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserverclient.h \
    ../../Classes/CppWtGroupWidget/wtgroupwidget.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppWtSelectFileDialog/wtselectfiledialog.h \
    ../../Classes/CppWtShapeWidget/wtshapewidget.h \
    ../../Libraries/fparser4.4.3/fparser.hh \
    administrator.h \
    administratordialog.h \
    administratordialogstate.h \
    administratordialogstateloggedin.h \
    administratordialogstatenotloggedin.h \
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
    participantdialogstateviewresultsall.h \
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
    participantstateviewresultsall.h \
    participantstateviewresultsgroup.h \
    participantstateviewresultsvoting.h \
    participantstatevoting.h \
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
    serverstateviewresultsall.h \
    serverstateviewresultsgroup.h \
    serverstateviewresultsvoting.h \
    serverstatevoting.h \
    serverstatewaiting.h \
    state.h \
    test.h \
    vote.h \
    votingoption.h \
    maintimer.h

RESOURCES += \
    ProjectGtst.qrc
