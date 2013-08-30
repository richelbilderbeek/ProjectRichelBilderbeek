QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppLed \
  ../../Classes/CppLedWidget \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtLedWidget \
  ../../Classes/CppRectangle \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget

SOURCES += qtmain.cpp \
    qttestleddialog.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppQtLedWidget/qtledwidget.cpp \
    testledmenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp

HEADERS  += \
  qttestleddialog.h \
  ../../Classes/CppLed/led.h \
  ../../Classes/CppQtLedWidget/qtledwidget.h \
    testledmenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppLedWidget/ledwidget.h

FORMS    += qttestleddialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
