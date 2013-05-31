QT       += core gui

TARGET = ToolTestDialDesktop
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppDial \
  ../../Classes/CppDialWidget \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtDialWidget \
  ../../Classes/CppRainbow \
  ../../Classes/CppRectangle \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget

SOURCES += qtmain.cpp\
  ../../Classes/CppAbout/about.cpp \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
  ../../Classes/CppDial/dial.cpp \
  ../../Classes/CppQtDialWidget/qtdialwidget.cpp \
    qttestdialmaindialog.cpp \
    testdialmenudialog.cpp \
    qttestdialmenudialog.cpp \
    ../../Classes/CppDialWidget/dialwidget.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppRainbow/rainbow.cpp

HEADERS  += \
  ../../Classes/CppAbout/about.h \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
  ../../Classes/CppDial/dial.h \
  ../../Classes/CppQtDialWidget/qtdialwidget.h \
    qttestdialmaindialog.h \
    testdialmenudialog.h \
    qttestdialmenudialog.h \
    ../../Classes/CppDialWidget/dialwidget.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppRainbow/rainbow.h

FORMS += \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestdialmaindialog.ui \
    qttestdialmenudialog.ui

RESOURCES += \
    ToolTestDial.qrc
