QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
SOURCES += main.cpp \
  sketchwidget.cpp \
  transparentsketchdialog.cpp
HEADERS  += \
  sketchwidget.h \
  transparentsketchdialog.h
FORMS    += \
  transparentsketchdialog.ui

#CONFIG += mobility
#MOBILITY =
#symbian {
#    TARGET.UID3 = 0xeaa0000d
#    # TARGET.CAPABILITY +=
#    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
#}
