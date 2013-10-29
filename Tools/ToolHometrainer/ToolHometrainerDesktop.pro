include(../../Classes/CppFileIo/CppFileIo.pro)
include(ToolHometrainerDesktop.pri)

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

# Console

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

# Qt


INCLUDEPATH += \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtMultipleChoiceQuestionDialog \
    ../../Classes/CppQtOpenQuestionDialog \
    ../../Classes/CppQtQuestionDialog

SOURCES += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtExercise/qtexercise.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtExercise/qtexercise.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui


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
    ../../Classes/CppExercise/CppExercise.pri
