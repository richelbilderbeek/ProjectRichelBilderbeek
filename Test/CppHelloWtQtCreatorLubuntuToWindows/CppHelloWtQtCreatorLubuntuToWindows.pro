QT       += core
QT       -= gui

#LIBS += -L/home/richel/Projects/Libraries/mxe/usr/i686-pc-mingw32/lib
#LIBS += -L/../../Libraries/mxe/usr/i686-pc-mingw32/lib
#LIBS += -Lhome/richel/Projects/Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -lwt -lwthttp -lboost_signals

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
