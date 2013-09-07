QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppMultiVector
SOURCES += main.cpp
HEADERS += \
    ../../Classes/CppMultiVector/multivector.h
