QT       += core
QT       -= gui
QMAKE_CXXFLAGS += -std=c++0x
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
INCLUDEPATH += \
    ../../Classes/CppMultiVector
SOURCES += main.cpp
HEADERS += \
    ../../Classes/CppMultiVector/multivector.h
