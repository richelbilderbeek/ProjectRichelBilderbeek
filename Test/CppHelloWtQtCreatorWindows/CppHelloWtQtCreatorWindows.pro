QT       += core
QT       -= gui

win32 {
  INCLUDEPATH += ../../Libraries/wt/src
  INCLUDEPATH += ../../Libraries/boost_1_54_0
  LIBS += ../../Libraries/wt/src
}

!win32 {
  error(Must be native Windows)
}

CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app
SOURCES += main.cpp
