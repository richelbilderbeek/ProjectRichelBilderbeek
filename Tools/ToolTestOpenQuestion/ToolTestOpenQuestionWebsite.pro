QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtMultipleChoiceQuestionDialog \
    ../../Classes/CppWtOpenQuestionDialog \
    ../../Classes/CppWtQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.cpp \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    wttestquestionmaindialog.cpp \
    wttestquestionmenudialog.cpp \
    testquestionmenudialog.cpp \
    testquestionmaindialog.cpp \
    wttestopenquestionmenudialog.cpp \
    wttestopenquestionmaindialog.cpp \
    testopenquestionmenudialog.cpp \
    testopenquestionmaindialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtMultipleChoiceQuestionDialog/wtmultiplechoicequestiondialog.h \
    ../../Classes/CppWtOpenQuestionDialog/wtopenquestiondialog.h \
    ../../Classes/CppWtQuestionDialog/wtquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    wttestopenquestionmenudialog.h \
    wttestopenquestionmaindialog.h \
    testopenquestionmenudialog.h \
    testopenquestionmaindialog.h

RESOURCES += \
    ToolTestOpenQuestion.qrc

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

unix {
  LIBS += \
    -lboost_filesystem \
    -lboost_signals \
    -lboost_system
}

win32 {
  INCLUDEPATH += \
    ../../Projects/Libraries/boost_1_54_0
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
