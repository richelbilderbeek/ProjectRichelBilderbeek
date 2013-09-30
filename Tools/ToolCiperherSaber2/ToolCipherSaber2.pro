QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
    main.cpp\
    dialog.cpp \
    cs2.cpp \
    cs2_encrypt.cpp

HEADERS  += \
    dialog.h \
    cs2.h \
    cs2_encrypt.h

FORMS    += dialog.ui
