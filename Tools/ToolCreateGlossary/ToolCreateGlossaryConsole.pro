QT       += core
QT       -= gui

QMAKE_CXXFLAGS += -std=c++0x

LIBS += \
    -lboost_system \
    -lboost_filesystem \
    -lboost_regex
INCLUDEPATH += ../../Classes/CppHtmlPage

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    ../../Classes/CppHtmlPage/htmlpage.cpp \
    createglossarymaindialog.cpp
HEADERS += \
    ../../Classes/CppHtmlPage/htmlpage.h \
    createglossarymaindialog.h
