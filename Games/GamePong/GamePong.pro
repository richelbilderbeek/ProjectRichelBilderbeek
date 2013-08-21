QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
TEMPLATE = app


SOURCES += main.cpp\
        pongmaindialog.cpp

HEADERS  += pongmaindialog.h

FORMS    += pongmaindialog.ui
