include(../../WebApplication.pri)
include(../../Libraries/BigInteger.pri)
include(../../Libraries/BoostAll.pri)
include(../../Libraries/Fparser.pri)
include(../../Libraries/Wt.pri)

include(../../Libraries/GeneralConsole.pri)
include(../../Libraries/GeneralWeb.pri)

#Detect dead code
#LIBS += -lgcov
#QMAKE_CXXFLAGS += --coverage

#Use of gprof
#QMAKE_CXXFLAGS_DEBUG += -pg
#QMAKE_LFLAGS_DEBUG += -pg

#Console
include(../../Classes/CppCanvas/CppCanvas.pri)
#include(../../CppCopy_if/CppCopy_if.pri)
include(../../Classes/CppCounter/CppCounter.pri)
include(../../Classes/CppDotMatrix/CppDotMatrix.pri)
include(../../Classes/CppFuzzy_equal_to/CppFuzzy_equal_to.pri)
include(../../Classes/CppGeometry/CppGeometry.pri)
include(../../Classes/CppImageCanvas/CppImageCanvas.pri)
include(../../Classes/CppIpAddress/CppIpAddress.pri)
include(../../Classes/CppLed/CppLed.pri)
include(../../Classes/CppLedWidget/CppLedWidget.pri)
include(../../Classes/CppMultipleChoiceQuestion/CppMultipleChoiceQuestion.pri)
include(../../Classes/CppMultipleChoiceQuestionDialog/CppMultipleChoiceQuestionDialog.pri)
include(../../Classes/CppOpenQuestion/CppOpenQuestion.pri)
include(../../Classes/CppOpenQuestionDialog/CppOpenQuestionDialog.pri)
include(../../Classes/CppPlane/CppPlane.pri)
include(../../Classes/CppQuestion/CppQuestion.pri)
include(../../Classes/CppQuestionDialog/CppQuestionDialog.pri)
include(../../Classes/CppRainbow/CppRainbow.pri)
include(../../Classes/CppShape/CppShape.pri)
include(../../Classes/CppShapeWidget/CppShapeWidget.pri)
include(../../Classes/CppStopwatch/CppStopwatch.pri)
include(../../Classes/CppTextCanvas/CppTextCanvas.pri)
include(../../Classes/CppWidget/CppWidget.pri)

#Web
include(../../Classes/CppWtGroupWidget/CppWtGroupWidget.pri)
include(../../Classes/CppWtLedWidget/CppWtLedWidget.pri)
include(../../Classes/CppWtMultipleChoiceQuestionDialog/CppWtMultipleChoiceQuestionDialog.pri)
include(../../Classes/CppWtQuestionDialog/CppWtQuestionDialog.pri)
include(../../Classes/CppWtSelectFileDialog/CppWtSelectFileDialog.pri)
include(../../Classes/CppWtServerPusher/CppWtServerPusher.pri)
include(../../Classes/CppWtShapeGroupWidget/CppWtShapeGroupWidget.pri)
include(../../Classes/CppWtShapeWidget/CppWtShapeWidget.pri)
include(../../Classes/CppWtTimedServerPusher/CppWtTimedServerPusher.pri)

include(ProjectGtstWebsite.pri)

SOURCES += wtmain.cpp


