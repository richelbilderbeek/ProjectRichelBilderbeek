#-------------------------------------------------
#
# Project created by QtCreator 2011-04-10T11:16:42
#
#-------------------------------------------------
QT       -= core
QT       -= gui
LIBS += \
  -lwt \
  -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
TARGET = ToolTestBroadcastServer
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtBroadcastServer

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserver.cpp \
    testbroadcastservermenudialog.cpp \
    testbroadcastserverwtmenudialog.cpp \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserverclient.cpp \
    testbroadcastserverwtmaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserver.h \
    testbroadcastservermenudialog.h \
    testbroadcastserverwtmaindialog.h \
    testbroadcastserverwtmenudialog.h \
    ../../Classes/CppWtBroadcastServer/wtbroadcastserverclient.h \
    testbroadcastserverwtmaindialog.h
