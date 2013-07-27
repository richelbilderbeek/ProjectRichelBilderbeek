QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

LIBS += \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

INCLUDEPATH += \
    ../../Classes/CppAbout \
    ../../Classes/CppQrcFile \
    ../../Classes/CppTrace

SOURCES += main.cpp \
    ../../Classes/CppQrcFile/qrcfile.cpp \
    ../../Classes/CppAbout/about.cpp \
    testqrcfilemenudialog.cpp

HEADERS += \
    ../../Classes/CppQrcFile/qrcfile.h \
    ../../Classes/CppAbout/about.h \
    ../../Classes/CppTrace/trace.h \
    testqrcfilemenudialog.h
