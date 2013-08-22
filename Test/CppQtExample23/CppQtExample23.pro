#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T15:49:59
#
#-------------------------------------------------
QT       += core gui
TARGET = CppQtExample23
TEMPLATE = app
SOURCES += main.cpp\
        grabmedialog.cpp
HEADERS  += grabmedialog.h
FORMS    += grabmedialog.ui
CONFIG += mobility
MOBILITY = 
symbian {
    TARGET.UID3 = 0xe7eb3159
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
