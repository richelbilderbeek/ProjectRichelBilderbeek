include(ToolHometrainerConsole.pri)
include(../../Classes/CppAbout/CppAbout.pri)
include(../../Classes/CppExercise/CppExercise.pri)
include(../../Classes/CppFileIo/CppFileIo.pri)
include(../../Classes/CppHelp/CppHelp.pri)

QT += core
QT -= gui
TEMPLATE = app

CONFIG   += console
CONFIG   -= app_bundle

INCLUDEPATH += \
    ../../Classes/CppMenuDialog \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppRichelBilderbeekProgram \
    ../../Classes/CppTrace


SOURCES += \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    ../../Classes/CppMenuDialog/menudialog.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.cpp \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.cpp \
    main.cpp

HEADERS  += \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppMenuDialog/menudialog.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtypes.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramtype.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogramstatus.h \
    ../../Classes/CppRichelBilderbeekProgram/richelbilderbeekprogram.h

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

OTHER_FILES += \
    ../../Classes/CppAbout/CppAbout.pri \
    ../../Classes/CppHelp/CppHelp.pri
