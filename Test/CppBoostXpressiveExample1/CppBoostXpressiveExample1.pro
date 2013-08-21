QT       += core
QT       -= gui
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++11

win32 {
  INCLUDEPATH += ../../Libraries/boost_1_54_0
}
