QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
  ../../Classes/CppAbout \
  ../../Classes/CppDial \
  ../../Classes/CppDialWidget \
  ../../Classes/CppQtAboutDialog \
  ../../Classes/CppQtDialWidget \
  ../../Classes/CppQtHideAndShowDialog \
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
    ../../Classes/CppRainbow/rainbow.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

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
    ../../Classes/CppRainbow/rainbow.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS += \
  ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qttestdialmaindialog.ui \
    qttestdialmenudialog.ui

RESOURCES += \
    ToolTestDial.qrc

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
