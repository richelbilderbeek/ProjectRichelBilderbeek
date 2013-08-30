QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

TEMPLATE = app


SOURCES += \
    main.cpp \
    tooltestgraphicsproxywidgetmaindialog.cpp \
    qttestgraphicsproxywidget.cpp \
    qttestgraphicsproxyitem.cpp \
    somedialog.cpp

HEADERS  += tooltestgraphicsproxywidgetmaindialog.h \
    qttestgraphicsproxywidget.h \
    qttestgraphicsproxyitem.h \
    somedialog.h

FORMS    += tooltestgraphicsproxywidgetmaindialog.ui \
    somedialog.ui
