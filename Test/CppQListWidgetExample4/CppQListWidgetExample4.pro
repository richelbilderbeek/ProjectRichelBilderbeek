QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES += \
  main.cpp \
  dialog.cpp \
    qtautoresizelistwidget.cpp

HEADERS  += dialog.h \
    qtautoresizelistwidget.h

FORMS    += dialog.ui
