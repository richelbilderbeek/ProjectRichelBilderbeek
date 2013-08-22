#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T16:21:42
#
#-------------------------------------------------
QT       += core gui
TARGET = CppQtExample25
TEMPLATE = app
SOURCES += main.cpp \
  sketchwidget.cpp \
  transparentsketchdialog.cpp
HEADERS  += \
  sketchwidget.h \
  transparentsketchdialog.h
FORMS    += \
  transparentsketchdialog.ui
CONFIG += mobility
MOBILITY = 

symbian {
    TARGET.UID3 = 0xeaa0000d
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
