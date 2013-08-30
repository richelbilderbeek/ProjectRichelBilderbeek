QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQrcFile \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

SOURCES += \
    qtmain.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppAbout/about.cpp \
    testqrcfilemenudialog.cpp \
    qttestqrcfilemenudialog.cpp \
    qttestqrcfilemaindialog.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp

HEADERS += \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    testqrcfilemenudialog.h \
    qttestqrcfilemenudialog.h \
    qttestqrcfilemaindialog.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h

FORMS += \
    qttestqrcfilemenudialog.ui \
    qttestqrcfilemaindialog.ui \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQrcFile/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolTestQrcFile.qrc
