#-------------------------------------------------
#
# Project created by QtCreator 2010-09-17T11:09:34
#
#-------------------------------------------------
QT       += core
QT       -= gui
TARGET = GameTicTacToeWt
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -DNDEBUG
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppTicTacToe \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtTicTacToeWidget

SOURCES += \
    tictactoemenudialog.cpp \
    wtmain.cpp \
    wttictactoegamedialog.cpp \
    wttictactoemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.cpp

HEADERS += \
    tictactoemenudialog.h \
    wttictactoegamedialog.h \
    wttictactoemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtTicTacToeWidget/wttictactoewidget.h
