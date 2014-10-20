QT       += core gui

QMAKE_CXXFLAGS += -std=c++1y

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToolSimTopPredatorPrey
TEMPLATE = app


SOURCES += main.cpp \
    qtsimtoppredatorpraymaindialog.cpp \
    qtsimpredatorpraymaindialog.cpp \
    qtfractionimage.cpp

HEADERS  += qtsimtoppredatorpraymaindialog.h \
    qtsimpredatorpraymaindialog.h \
    qtfractionimage.h

FORMS    += qtsimtoppredatorpraymaindialog.ui \
    qtsimpredatorpraymaindialog.ui
