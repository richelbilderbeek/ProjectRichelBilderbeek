QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -Werror
SOURCES +=\
    qtmain.cpp \
    qtdialog.cpp

HEADERS  += \
    qtdialog.h

FORMS    += \
    qtdialog.ui

RESOURCES += \
    CppQTableWidgetExample3.qrc
