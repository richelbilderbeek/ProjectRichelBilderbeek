#-------------------------------------------------
#
# Project created by QtCreator 2011-04-10T11:16:42
#
#-------------------------------------------------
QT       -= core
QT       -= gui
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
TARGET = ToolTestTimedServerPusher
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtTimedServerPusher

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.cpp \
    testtimedserverpusherdata.cpp \
    testtimedserverpushermenudialog.cpp \
    testtimedserverpusherwtmenudialog.cpp \
    testtimedserverpusherwtmaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.h \
    testtimedserverpusherdata.h \
    testtimedserverpushermenudialog.h \
    testtimedserverpusherwtmaindialog.h \
    testtimedserverpusherwtmenudialog.h
