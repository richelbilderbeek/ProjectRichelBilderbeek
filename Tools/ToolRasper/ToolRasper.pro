QT       += core
QT       += gui
LIBS += -lwt -lwthttp -lboost_signals -lboost_regex -lboost_system -lboost_filesystem -lboost_program_options
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppRaspberryPi \
  ../../Classes/CppTrace \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig

SOURCES += wtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    raspermenudialog.cpp \
    wtraspermenudialog.cpp \
    wtraspermaindialog.cpp \
    ../../Classes/CppRaspberryPi/raspberrypigpiopin.cpp \
    wtrasperresources.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    raspermenudialog.h \
    wtraspermenudialog.h \
    wtraspermaindialog.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppRaspberryPi/raspberrypigpiopin.h \
    ../../Classes/CppRaspberryPi/raspberrypifwd.h \
    wtrasperresources.h

OTHER_FILES += \
    ../../Classes/CppTrace/Licence.txt

RESOURCES += \
    ToolRasper.qrc
