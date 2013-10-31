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
include(ToolHometrainerConsole.pri)

QT += core
QT -= gui
TEMPLATE = app
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += \
    main.cpp

HEADERS  +=

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
