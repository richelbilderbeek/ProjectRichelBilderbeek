QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++1y

SOURCES += main.cpp\
        qtwidget.cpp

HEADERS  += qtwidget.h

FORMS    += qtwidget.ui
