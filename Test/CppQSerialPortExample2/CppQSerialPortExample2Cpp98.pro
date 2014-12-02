QT       += core gui
QMAKE_CXXFLAGS += -std=c++1y -Wextra -Werror
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport
TEMPLATE = app
SOURCES += main.cpp \
        dialog.cpp
HEADERS  += dialog.h
FORMS    += dialog.ui
