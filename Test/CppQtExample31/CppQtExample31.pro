QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wextra -Werror

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
