QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
INCLUDEPATH += ../../Classes/CppStopwatch
HEADERS += \
    ../../Classes/CppStopwatch/stopwatch.h
