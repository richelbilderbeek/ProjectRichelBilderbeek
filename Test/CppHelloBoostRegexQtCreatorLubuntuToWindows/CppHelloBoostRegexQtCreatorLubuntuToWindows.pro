QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -lboost_regex
