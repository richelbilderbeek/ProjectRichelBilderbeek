TEMPLATE = app
CONFIG += console
CONFIG -= qt

win32 {
  LIBS += -L../../Libraries/mxe/usr/i686-pc-mingw32/lib
}

LIBS += -lboost_regex

SOURCES += main.cpp

