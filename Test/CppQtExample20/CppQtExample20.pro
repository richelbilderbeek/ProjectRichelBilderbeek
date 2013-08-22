#-------------------------------------------------
#
# Project created by QtCreator 2011-02-08T10:19:56
#
#-------------------------------------------------
QT       += core gui
TARGET = CppQtExample20
TEMPLATE = app
SOURCES += main.cpp\
  sketchdialog.cpp \
  sketchwidget.cpp
HEADERS  += \
  sketchdialog.h \
  sketchwidget.h
FORMS    += sketchdialog.ui
CONFIG += mobility
MOBILITY = 
symbian {
    TARGET.UID3 = 0xe83b2efd
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
