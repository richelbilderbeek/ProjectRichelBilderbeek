QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    daswahreschlagerfestmenudialog.cpp \
    daswahreschlagerfestwidget.cpp \
    qtdaswahreschlagerfestmaindialog.cpp \
    qtdaswahreschlagerfestmenudialog.cpp \
    qtdaswahreschlagerfestwidget.cpp \
    qtmain.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp

HEADERS  += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    daswahreschlagerfestwidget.h \
    qtdaswahreschlagerfestmaindialog.h \
    qtdaswahreschlagerfestmenudialog.h \
    qtdaswahreschlagerfestwidget.h \
    daswahreschlagerfestmenudialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS    += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtdaswahreschlagerfestmaindialog.ui \
    qtdaswahreschlagerfestmenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt

RESOURCES += \
    GameDasWahreSchlagerfest.qrc

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
