QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
SOURCES += main.cpp
QMAKE_CXXFLAGS += -Wall -Wextra -Werror
INCLUDEPATH += /usr/include/qwt-qt4
LIBS += -lqwt-qt4
