QT       += core gui widgets

QMAKE_CXXFLAGS += -std=c++11

LIBS += \
    -lboost_system \
    -lboost_filesystem \
    -lboost_regex

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppHtmlPage \
    ../../Classes/CppQtAboutDialog \
    ../../Classes/CppTrace

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += qtmain.cpp \
    ../../Classes/CppAbout/about.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.cpp \
    createglossarymaindialog.cpp \
    createglossarymenudialog.cpp \
    qtcreateglossarymaindialog.cpp \
    qtcreateglossarymenudialog.cpp

HEADERS += \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppHtmlPage/htmlpage.h \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.h \
    ../../Classes/CppTrace/trace.h \
    createglossarymaindialog.h \
    createglossarymenudialog.h \
    qtcreateglossarymaindialog.h \
    qtcreateglossarymenudialog.h

FORMS += \
    ../../Classes/CppQtAboutDialog/qtaboutdialog.ui \
    qtcreateglossarymaindialog.ui \
    qtcreateglossarymenudialog.ui

OTHER_FILES += \
    ../../Classes/CppAbout/Licence.txt \
    ../../Classes/CppQtAboutDialog/Licence.txt \
    ../../Classes/CppTrace/Licence.txt \
    Licence.txt

RESOURCES += \
    ToolCreateGlossary.qrc
