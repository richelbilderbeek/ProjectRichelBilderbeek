QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    qtdialog.cpp \
    qtmain.cpp \
    mydata.cpp \
    mymodel.cpp

HEADERS  += qtdialog.h \
    mydata.h \
    mymodel.h

FORMS    += qtdialog.ui
