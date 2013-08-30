QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
SOURCES += main.cpp\
        grabmedialog.cpp
HEADERS  += grabmedialog.h
FORMS    += grabmedialog.ui

#CONFIG += mobility
#MOBILITY =
#symbian {
#    TARGET.UID3 = 0xe7eb3159
#    # TARGET.CAPABILITY +=
#    TARGET.EPOCSTACKSIZE = 0x14000
#    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
#}
