QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += ../../Classes/CppLazy_init

SOURCES += main.cpp

HEADERS += \
    ../../Classes/CppLazy_init/lazy_init.h
