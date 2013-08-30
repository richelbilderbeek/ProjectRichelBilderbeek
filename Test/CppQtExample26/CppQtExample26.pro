QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    tooltesttextpositionwidgetdialog.cpp \
    qttextpositionwidget.cpp \
    qttextpositionitem.cpp

HEADERS += \
    tooltesttextpositionwidgetdialog.h \
    qttextpositionwidget.h \
    qttextpositionitem.h

FORMS += tooltesttextpositionwidgetdialog.ui
