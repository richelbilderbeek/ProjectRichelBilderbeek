QT       += core gui
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lwt -lwthttp -lboost_signals -lboost_regex -lboost_system -lboost_filesystem -lboost_program_options
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppRaspberryPi \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppRaspberryPi/raspberrypigpiopin.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    raspermenudialog.cpp \
    wtmain.cpp \
    wtraspermaindialog.cpp \
    wtraspermenudialog.cpp \
    wtrasperresources.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppRaspberryPi/raspberrypifwd.h \
    ../../Classes/CppRaspberryPi/raspberrypigpiopin.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    raspermenudialog.h \
    wtraspermaindialog.h \
    wtraspermenudialog.h \
    wtrasperresources.h

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt

RESOURCES += \
    ToolRasper.qrc
