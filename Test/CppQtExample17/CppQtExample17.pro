QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    main.cpp \
    trafficlightdialog.cpp \
    image.cpp

HEADERS  += \
    trafficlightdialog.h \
    image.h

FORMS    += trafficlightdialog.ui

RESOURCES += \
    resources.qrc
