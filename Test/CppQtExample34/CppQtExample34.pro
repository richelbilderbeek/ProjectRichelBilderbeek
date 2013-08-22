QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -Wextra -Werror
TARGET = CppQtExample34
TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    qtarrowswidget.cpp \
    qtarrowitem.cpp

HEADERS += \
    qtarrowswidget.h \
    qtarrowitem.h
