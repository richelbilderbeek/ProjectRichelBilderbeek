#-------------------------------------------------
#
# Project created by QtCreator 2011-06-27T10:16:35
#
#-------------------------------------------------
QT += core gui
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppEncranger \
    ../../Classes/CppLoopReader \
    ../../Classes/CppMultipleChoiceQuestion \
    ../../Classes/CppOpenQuestion \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQuestion \
    ../../Classes/CppTrace


SOURCES += \  
    ../../Classes/CppEncranger/encranger.cpp \
    qtmain.cpp \
    qtquestionnairedialog.cpp \
    qtmenudialog.cpp \
    menudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppOpenQuestion/openquestion.cpp \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.cpp \
    ../../Classes/CppQuestion/question.cpp

HEADERS += \
    UnitFormCreateTest.h \
    UnitFormMain.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h \
    qtquestionnairedialog.h \
    qtmenudialog.h \
    UnitFormMenu.h \
    menudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppOpenQuestion/openquestion.h \
    ../../Classes/CppMultipleChoiceQuestion/multiplechoicequestion.h \
    ../../Classes/CppQuestion/question.h

LIBS += \
  -lboost_filesystem \
  -lboost_regex      \
  -lboost_system

FORMS += \
    qtquestionnairedialog.ui \
    qtmenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

RESOURCES += \
    ToolHometrainer.qrc
