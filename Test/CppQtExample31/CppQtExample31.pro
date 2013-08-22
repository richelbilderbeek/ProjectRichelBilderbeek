QT       += core gui
QMAKE_CXXFLAGS += -std=c++11 -Wextra -Werror
TARGET = CppQtExample31
TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    dialog.cpp \
    qtarrowswidget.cpp \
    qtarrowitem.cpp

HEADERS += \
    dialog.h \
    qtarrowswidget.h \
    qtarrowitem.h

FORMS += dialog.ui
