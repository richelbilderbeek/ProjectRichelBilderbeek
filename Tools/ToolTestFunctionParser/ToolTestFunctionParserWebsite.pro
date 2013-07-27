#-------------------------------------------------
#
# Project created by QtCreator 2011-06-24T09:21:56
#
#-------------------------------------------------

QT       += core gui

LIBS += -lwt -lwthttp

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Libraries/fparser4.4.3


SOURCES +=\
        wttestfunctionparsermaindialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Libraries/fparser4.4.3/fparser.cc \
    wtmain.cpp \
    wttestfunctionparsermenudialog.cpp \
    testfunctionparsermenudialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp

HEADERS  += wttestfunctionparsermaindialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Libraries/fparser4.4.3/fparser.hh \
    wttestfunctionparsermenudialog.h \
    testfunctionparsermenudialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h

RESOURCES += \
    ToolTestFunctionParser.qrc
