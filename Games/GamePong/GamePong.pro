QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
TARGET = GamePong
TEMPLATE = app


SOURCES += main.cpp\
        pongmaindialog.cpp

HEADERS  += pongmaindialog.h

FORMS    += pongmaindialog.ui
