QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += qtmain.cpp \
    fakeevymaindialog.cpp

HEADERS  += \
    fakeevymaindialog.h

FORMS    +=
