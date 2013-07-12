QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
TEMPLATE = app
SOURCES += main.cpp\
        qtdialog.cpp
HEADERS  += qtdialog.h
FORMS    += qtdialog.ui
