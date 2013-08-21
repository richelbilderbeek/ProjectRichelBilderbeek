QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
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
