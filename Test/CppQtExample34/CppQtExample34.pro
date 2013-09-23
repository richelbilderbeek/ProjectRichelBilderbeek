QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
unix {
  QMAKE_CXXFLAGS += -Werror
}

TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    qtarrowswidget.cpp \
    qtarrowitem.cpp

HEADERS += \
    qtarrowswidget.h \
    qtarrowitem.h
