#-------------------------------------------------
#
# Project created by QtCreator 2010-12-14T12:41:04
#
#-------------------------------------------------
QT       += core gui

LIBS += -lwt -lwthttp -lboost_system -lboost_filesystem

QMAKE_CXXFLAGS += \
  -DNDEBUG \
  -std=c++0x

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig

SOURCES += wtmain.cpp \
    projectmuscadomesticamaindialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    fly.cpp \
    mating.cpp \
    random.cpp \
    newgeneration.cpp \
    nextgeneration.cpp \
    richel.cpp \
    simulation.cpp

HEADERS += \
    projectmuscadomesticamaindialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    layout.h \
    fly.h \
    mating.h \
    random.h \
    newgeneration.h \
    nextgeneration.h \
    richel.h \
    simulation.h
