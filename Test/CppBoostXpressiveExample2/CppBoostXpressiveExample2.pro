TEMPLATE = app
CONFIG += console
CONFIG -= qt

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}

SOURCES += main.cpp

