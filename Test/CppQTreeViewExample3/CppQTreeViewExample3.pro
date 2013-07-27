QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

SOURCES += \
    qtdialog.cpp \
    qtmain.cpp \
    qtaddrowcommand.cpp \
    qtmytreeview.cpp \
    qtmyitem.cpp

HEADERS  += qtdialog.h \
    qtaddrowcommand.h \
    qtmytreeview.h \
    qtmyitem.h

FORMS    += qtdialog.ui
