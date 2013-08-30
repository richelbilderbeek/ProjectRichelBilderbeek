QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -Wall -Wextra -Werror

TEMPLATE = app

SOURCES += \
    qttooltestbouncingrectswidgetmaindialog.cpp \
    qtmain.cpp \
    qtbouncingrectswidget.cpp \
    qtbouncingrect.cpp

HEADERS  += qttooltestbouncingrectswidgetmaindialog.h \
    qtbouncingrectswidget.h \
    qtbouncingrect.h

FORMS    += qttooltestbouncingrectswidgetmaindialog.ui
