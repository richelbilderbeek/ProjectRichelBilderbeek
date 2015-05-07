QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++1y

SOURCES += main.cpp\
        qtwidget.cpp \
    simulation.cpp \
    celltypes.cpp \
    celltype.cpp

HEADERS  += qtwidget.h \
    simulation.h \
    celltypes.h \
    celltype.h

FORMS    += qtwidget.ui
