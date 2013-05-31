QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_signals

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += \
    wtlooseapplication.cpp \
    wtmain.cpp \
    wtloosemaindialog.cpp

HEADERS += \
    wtlooseapplication.h \
    wtloosemaindialog.h
