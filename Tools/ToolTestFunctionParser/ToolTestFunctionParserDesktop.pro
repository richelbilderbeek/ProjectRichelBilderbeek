QT       += core gui

TEMPLATE = app

QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++0x

win32 {
  INCLUDEPATH += E:/boost_1_50_0
  INCLUDEPATH += ../../Libraries/fparser4.4.3
  LIBS += -LE:/boost_1_50_0/stage/lib
  SOURCES += ../../Libraries/fparser4.4.3/fparser.cc
}

unix {
  INCLUDEPATH += ../../Libraries/fparser4.5.1
  SOURCES += ../../Libraries/fparser4.5.1/fparser.cc
}

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    qtmain.cpp \
    qttestfunctionparsermaindialog.cpp \
    qttestfunctionparsermenudialog.cpp \
    testfunctionparsermenudialog.cpp


HEADERS += \
    qttestfunctionparsermaindialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Libraries/fparser4.4.3/fparser.hh \
    qttestfunctionparsermenudialog.h \
    testfunctionparsermenudialog.h

FORMS += \
    qttestfunctionparsermaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestfunctionparsermenudialog.ui

RESOURCES += \
    ToolTestFunctionParser.qrc
