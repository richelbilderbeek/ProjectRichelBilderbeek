QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    daswahreschlagerfestmenudialog.cpp \
    daswahreschlagerfestwidget.cpp \
    qtdaswahreschlagerfestmaindialog.cpp \
    qtdaswahreschlagerfestmenudialog.cpp \
    qtdaswahreschlagerfestwidget.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    daswahreschlagerfestwidget.h \
    qtdaswahreschlagerfestmaindialog.h \
    qtdaswahreschlagerfestmenudialog.h \
    qtdaswahreschlagerfestwidget.h \
    daswahreschlagerfestmenudialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtdaswahreschlagerfestmaindialog.ui \
    qtdaswahreschlagerfestmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt

RESOURCES += \
    GameDasWahreSchlagerfest.qrc

#
#
# Type of compile
#
#

CONFIG(debug, debug|release) {
  message(Debug mode)
}

CONFIG(release, debug|release) {
  message(Release mode)

  #Remove all asserts and TRACE
  DEFINES += NDEBUG NTRACE_BILDERBIKKEL
}

#
#
# Platform specific
#
#

#
#
# Compiler flags
#
#
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

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
