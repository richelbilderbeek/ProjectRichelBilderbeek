QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppQtAboutDialog

SOURCES +=  \
    beerwantermaindialog.cpp \
    beerwantermenudialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtbeerwantermaindialog.cpp \
    qtbeerwanterwidget.cpp \
    qtmain.cpp \
    qtbeerwantermenudialog.cpp

HEADERS += \
    beerwantermaindialog.h \
    beerwantermenudialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
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

