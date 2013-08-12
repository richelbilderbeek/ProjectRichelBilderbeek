TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += ../../Libraries/irrlicht-1.8/include
LIBS += -L../../Libraries/irrlicht-1.8/lib/Win32-gcc/ -lirrlicht
LIBS += -L../../Libraries/irrlicht-1.8/bin/Win32-gcc

