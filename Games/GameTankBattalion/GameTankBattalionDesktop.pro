QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
SOURCES += main.cpp\
        dialoggame.cpp \
    qtgamewidget.cpp \
    tankbattalion.cpp
HEADERS  += dialoggame.h \
    qtgamewidget.h \
    tankbattalion.h
FORMS    += dialoggame.ui

RESOURCES += \
    qtresources.qrc
