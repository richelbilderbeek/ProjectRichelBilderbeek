#-------------------------------------------------
#
# Project created by QtCreator 2010-09-24T14:02:31
#
#-------------------------------------------------
QT       += core gui
TARGET = GameTicTacToeQt
QMAKE_CXXFLAGS += -std=c++0x
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtTicTacToeWidget \
    ../../Classes/CppTicTacToe
SOURCES += qtmain.cpp\
    qttictactoegamedialog.cpp \
    qttictactoewinnerdialog.cpp \
    qttictactoemenudialog.cpp \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.cpp \
    ../../Classes/CppTicTacToe/tictactoe.cpp \
    tictactoemenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp
HEADERS  += \
    qttictactoegamedialog.h \
    qttictactoewinnerdialog.h \
    qttictactoemenudialog.h \
    ../../Classes/CppQtTicTacToeWidget/qttictactoewidget.h \
    ../../Classes/CppTicTacToe/tictactoe.h \
    tictactoemenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h
FORMS    += \
    qttictactoegamedialog.ui \
    qttictactoewinnerdialog.ui \
    qttictactoemenudialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
RESOURCES += GameTicTacToe.qrc
