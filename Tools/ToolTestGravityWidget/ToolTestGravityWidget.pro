QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app


SOURCES += main.cpp \
        tooltestgravitywidgetmaindialog.cpp \
    qtgravitywidgetitem.cpp \
    qtgravitywidget.cpp

HEADERS  += tooltestgravitywidgetmaindialog.h \
    qtgravitywidgetitem.h \
    qtgravitywidget.h

FORMS    += tooltestgravitywidgetmaindialog.ui
