QT       -= core
QT       -= gui
TARGET = CppAddOne

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -effc++

#Needed for gprog
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
