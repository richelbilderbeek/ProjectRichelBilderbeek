QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppLed \
  ../../Classes/CppLedWidget \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtHideAndShowDialog \
  ../../Classes/CppQtLedWidget \
  ../../Classes/CppRectangle \
  ../../Classes/CppTrace \
  ../../Classes/CppWidget

SOURCES += qtmain.cpp \
    ../../Classes/CppLed/led.cpp \
    ../../Classes/CppQtLedWidget/qtledwidget.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppRectangle/rectangle.cpp \
    ../../Classes/CppWidget/widget.cpp \
    ../../Classes/CppLedWidget/ledwidget.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qttooltestledmaindialog.cpp \
    tooltestledmenudialog.cpp

HEADERS  += \
  ../../Classes/CppLed/led.h \
  ../../Classes/CppQtLedWidget/qtledwidget.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppRectangle/rectangle.h \
    ../../Classes/CppWidget/widget.h \
    ../../Classes/CppLedWidget/ledwidget.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qttooltestledmaindialog.h \
    tooltestledmenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttooltestledmaindialog.ui

#
#
# Type of compile
#
#

CONFIG(release, debug|release) {
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++

unix {
  QMAKE_CXXFLAGS += -Werror
}

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
