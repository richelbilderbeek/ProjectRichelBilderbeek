QMAKE_CXXFLAGS += -std=c++1y -Wall -Wextra
QT += core
QT += gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

include(../../Libraries/Boost.pri)

SOURCES += main.cpp
