QT       += core gui widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppMultipleChoiceQuestionDialog \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppOpenQuestionDialog \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtMultipleChoiceQuestionDialog \
    ../../Classes/CppQtOpenQuestionDialog \
    ../../Classes/CppQtQuestionDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppQuestionDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.cpp \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.cpp \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.cpp \
    ../../Classes/CppQuestion/question.cpp \
    ../../Classes/CppQuestionDialog/questiondialog.cpp \
    qttestquestionmaindialog.cpp \
    qttestquestionmenudialog.cpp \
    testquestionmaindialog.cpp \
    testquestionmenudialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppMultipleChoiceQuestionDialog/multiplechoicequestiondialog.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppOpenQuestionDialog/openquestiondialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.h \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.h \
    ../../Classes/CppQtQuestionDialog/qtquestiondialog.h \
    ../../Classes/CppQuestion/question.h \
    ../../Classes/CppQuestionDialog/questiondialog.h \
    qttestquestionmaindialog.h \
    qttestquestionmenudialog.h \
    testquestionmaindialog.h \
    testquestionmenudialog.h \
    testquestionmaindialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    ../../Classes/CppQtMultipleChoiceQuestionDialog/qtmultiplechoicequestiondialog.ui \
    ../../Classes/CppQtOpenQuestionDialog/qtopenquestiondialog.ui \
    qttestquestionmaindialog.ui \
    qttestquestionmenudialog.ui

RESOURCES += \
    ToolTestQuestion.qrc

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
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

#unix {
  QMAKE_CXXFLAGS += -Werror
#}

#
#
# Boost
#
#

unix {
  message(Unix: Boost already in include path)
}

win32 {
  !cross_compile
  {
    message(Native Windows: add Boost to include path)
    INCLUDEPATH += \
      ../../Libraries/boost_1_54_0
  }
  cross_compile
  {
    message(Lubuntu to Windows: Boost already in include path)
  }
}
