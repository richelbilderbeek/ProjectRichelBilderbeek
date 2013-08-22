QT       += core gui
QMAKE_CXXFLAGS += -std=c++0x
TARGET = ToolTestTextPositionWidget
TEMPLATE = app

SOURCES += \
    qtmain.cpp \
    tooltesttextpositionwidgetdialog.cpp \
    qttextpositionwidget.cpp

HEADERS += \
    tooltesttextpositionwidgetdialog.h \
    qttextpositionwidget.h

FORMS += tooltesttextpositionwidgetdialog.ui
