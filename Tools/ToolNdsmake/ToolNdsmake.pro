#-------------------------------------------------
#
# Project created by QtCreator 2010-10-10T09:30:26
#
#-------------------------------------------------
QT += core
QT -= gui qt
TARGET = ndsmake
CONFIG   += console static
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    ../ToolTestProFile/profile.cpp \
    ndsmake.cpp
QMAKE_CXX_FLAGS_WARN_ON += -Wextra
HEADERS += \
    createholymakefile.h \
    createmakefile.h \
    ../ToolTestProFile/profile.h \
    ndsmake.h
