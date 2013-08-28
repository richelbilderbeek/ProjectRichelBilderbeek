QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror

RESOURCES += \
    ToolTestAbout.qrc

TEMPLATE = app

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += main.cpp\
        qttestaboutmaindialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppAbout/about.cpp

HEADERS  += qttestaboutmaindialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h

FORMS    += qttestaboutmaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

#
#
# Boost
#
#

win32 {

  message(Windows: add Boost to includepath)

  INCLUDEPATH += \
    ../../Libraries/boost_1_54_0
}

