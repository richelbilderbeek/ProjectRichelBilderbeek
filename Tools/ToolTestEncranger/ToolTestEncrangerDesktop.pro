#-------------------------------------------------
#
# Project created by QtCreator 2011-03-06T10:58:35
#
#-------------------------------------------------
QT       += core gui
TARGET = ToolTestEncranger
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppEncranger \
    ../../Classes/CppLoopReader \
    ../../Classes/CppQtAboutDialog
SOURCES += qtmain.cpp \
    qttestencrangerdialog.cpp \
    testencrangerdialog.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppEncranger/encranger.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp
HEADERS  += \
    qttestencrangerdialog.h \
    testencrangerdialog.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppEncranger/encranger.h \
    ../../Classes/CppLoopReader/loopreader.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h
FORMS    += \
    qttestencrangerdialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui
RESOURCES += \
    ToolTestEncranger.qrc
