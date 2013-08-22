#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T14:39:39
#
#-------------------------------------------------

QT       += core gui

TARGET = CppQtExample22
TEMPLATE = app


SOURCES += main.cpp\
        transparentdialog.cpp

HEADERS  += transparentdialog.h

FORMS    += transparentdialog.ui

CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xec5641b7
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
