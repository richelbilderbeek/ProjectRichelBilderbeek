QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
SOURCES += main.cpp\
  sketchdialog.cpp \
  sketchwidget.cpp
HEADERS  += \
  sketchdialog.h \
  sketchwidget.h
FORMS    += sketchdialog.ui

#CONFIG += mobility
#MOBILITY =
#symbian {
#    TARGET.UID3 = 0xe83b2efd
#    # TARGET.CAPABILITY +=
#    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
#}
