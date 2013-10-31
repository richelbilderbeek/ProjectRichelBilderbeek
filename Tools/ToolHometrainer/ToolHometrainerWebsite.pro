QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include(../../Tools/ToolHometrainer/ToolHometrainerWebsite.pri)

include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppExercise/CppExercise.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)
include(../../Classes/CppMenuDialog/CppMenuDialog.pri)
include(../../Classes/CppMultipleChoiceQuestion/CppMultipleChoiceQuestion.pri)
include(../../Classes/CppMultipleChoiceQuestionDialog/CppMultipleChoiceQuestionDialog.pri)
include(../../Classes/CppOpenQuestion/CppOpenQuestion.pri)
include(../../Classes/CppOpenQuestionDialog/CppOpenQuestionDialog.pri)
include(../../Classes/CppQuestion/CppQuestion.pri)
include(../../Classes/CppQuestionDialog/CppQuestionDialog.pri)
include(../../Classes/CppRichelBilderbeekProgram/CppRichelBilderbeekProgram.pri)
include(../../Classes/CppTrace/CppTrace.pri)

include(../../Classes/CppWtAboutDialog/CppWtAboutDialog.pri)
include(../../Classes/CppWtAutoConfig/CppWtAutoConfig.pri)
include(../../Classes/CppWtExercise/CppWtExercise.pri)
include(../../Classes/CppWtMultipleChoiceQuestionDialog/CppWtMultipleChoiceQuestionDialog.pri)
include(../../Classes/CppWtOpenQuestionDialog/CppWtOpenQuestionDialog.pri)
include(../../Classes/CppWtQuestionDialog/CppWtQuestionDialog.pri)
include(../../Classes/CppWtSelectFileDialog/CppWtSelectFileDialog.pri)

SOURCES += wtmain.cpp


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
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

LIBS += \
  -lboost_date_time \
  -lboost_filesystem \
  -lboost_program_options \
  -lboost_regex \
  -lboost_signals \
  -lboost_system

#
#
# Wt
#
#

LIBS += \
  -lwt \
  -lwthttp
