QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    qtdialog.cpp \
    qtmain.cpp

HEADERS  += qtdialog.h

FORMS    += qtdialog.ui
