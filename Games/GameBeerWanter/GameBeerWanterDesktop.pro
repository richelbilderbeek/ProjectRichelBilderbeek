QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtAboutDialog

SOURCES +=  \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    beerwantermaindialog.cpp \
    beerwantermenudialog.cpp \
    qtbeerwantermaindialog.cpp \
    qtbeerwantermenudialog.cpp \
    qtbeerwanterwidget.cpp \
    qtmain.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    beerwantermaindialog.h \
    beerwantermenudialog.h \
    qtbeerwantermaindialog.h \
    qtbeerwantermenudialog.h \
    qtbeerwanterwidget.h


RESOURCES += \
    beerwanter.qrc

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtbeerwantermaindialog.ui \
    qtbeerwantermenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt \
    GameBeerWanterTest.sh

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
#Cannot use -Weffc++ due to use of resources
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Weffc++ -Werror

#
#
# Boost
#
#

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}

