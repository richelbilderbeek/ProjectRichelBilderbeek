QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11 -Wextra -Wall -Werror
SOURCES += \
    qtdialog.cpp \
    qtmain.cpp \
    mymodel.cpp \
    mydata.cpp

HEADERS  += qtdialog.h \
    mymodel.h \
    mydata.h

FORMS    += qtdialog.ui
