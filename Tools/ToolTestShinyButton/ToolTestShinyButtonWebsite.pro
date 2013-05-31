#-------------------------------------------------
#
# Project created by QtCreator 2011-04-11T09:14:30
#
#-------------------------------------------------
QT       += core
QT       -= gui
LIBS += -lwt -lwthttp -lboost_program_options -lboost_signals -lboost_system -lboost_filesystem
TARGET = TestShinyButtonWebsite
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppDial \
  ../../Classes/CppDialWidget \
  ../../Classes/CppRainbow \
  ../../Classes/CppRectangle \
  ../../Classes/CppShinyButton \
  ../../Classes/CppShinyButtonWidget \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget \
  ../../Classes/CppWtAboutDialog \
  ../../Classes/CppWtAutoConfig \
  ../../Classes/CppWtDialWidget \
  ../../Classes/CppWtShinyButtonWidget

SOURCES += wtmain.cpp\
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppShinyButton/shinybutton.cpp \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.cpp \
  ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.cpp \
    ../../Classes/CppWtAutoConfig/wtautoconfig.cpp \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWtDialWidget/wtdialwidget.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppDial/dial.cpp \
    ../../Classes/CppRainbow/rainbow.cpp \
    testshinybuttonmenudialog.cpp \
    wttestshinybuttonmaindialog.cpp \
    wttestshinybuttonmenudialog.cpp

HEADERS  += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppShinyButton/shinybutton.h \
  ../../Classes/CppWtAboutDialog/wtaboutdialog.h \
  ../../Classes/CppWtShinyButtonWidget/wtshinybuttonwidget.h \
    ../../Classes/CppWtAutoConfig/wtautoconfig.h \
    ../../Classes/CppTrace/trace.h \
    ../../Classes/CppShinyButtonWidget/shinybuttonwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWtDialWidget/wtdialwidget.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppDial/dial.h \
    ../../Classes/CppRainbow/rainbow.h \
    testshinybuttonmenudialog.h \
    wttestshinybuttonmaindialog.h \
    wttestshinybuttonmenudialog.h

RESOURCES += \
    ToolTestShinyButton.qrc
