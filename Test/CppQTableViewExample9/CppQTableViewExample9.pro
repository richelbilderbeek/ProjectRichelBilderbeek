QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    qtdialog.cpp \
    qtmain.cpp \
    mymodel.cpp

HEADERS  += qtdialog.h \
    mymodel.h

FORMS    += qtdialog.ui
