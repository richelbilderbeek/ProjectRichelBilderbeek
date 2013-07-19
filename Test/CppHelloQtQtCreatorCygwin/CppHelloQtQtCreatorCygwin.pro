QT       += core gui

#Support both Qt4 and Qt5
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
SOURCES += main.cpp\
        dialog.cpp
HEADERS  += dialog.h
FORMS    += dialog.ui
