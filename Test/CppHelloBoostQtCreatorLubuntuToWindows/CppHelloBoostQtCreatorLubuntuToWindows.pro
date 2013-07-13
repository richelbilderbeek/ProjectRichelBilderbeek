QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
INCLUDEPATH += ../../Libraries/mxe/usr/i686-pc-mingw32/boost
LIBS += -L../..//Libraries/mxe/usr/i686-pc-mingw32/lib -lboost_regex
