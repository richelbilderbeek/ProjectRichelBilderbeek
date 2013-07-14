QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

LIBS += -L/home/richel/Projects/Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -L/../../Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -Lhome/richel/Projects/Libraries/mxe/usr/i686-pc-mingw32/lib
LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib

LIBS += -lgmp
LIBS += -lboost_regex
LIBS += -ljpeg
#LIBS += -lrichel
