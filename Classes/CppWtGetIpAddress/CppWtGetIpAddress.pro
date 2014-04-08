#-------------------------------------------------
#
# Project created by QtCreator 2011-05-15T20:17:39
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
INCLUDEPATH += ../../Classes/CppWtAutoConfig
TARGET = CppWtGetIpAddress
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp
HEADERS += \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h
