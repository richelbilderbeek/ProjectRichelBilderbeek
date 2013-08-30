QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog \
    ../../Classes/CppRandomCode

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppRandomCode/randomcode.cpp \
    randomcodemenudialog.cpp \
    qtrandomcodemaindialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtrandomcodemenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppRandomCode/randomcode.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    randomcodemenudialog.h \
    qtrandomcodemaindialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h \
    qtrandomcodemenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtrandomcodemaindialog.ui \
    qtrandomcodemenudialog.ui

RESOURCES += \
    ToolRandomCode.qrc

OTHER_FILES += \
    ../../Classes/CppQtHideAndShowDialog/Licence.txt
