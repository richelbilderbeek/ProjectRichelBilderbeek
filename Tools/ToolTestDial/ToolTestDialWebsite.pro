#-------------------------------------------------
#
# Project created by QtCreator 2011-04-11T09:14:30
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppDial \
    ../../Classes/CppDialWidget \
    ../../Classes/CppRainbow \
    ../../Classes/CppRectangle \
    ../../Classes/CppWidget \
    ../../Classes/CppWtAboutDialog \
    ../../Classes/CppWtAutoConfig \
    ../../Classes/CppWtDialWidget

SOURCES += wtmain.cpp\
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    wttestdialmaindialog.cpp \
    wttestdialmenudialog.cpp \
    testdialmenudialog.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    wttestdialmaindialog.h \
    wttestdialmenudialog.h \
    testdialmenudialog.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppRainbow/rainbow.h

RESOURCES += \
    ToolTestDial.qrc
