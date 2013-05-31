#-------------------------------------------------
#
# Project created by QtCreator 2012-01-25T20:42:26
#
#-------------------------------------------------

QT       += core gui

TARGET = ToolTestAbout
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
