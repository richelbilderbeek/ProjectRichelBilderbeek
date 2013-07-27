QT       -= core
QT       -= gui
LIBS += -lwt -lwthttp
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtServerPusher

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusher.cpp \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.cpp \
    testserverpusherdata.cpp \
    testserverpushermenudialog.cpp \
    testserverpusherwtmenudialog.cpp \
    testserverpusherwtmaindialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppWtServerPusher/wtserverpusher.h \
    ../../Classes/CppWtServerPusher/wtserverpusherclient.h \
    testserverpusherdata.h \
    testserverpushermenudialog.h \
    testserverpusherwtmaindialog.h \
    testserverpusherwtmenudialog.h
