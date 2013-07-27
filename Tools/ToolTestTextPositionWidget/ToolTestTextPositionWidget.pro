QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
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
