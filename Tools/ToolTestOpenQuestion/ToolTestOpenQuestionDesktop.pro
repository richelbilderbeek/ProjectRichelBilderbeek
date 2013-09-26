QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtOpenQuestionDialog \
    ../../Classes/CppQtQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    qttestopenquestionmaindialog.cpp \
    qttestopenquestionmenudialog.cpp \
    testopenquestionmaindialog.cpp \
    testopenquestionmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    qttestopenquestionmaindialog.h \
    qttestopenquestionmenudialog.h \
    testopenquestionmaindialog.h \
    testopenquestionmenudialog.h \
    testopenquestionmaindialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui \
    qttestopenquestionmaindialog.ui \
    qttestopenquestionmenudialog.ui

RESOURCES += \
    ToolTestOpenQuestion.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

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
