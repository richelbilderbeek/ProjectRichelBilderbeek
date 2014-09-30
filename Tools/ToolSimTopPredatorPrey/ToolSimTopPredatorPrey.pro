QT       += core gui

QMAKE_CXXFLAGS += -std=c++1y

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToolSimTopPredatorPrey
TEMPLATE = app


SOURCES += main.cpp \
    qtsimtoppredatorpraymaindialog.cpp \
    qtsimtoppredatorpreywidget.cpp

HEADERS  += qtsimtoppredatorpraymaindialog.h \
    qtsimtoppredatorpreywidget.h

FORMS    += qtsimtoppredatorpraymaindialog.ui
