QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app


INCLUDEPATH += \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppQtHideAndShowDialog

SOURCES += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.cpp \
    qtmain.cpp

HEADERS  += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppQtHideAndShowDialog/qthideandshowdialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

include(ToolCreateQtProjectZipFileDesktop.pri)

