#-------------------------------------------------
#
# Project created by QtCreator 2011-04-10T11:16:42
#
#-------------------------------------------------
QT       -= core
QT       -= gui
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppStopwatch \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtServerPusher \
  ../../Classes/CppWtTimedServerPusher

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusher.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.cpp \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.cpp \
    timepolldata.cpp \
    timepollmenudialog.cpp \
    timepollwtmaindialog.cpp \
    timepollwtmenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppStopwatch/stopwatch.h \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.h \
    ../../Classes/CppWtServerPusher/wtserverpusher.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusherclient.h \
    ../../Classes/CppWtTimedServerPusher/wttimedserverpusher.h \
    timepolldata.h \
    timepollmenudialog.h \
    timepollwtmaindialog.h \
    timepollwtmenudialog.h
