#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T14:02:32
#
#-------------------------------------------------
QT       += core gui
TARGET = CppQtExample32
TEMPLATE = app
SOURCES += main.cpp\
        transparentdialog.cpp
HEADERS  += transparentdialog.h
FORMS    += transparentdialog.ui
CONFIG += mobility
MOBILITY = 
symbian {
    TARGET.UID3 = 0xe7de6653
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
